#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Nov. 2025

Downloaded from the bottom of the page as "cursor_demo.py" from here!:
https://matplotlib.org/stable/gallery/event_handling/cursor_demo.html


=================
Cross-hair cursor [makes 3 plots]
=================

This example adds a cross-hair as a data cursor.  The cross-hair is
implemented as regular line objects that are updated on mouse move.

We show three implementations:

1) A simple cursor implementation that redraws the figure on every mouse move.
   This is a bit slow, and you may notice some lag of the cross-hair movement.
2) A cursor that uses blitting for speedup of the rendering.
3) A cursor that snaps to data points.

Faster cursoring is possible using native GUI drawing, as in
:doc:`/gallery/user_interfaces/wxcursor_demo_sgskip`.

The mpldatacursor__ and mplcursors__ third-party packages can be used to
achieve a similar effect.

__ https://github.com/joferkington/mpldatacursor
__ https://github.com/anntzer/mplcursors

.. redirect-from:: /gallery/misc/cursor_demo
"""

import matplotlib.pyplot as plt
import numpy as np

from matplotlib.backend_bases import MouseEvent


class Cursor:
    """
    A cross hair cursor.
    """
    def __init__(self, ax):
        self.ax = ax
        self.horizontal_line = ax.axhline(color='k', lw=0.8, ls='--')
        self.vertical_line = ax.axvline(color='k', lw=0.8, ls='--')
        # text location in axes coordinates [`transform=ax.transAxes`] to always keep it in the 
        # same plot location regardless of data limits, zooming, panning, scrolling, etc.
        self.text = ax.text(0.72, 0.9, '', transform=ax.transAxes)

    def set_cross_hair_visible(self, visible: bool):
        need_redraw = self.horizontal_line.get_visible() != visible
        self.horizontal_line.set_visible(visible)
        self.vertical_line.set_visible(visible)
        self.text.set_visible(visible)
        return need_redraw

    def on_mouse_move(self, event: MouseEvent):
        if not event.inaxes:
            need_redraw = self.set_cross_hair_visible(False)
            if need_redraw:
                self.ax.figure.canvas.draw()
        else:
            self.set_cross_hair_visible(True)
            x, y = event.xdata, event.ydata
            # update the line positions
            self.horizontal_line.set_ydata([y])
            self.vertical_line.set_xdata([x])
            self.text.set_text(f'x={x:1.2f}, y={y:1.2f}')
            self.ax.figure.canvas.draw()


def test_simple_cursor():
    x = np.arange(0, 1, 0.01)
    y = np.sin(2 * 2 * np.pi * x)

    fig, ax = plt.subplots()
    ax.set_title('Simple cursor')
    ax.plot(x, y, 'o')
    simple_cursor = Cursor(ax)
    fig.canvas.mpl_connect('motion_notify_event', simple_cursor.on_mouse_move)

    # Simulate a mouse move to (0.5, 0.5), needed for online docs
    t = ax.transData
    MouseEvent(
        "motion_notify_event", ax.figure.canvas, *t.transform((0.5, 0.5))
    )._process()
    
    return simple_cursor


# %%
# Faster redrawing using blitting
# """""""""""""""""""""""""""""""
# This technique stores the rendered plot as a background image. Only the
# changed artists (cross-hair lines and text) are rendered anew. They are
# combined with the background using blitting.
#
# This technique is significantly faster. It requires a bit more setup because
# the background has to be stored without the cross-hair lines (see
# ``create_new_background()``). Additionally, a new background has to be
# created whenever the figure changes. This is achieved by connecting to the
# ``'draw_event'``.


class BlittedCursor:
    """
    A cross-hair cursor using blitting for faster redraw.
    """
    def __init__(self, ax):
        self.ax = ax
        self.background = None
        self.horizontal_line = ax.axhline(color='k', lw=0.8, ls='--')
        self.vertical_line = ax.axvline(color='k', lw=0.8, ls='--')
        # text location in axes coordinates [`transform=ax.transAxes`] to always keep it in the 
        # same plot location regardless of data limits, zooming, panning, scrolling, etc.
        self.text = ax.text(0.72, 0.9, '', transform=ax.transAxes)
        self._creating_background = False
        ax.figure.canvas.mpl_connect('draw_event', self.on_draw)

    def on_draw(self, event):
        self.create_new_background()

    def set_cross_hair_visible(self, visible: bool):
        need_redraw = self.horizontal_line.get_visible() != visible
        self.horizontal_line.set_visible(visible)
        self.vertical_line.set_visible(visible)
        self.text.set_visible(visible)
        return need_redraw

    def create_new_background(self):
        if self._creating_background:
            # discard calls triggered from within this function
            return
        self._creating_background = True
        self.set_cross_hair_visible(False)
        self.ax.figure.canvas.draw()
        self.background = self.ax.figure.canvas.copy_from_bbox(self.ax.bbox)
        self.set_cross_hair_visible(True)
        self._creating_background = False

    def on_mouse_move(self, event: MouseEvent):
        if self.background is None:
            self.create_new_background()
        if not event.inaxes:
            need_redraw = self.set_cross_hair_visible(False)
            if need_redraw:
                self.ax.figure.canvas.restore_region(self.background)
                self.ax.figure.canvas.blit(self.ax.bbox)
        else:
            self.set_cross_hair_visible(True)
            # update the line positions
            x, y = event.xdata, event.ydata
            self.horizontal_line.set_ydata([y])
            self.vertical_line.set_xdata([x])
            self.text.set_text(f'x={x:1.2f}, y={y:1.2f}')

            self.ax.figure.canvas.restore_region(self.background)
            self.ax.draw_artist(self.horizontal_line)
            self.ax.draw_artist(self.vertical_line)
            self.ax.draw_artist(self.text)
            self.ax.figure.canvas.blit(self.ax.bbox)


def test_blitted_cursor():
    x = np.arange(0, 1, 0.01)
    y = np.sin(2 * 2 * np.pi * x)

    fig, ax = plt.subplots()
    ax.set_title('Blitted cursor')
    ax.plot(x, y, 'o')
    blitted_cursor = BlittedCursor(ax)
    fig.canvas.mpl_connect('motion_notify_event', blitted_cursor.on_mouse_move)

    # Simulate a mouse move to (0.5, 0.5), needed for online docs
    t = ax.transData
    MouseEvent(
        "motion_notify_event", ax.figure.canvas, *t.transform((0.5, 0.5))
    )._process()
    
    return blitted_cursor


# %%
# Snapping to data points
# """""""""""""""""""""""
# The following cursor snaps its position to the data points of a `.Line2D`
# object.
#
# To save unnecessary redraws, the index of the last indicated data point is
# saved in ``self._last_index``. A redraw is only triggered when the mouse
# moves far enough so that another data point must be selected. This reduces
# the lag due to many redraws. Of course, blitting could still be added on top
# for additional speedup.


class SnappingCursor:
    """
    A cross-hair cursor that snaps to the data point of a line, which is
    closest to the *x* position of the cursor.

    For simplicity, this assumes that *x* values of the data are sorted.
    """
    def __init__(self, ax, line):
        self.ax = ax
        self.horizontal_line = ax.axhline(color='k', lw=0.8, ls='--')
        self.vertical_line = ax.axvline(color='k', lw=0.8, ls='--')
        self.x, self.y = line.get_data()
        self._last_index = None
        # text location in axes coordinates [`transform=ax.transAxes`] to always keep it in the 
        # same plot location regardless of data limits, zooming, panning, scrolling, etc.
        self.text = ax.text(0.72, 0.9, '', transform=ax.transAxes)

    def set_cross_hair_visible(self, visible: bool):
        need_redraw = self.horizontal_line.get_visible() != visible
        self.horizontal_line.set_visible(visible)
        self.vertical_line.set_visible(visible)
        self.text.set_visible(visible)
        return need_redraw

    def on_mouse_move(self, event: MouseEvent):
        if not event.inaxes:
            self._last_index = None
            need_redraw = self.set_cross_hair_visible(False)
            if need_redraw:
                self.ax.figure.canvas.draw()
        else:
            self.set_cross_hair_visible(True)
            x, y = event.xdata, event.ydata
            index = min(np.searchsorted(self.x, x), len(self.x) - 1)
            if index == self._last_index:
                return  # still on the same data point. Nothing to do.
            self._last_index = index
            x = self.x[index]
            y = self.y[index]
            # update the line positions
            self.horizontal_line.set_ydata([y])
            self.vertical_line.set_xdata([x])
            self.text.set_text(f'x={x:1.2f}, y={y:1.2f}')
            self.ax.figure.canvas.draw()


def test_snapping_cursor():
    x = np.arange(0, 1, 0.01)
    y = np.sin(2 * 2 * np.pi * x)

    fig, ax = plt.subplots()
    ax.set_title('Snapping cursor')
    line, = ax.plot(x, y, 'o')
    snap_cursor = SnappingCursor(ax, line)
    fig.canvas.mpl_connect('motion_notify_event', snap_cursor.on_mouse_move)

    # Simulate a mouse move to (0.5, 0.5), needed for online docs
    t = ax.transData
    MouseEvent(
        "motion_notify_event", ax.figure.canvas, *t.transform((0.5, 0.5))
    )._process()
    
    return snap_cursor


class SnappingBlittedCursor:
    """
    A cross-hair cursor that snaps to data points AND uses blitting for faster redraw.
    
    This combines the best of both worlds: snapping to exact data points for precision
    and blitting for performance.
    """
    def __init__(self, ax, line):
        self.ax = ax
        self.background = None
        self.horizontal_line = ax.axhline(color='k', lw=0.8, ls='--')
        self.vertical_line = ax.axvline(color='k', lw=0.8, ls='--')
        self.x, self.y = line.get_data()
        self._last_index = None
        # text location in axes coordinates [`transform=ax.transAxes`] to always keep it in the 
        # same plot location regardless of data limits, zooming, panning, scrolling, etc.
        self.text = ax.text(0.72, 0.9, '', transform=ax.transAxes)
        self._creating_background = False
        ax.figure.canvas.mpl_connect('draw_event', self.on_draw)

    def on_draw(self, event):
        self.create_new_background()

    def set_cross_hair_visible(self, visible: bool):
        need_redraw = self.horizontal_line.get_visible() != visible
        self.horizontal_line.set_visible(visible)
        self.vertical_line.set_visible(visible)
        self.text.set_visible(visible)
        return need_redraw

    def create_new_background(self):
        if self._creating_background:
            # discard calls triggered from within this function
            return
        self._creating_background = True
        self.set_cross_hair_visible(False)
        self.ax.figure.canvas.draw()
        self.background = self.ax.figure.canvas.copy_from_bbox(self.ax.bbox)
        self.set_cross_hair_visible(True)
        self._creating_background = False

    def on_mouse_move(self, event: MouseEvent):
        if self.background is None:
            self.create_new_background()
        if not event.inaxes:
            self._last_index = None
            need_redraw = self.set_cross_hair_visible(False)
            if need_redraw:
                self.ax.figure.canvas.restore_region(self.background)
                self.ax.figure.canvas.blit(self.ax.bbox)
        else:
            self.set_cross_hair_visible(True)
            x, y = event.xdata, event.ydata

            # Search for the nearest data point to the cursor on the x-axis to "snap" to it
            index = min(np.searchsorted(self.x, x), len(self.x) - 1)
            if index == self._last_index:
                return  # still on the same data point. Nothing to do.
            self._last_index = index
            x = self.x[index]
            y = self.y[index]
            
            # update the line positions
            self.horizontal_line.set_ydata([y])
            self.vertical_line.set_xdata([x])
            self.text.set_text(f'x={x:1.2f}, y={y:1.2f}')

            self.ax.figure.canvas.restore_region(self.background)
            self.ax.draw_artist(self.horizontal_line)
            self.ax.draw_artist(self.vertical_line)
            self.ax.draw_artist(self.text)
            self.ax.figure.canvas.blit(self.ax.bbox)


class SnappingBlittedCursorMultipleSubplots:
    """
    A cross-hair cursor that snaps to data points AND uses blitting for faster redraw.
    
    This combines the best of both worlds: snapping to exact data points for precision
    and blitting for performance.
    
    Can handle multiple subplots with synchronized cursors across all subplots.
    """
    def __init__(self, ax, line):
        if isinstance(ax, list):
            # Multiple axes case
            self.axes = ax
            self.lines = line if isinstance(line, list) else [line] * len(ax)
            self.fig = ax[0].figure
        else:
            # Single axis case (backward compatibility)
            self.axes = [ax]
            self.lines = [line]
            self.fig = ax.figure
            
        self.background = None
        self.horizontal_lines = []
        self.vertical_lines = []
        self.texts = []
        self.x_data = []
        self.y_data = []
        self._last_indices = [None] * len(self.axes)
        
        # Create cursor elements for each axis
        for i, (ax, line) in enumerate(zip(self.axes, self.lines)):
            h_line = ax.axhline(color='k', lw=0.8, ls='--')
            v_line = ax.axvline(color='k', lw=0.8, ls='--')
            # text location in axes coordinates [`transform=ax.transAxes`] to always keep it in the 
            # same plot location regardless of data limits, zooming, panning, scrolling, etc.
            text = ax.text(0.72, 0.9, '', transform=ax.transAxes)
            
            self.horizontal_lines.append(h_line)
            self.vertical_lines.append(v_line)
            self.texts.append(text)
            
            x, y = line.get_data()
            self.x_data.append(x)
            self.y_data.append(y)
            
        self._creating_background = False
        self.fig.canvas.mpl_connect('draw_event', self.on_draw)

    def on_draw(self, event):
        self.create_new_background()

    def set_cross_hair_visible(self, visible: bool):
        need_redraw = False
        for h_line, v_line, text in zip(self.horizontal_lines, self.vertical_lines, self.texts):
            if h_line.get_visible() != visible:
                need_redraw = True
            h_line.set_visible(visible)
            v_line.set_visible(visible)
            text.set_visible(visible)
        return need_redraw

    def create_new_background(self):
        if self._creating_background:
            # discard calls triggered from within this function
            return
        self._creating_background = True
        self.set_cross_hair_visible(False)
        self.fig.canvas.draw()
        self.background = self.fig.canvas.copy_from_bbox(self.fig.bbox)
        self.set_cross_hair_visible(True)
        self._creating_background = False

    def on_mouse_move(self, event: MouseEvent):
        if self.background is None:
            self.create_new_background()
            
        # Check if mouse is in any of our axes
        active_ax_index = None
        for i, ax in enumerate(self.axes):
            if event.inaxes == ax:
                active_ax_index = i
                break
                
        if active_ax_index is None:
            # Mouse not in any of our axes
            self._last_indices = [None] * len(self.axes)
            need_redraw = self.set_cross_hair_visible(False)
            if need_redraw:
                self.fig.canvas.restore_region(self.background)
                self.fig.canvas.blit(self.fig.bbox)
        else:
            self.set_cross_hair_visible(True)
            x, y = event.xdata, event.ydata

            # Find the data point to snap to in the active axis
            x_data = self.x_data[active_ax_index]
            y_data = self.y_data[active_ax_index]
            index = min(np.searchsorted(x_data, x), len(x_data) - 1)
            
            if index == self._last_indices[active_ax_index]:
                return  # still on the same data point. Nothing to do.
                
            # Update all last indices to the same index for synchronization
            self._last_indices = [index] * len(self.axes)
            
            # Get the snapped x position from the active axis
            snapped_x = x_data[index]
            
            # Update cursor lines on ALL axes using the same x position
            for i, (h_line, v_line, text, x_dat, y_dat) in enumerate(
                zip(self.horizontal_lines, self.vertical_lines, self.texts, 
                    self.x_data, self.y_data)):
                
                # Find the corresponding y value for this snapped x in each axis
                if i == active_ax_index:
                    # For the active axis, use the exact snapped point
                    snap_y = y_data[index]
                else:
                    # For other axes, find the closest x value
                    other_index = min(np.searchsorted(x_dat, snapped_x), len(x_dat) - 1)
                    snap_y = y_dat[other_index]
                
                # Update the line positions
                h_line.set_ydata([snap_y])
                v_line.set_xdata([snapped_x])
                text.set_text(f'x={snapped_x:1.2f}, y={snap_y:1.2f}')

            self.fig.canvas.restore_region(self.background)
            
            # Draw all artists
            for h_line, v_line, text in zip(self.horizontal_lines, self.vertical_lines, self.texts):
                for ax in self.axes:
                    if h_line.axes == ax:
                        ax.draw_artist(h_line)
                        ax.draw_artist(v_line)
                        ax.draw_artist(text)
                        
            self.fig.canvas.blit(self.fig.bbox)


def test_snapping_blitted_cursor():
    x = np.arange(0, 1, 0.01)
    y = np.sin(2 * 2 * np.pi * x)

    fig, ax = plt.subplots()
    ax.set_title('Snapping Blitted cursor')
    line, = ax.plot(x, y, 'o')
    snap_blit_cursor = SnappingBlittedCursor(ax, line)
    fig.canvas.mpl_connect('motion_notify_event', snap_blit_cursor.on_mouse_move)

    # Simulate a mouse move to (0.5, 0.5), needed for online docs
    t = ax.transData
    MouseEvent(
        "motion_notify_event", ax.figure.canvas, *t.transform((0.5, 0.5))
    )._process()
    
    return snap_blit_cursor


def test_snapping_blitted_cursor2():
    """
    Test `SnappingBlittedCursorMultipleSubplots` with a single subplot.
    """
    x = np.arange(0, 1, 0.01)
    y = np.sin(2 * 2 * np.pi * x)

    fig, ax = plt.subplots()
    ax.set_title('Snapping Blitted cursor 2')
    line, = ax.plot(x, y, 'o')
    snap_blit_cursor = SnappingBlittedCursorMultipleSubplots(ax, line)
    fig.canvas.mpl_connect('motion_notify_event', snap_blit_cursor.on_mouse_move)

    # Simulate a mouse move to (0.5, 0.5), needed for online docs
    t = ax.transData
    MouseEvent(
        "motion_notify_event", ax.figure.canvas, *t.transform((0.5, 0.5))
    )._process()
    
    return snap_blit_cursor


def test_snapping_blitted_cursor_multiple_subplots():
    """
    Test SnappingBlittedCursor with multiple subplots (3 rows x 1 column).
    
    Creates synchronized cursors across all subplots that snap to data points.
    Moving the mouse over any subplot will show cursors on all subplots at the
    same x-coordinate.
    """
    # Generate different datasets for each subplot
    x = np.arange(0, 2, 0.02)  # Common x-axis for all plots
    y1 = np.sin(2 * np.pi * x)           # Sine wave
    y2 = np.cos(3 * np.pi * x)           # Cosine wave with different frequency  
    y3 = x**2 - x                        # Quadratic function
    
    # Create figure with 3 subplots in 1 column
    fig, (ax1, ax2, ax3) = plt.subplots(3, 1, figsize=(10, 8), sharex=True)
    
    # Plot data on each subplot
    line1, = ax1.plot(x, y1, 'o-', markersize=3, label='sin(2πx)')
    line2, = ax2.plot(x, y2, 's-', markersize=3, color='orange', label='cos(3πx)')
    line3, = ax3.plot(x, y3, '^-', markersize=3, color='green', label='x² - x')
    
    # Set titles and labels
    ax1.set_title('Multiple Subplots with Synchronized Snapping Blitted Cursor')
    ax1.set_ylabel('sin(2πx)')
    ax1.legend()
    ax1.grid(True, alpha=0.3)
    
    ax2.set_ylabel('cos(3πx)')  
    ax2.legend()
    ax2.grid(True, alpha=0.3)
    
    ax3.set_ylabel('x² - x')
    ax3.set_xlabel('x')
    ax3.legend()
    ax3.grid(True, alpha=0.3)
    
    # Create the multi-subplot cursor
    axes = [ax1, ax2, ax3]
    lines = [line1, line2, line3]
    multi_cursor = SnappingBlittedCursorMultipleSubplots(axes, lines)
    fig.canvas.mpl_connect('motion_notify_event', multi_cursor.on_mouse_move)
    
    # Add instructions
    fig.text(0.5, 0.02, 
             'Move mouse over any subplot to see synchronized cursors that snap to data points',
             ha='center', fontsize=10, style='italic')
    
    plt.tight_layout()
    plt.subplots_adjust(bottom=0.1)  # Make room for instructions
    
    # Simulate a mouse move to (0.5, 0.5) on the first subplot
    t = ax1.transData
    MouseEvent(
        "motion_notify_event", ax1.figure.canvas, *t.transform((0.5, 0.5))
    )._process()
    
    return multi_cursor


def main():
    # Keep references to cursor objects so they don't get garbage collected
    cursor1 = test_simple_cursor()
    cursor2 = test_blitted_cursor()
    cursor3 = test_snapping_cursor()
    cursor4 = test_snapping_blitted_cursor()
    cursor5 = test_snapping_blitted_cursor2()
    cursor6 = test_snapping_blitted_cursor_multiple_subplots()
    plt.show()


if __name__ == "__main__":
    main()
