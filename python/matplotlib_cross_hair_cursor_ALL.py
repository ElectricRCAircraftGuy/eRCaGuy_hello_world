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

import matplotlib
import matplotlib.pyplot as plt
import matplotlib.dates as mdates
import numpy as np
import pandas as pd
from datetime import datetime
from typing import Union, List

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

    # Note: Simulated mouse events don't work well with blitted cursors
    # due to background creation timing. Move mouse over plot to see cursor.

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
    def __init__(self, ax: matplotlib.axes.Axes, line: matplotlib.lines.Line2D):
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


# [BEST!--USE THIS ONE!]
class SnappingBlittedCursorMultipleSubplots:
    """
    A cross-hair cursor that snaps to data points AND uses blitting for faster redraw.

    This combines the best of both worlds: snapping to exact data points for precision
    and blitting for performance.

    Can handle multiple subplots with synchronized cursors across all subplots.
    """
    def __init__(self,
                 axes: Union[matplotlib.axes.Axes, List[matplotlib.axes.Axes]],
                 lines: Union[matplotlib.lines.Line2D, List[matplotlib.lines.Line2D]]):
        """
        Initialize the cursor.

        Args:
            ax: Either a single matplotlib.axes.Axes object, or a list of matplotlib.axes.Axes
                objects
            line: Either a single matplotlib.lines.Line2D object, or a list of
                matplotlib.lines.Line2D objects

        Note: If one parameter is a list, then both must be lists of the same length.
        """
        if isinstance(axes, list):
            # Multiple axes case: `axes` is a list of axes, and `lines` is a list of lines
            if not isinstance(lines, list) or len(lines) != len(axes):
                raise ValueError(
                    "When `axes` is a list, `lines` must also be a list of the same length.")
            self.axes = axes
            self.lines = lines
        else:
            # Single axis case (backward compatibility): force into a list of len 1
            self.axes = [axes]
            self.lines = [lines]

        self.num_subplots = len(self.axes)

        # Group axes by figure and store separate backgrounds for each figure, since
        # each figure has its own canvas and background, and each axis can belong to the same
        # or a different figure.
        self.figures = {}  # Dict[figure] -> {'axes': [axes], 'background': background}
        for ax in self.axes:
            if ax.figure not in self.figures:
                self.figures[ax.figure] = {'axes': [], 'background': None}
            self.figures[ax.figure]['axes'].append(ax)

        print(f"DEBUG: len(self.figures) = {len(self.figures)}")

        # Connect draw events to all figures
        for fig in self.figures.keys():
            fig.canvas.mpl_connect('draw_event', self.on_draw)

        self.horizontal_lines = []
        self.vertical_lines = []
        self.texts = []
        self.x_data = []
        self.y_data = []
        self._last_indices = [None] * self.num_subplots
        self._creating_background = False

        # Create cursor elements for each axis
        for i, (ax, line) in enumerate(zip(self.axes, self.lines)):
            h_line = ax.axhline(color='k', lw=0.8, ls='--')
            v_line = ax.axvline(color='k', lw=0.8, ls='--')
            # text location in axes coordinates [`transform=ax.transAxes`] to always keep it in the
            # same plot location regardless of data limits, zooming, panning, scrolling, etc.
            text = ax.text(0.82, 0.95, '', transform=ax.transAxes)

            self.horizontal_lines.append(h_line)
            self.vertical_lines.append(v_line)
            self.texts.append(text)

            x, y = line.get_data()
            self.x_data.append(x)
            self.y_data.append(y)

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

        # Create background for each figure separately
        for fig, fig_data in self.figures.items():
            fig.canvas.draw()
            fig_data['background'] = fig.canvas.copy_from_bbox(fig.bbox)

        self.set_cross_hair_visible(True)
        self._creating_background = False

    def on_mouse_move(self, event: MouseEvent):
        # Check if any figure needs background creation
        need_background = any(fig_data['background'] is None for fig_data in self.figures.values())
        if need_background:
            self.create_new_background()

        # Check if mouse is in any of our axes
        active_ax_index = None
        for i, ax in enumerate(self.axes):
            if event.inaxes == ax:
                active_ax_index = i
                break

        if active_ax_index is None:
            # Mouse not in any of our axes
            self._last_indices = [None] * self.num_subplots
            need_redraw = self.set_cross_hair_visible(False)
            if need_redraw:
                # Restore and blit each figure separately
                for fig, fig_data in self.figures.items():
                    if fig_data['background'] is not None:
                        fig.canvas.restore_region(fig_data['background'])
                        fig.canvas.blit(fig.bbox)
        else:
            # The mouse is in one of our axes

            self.set_cross_hair_visible(True)
            x, y = event.xdata, event.ydata

            # Find the active axis data
            x_data = self.x_data[active_ax_index]
            y_data = self.y_data[active_ax_index]

            # Check if x_data contains datetime objects and convert to numeric if needed
            x_data_numeric = x_data
            self.use_date_objects = False
            if len(x_data) > 0 and isinstance(x_data[0], (pd.Timestamp, datetime, np.datetime64)):
                # x_data contains datetime objects - convert to matplotlib's numeric format
                x_data_numeric = mdates.date2num(x_data)
                self.use_date_objects = True

            # Search for the nearest data point to the cursor on the x-axis to "snap" to it
            # - Find the closest data point by checking both index and index-1
            index = min(np.searchsorted(x_data_numeric, x), len(x_data_numeric) - 1)
            index_minus1 = max(index - 1, 0)
            x_dist1 = abs(x_data_numeric[index] - x)
            x_dist2 = abs(x_data_numeric[index_minus1] - x)
            if x_dist1 <= x_dist2:
                index = index
            else:
                index = index_minus1

            if index == self._last_indices[active_ax_index]:
                return  # still on the same data point. Nothing to do.

            # Update all last indices to the same index for synchronization
            self._last_indices = [index] * self.num_subplots

            # Get the snapped x position from the active axis
            snapped_x = x_data[index]

            # Update cursor lines on ALL axes using the same x position
            for i, (h_line, v_line, text, x_data, y_data) in enumerate(
                zip(self.horizontal_lines, self.vertical_lines, self.texts,
                    self.x_data, self.y_data)):

                # So long as the subplots all share the same x-axis data, we can just use the same
                # index
                snapped_y = y_data[index]

                # Update the line positions
                h_line.set_ydata([snapped_y])
                v_line.set_xdata([snapped_x])

                # Format the text display - handle datetime vs numeric data
                if self.use_date_objects:
                    # For datetime objects, use a more readable format
                    if hasattr(snapped_x, 'strftime'):
                        x_text = snapped_x.strftime('%H:%M:%S')
                    else:
                        x_text = str(snapped_x)
                else:
                    # For numeric data, use standard formatting
                    x_text = f'{snapped_x:1.9f}'

                text.set_text(f'x={x_text}, y={snapped_y:1.9f}')

            # Restore background and draw artists for each figure separately
            for fig, fig_data in self.figures.items():
                if fig_data['background'] is not None:
                    fig.canvas.restore_region(fig_data['background'])

                    # Draw artists for axes in this figure only
                    for ax in fig_data['axes']:
                        for i, (h_line, v_line, text) in enumerate(zip(self.horizontal_lines, self.vertical_lines, self.texts)):
                            if h_line.axes == ax:
                                ax.draw_artist(h_line)
                                ax.draw_artist(v_line)
                                ax.draw_artist(text)

                    # Blit this figure
                    fig.canvas.blit(fig.bbox)


def test_snapping_blitted_cursor():
    x = np.arange(0, 1, 0.01)
    y = np.sin(2 * 2 * np.pi * x)

    fig, ax = plt.subplots()
    ax.set_title('Snapping Blitted cursor')
    line, = ax.plot(x, y, 'o')
    snap_blit_cursor = SnappingBlittedCursor(ax, line)
    fig.canvas.mpl_connect('motion_notify_event', snap_blit_cursor.on_mouse_move)

    # Note: Simulated mouse events don't work well with blitted cursors
    # due to background creation timing. Move mouse over plot to see cursor.

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

    # Note: Simulated mouse events don't work well with blitted cursors
    # due to background creation timing. Move mouse over plot to see cursor.

    return snap_blit_cursor


# [BEST]
def test_snapping_blitted_cursor_multiple_subplots():
    """
    Test SnappingBlittedCursor with multiple subplots (3 rows x 1 column).

    Creates synchronized cursors across all subplots that snap to data points.
    Moving the mouse over any subplot will show cursors on all subplots at the
    same x-coordinate.
    """
    # Generate different datasets for each subplot
    x = np.arange(0, 2, 0.02)  # Common x-axis for all plots
    y1 = np.sin(2 * np.pi * x)           # Sine wave (sin(2πx))
    y2 = np.cos(3 * np.pi * x)           # Cosine wave with different frequency (cos(3πx))
    y3 = x**2 - x                        # Quadratic function (x² - x)

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
             'Move mouse over any subplot to see synchronized cursors that snap to data points.',
             ha='center', fontsize=10, style='italic')

    plt.tight_layout()
    plt.subplots_adjust(bottom=0.1)  # Make room for instructions

    # [Removed] Simulate a mouse move to (0.5, 0.5) on the first subplot
    # Note: Simulated mouse events don't work well with blitted cursors
    # due to background creation timing. Move mouse over plot to see cursor.

    return multi_cursor


def test_snapping_blitted_cursor_multiple_subplots_and_figures():
    """
    Test synchronized cursors across multiple figures AND multiple subplots.

    Creates:
    - Figure 1: 3 subplots (velocity, acceleration, jerk) in 1 column
    - Figure 2: 1 subplot (combined view)

    All cursors are synchronized - moving mouse over any subplot in either figure
    will show cursors on ALL subplots across BOTH figures at the same x-coordinate.
    """
    # Generate datasets (same x-axis for all plots for synchronization)
    x = np.arange(0, 2, 0.02)  # Common x-axis for all plots

    # Simulated data derivatives
    # Velocity with noise
    y_velocity = np.sin(2 * np.pi * x) + 0.1 * np.random.randn(len(x))
    # Acceleration with noise
    y_acceleration = np.cos(3 * np.pi * x) + 0.05 * np.random.randn(len(x))
    # Jerk (derivative of acceleration)
    y_jerk = np.diff(y_acceleration, prepend=y_acceleration[0])
    # Combined signal
    y_combined = y_velocity + 0.5 * y_acceleration

    # ==============================================
    # Figure 1: Multi-subplot figure (3 subplots)
    # ==============================================
    fig1, (ax1, ax2, ax3) = plt.subplots(3, 1, figsize=(12, 9), sharex=True)
    fig1.suptitle('Figure 1: Data Analysis - Velocity, Acceleration, Jerk', fontsize=14)

    # Plot data on each subplot
    line1, = ax1.plot(x, y_velocity, 'o-', markersize=2, linewidth=1,
                      color='blue', label='Velocity (m/sec)')
    line2, = ax2.plot(x, y_acceleration, 's-', markersize=2, linewidth=1,
                      color='orange', label='Acceleration (m/sec²)')
    line3, = ax3.plot(x, y_jerk, '^-', markersize=2, linewidth=1,
                      color='green', label='Jerk (m/sec³)')

    # Configure subplots
    ax1.set_ylabel('Velocity (m/sec)')
    ax1.legend(loc='upper right')
    ax1.grid(True, alpha=0.3)
    ax1.axhline(y=0, color='black', linewidth=0.5, alpha=0.7)

    ax2.set_ylabel('Acceleration (m/sec²)')
    ax2.legend(loc='upper right')
    ax2.grid(True, alpha=0.3)
    ax2.axhline(y=0, color='black', linewidth=0.5, alpha=0.7)

    ax3.set_ylabel('Jerk (m/sec³)')
    ax3.set_xlabel('Time (arbitrary units)')
    ax3.legend(loc='upper right')
    ax3.grid(True, alpha=0.3)
    ax3.axhline(y=0, color='black', linewidth=0.5, alpha=0.7)

    # ==============================================
    # Figure 2: Single subplot figure
    # ==============================================
    fig2, ax4 = plt.subplots(1, 1, figsize=(12, 4))
    fig2.suptitle('Figure 2: Combined Data Signal', fontsize=14)

    # Manually share x-axis with ax1 from Figure 1 to synchronize zooming/panning across both figures
    # Note: sharex parameter in plt.subplots() doesn't work across different figures, so we must
    # call sharex() after creation
    ax4.sharex(ax1)

    # Plot combined data
    line4, = ax4.plot(x, y_combined, 'd-', markersize=2, linewidth=1.5,
                      color='red', label='Combined Signal')

    # Configure subplot
    ax4.set_ylabel('Combined Signal')
    ax4.set_xlabel('Time (arbitrary units)')
    ax4.legend(loc='upper right')
    ax4.grid(True, alpha=0.3)
    ax4.axhline(y=0, color='black', linewidth=0.5, alpha=0.7)

    # ==============================================
    # Create unified cursor system across both figures
    # ==============================================

    # Combine all axes and lines from both figures
    all_axes = [ax1, ax2, ax3, ax4]
    all_lines = [line1, line2, line3, line4]

    # [Sometimes required] Store the current axis limits before creating the cursor
    # - Since the x-limits are shared among all subplot axes, you only need to save and restore one
    ax1_xlim = ax1.get_xlim()

    # Create synchronized cursor across ALL subplots in BOTH figures
    unified_cursor = SnappingBlittedCursorMultipleSubplots(all_axes, all_lines)

    # Connect mouse events to both figures
    fig1.canvas.mpl_connect('motion_notify_event', unified_cursor.on_mouse_move)
    fig2.canvas.mpl_connect('motion_notify_event', unified_cursor.on_mouse_move)

    # [Sometimes required] Restore the original axis limits after cursor creation
    ax1.set_xlim(ax1_xlim)

    # ==============================================
    # Final layout and instructions
    # ==============================================

    # Adjust layouts
    fig1.tight_layout()
    fig1.subplots_adjust(bottom=0.08, top=0.92)  # Make room for suptitle and instructions

    fig2.tight_layout()
    fig2.subplots_adjust(bottom=0.15, top=0.85)   # Make room for suptitle and instructions

    # Add instructions to both figures
    fig1.text(0.5, 0.02,
              'Move mouse over ANY subplot in EITHER figure to see synchronized cursors across '
              'ALL plots',
              ha='center', fontsize=10, style='italic', weight='bold')

    fig2.text(0.5, 0.02,
              'Cursors synchronized with Figure 1 - Move mouse here or on Figure 1',
              ha='center', fontsize=10, style='italic', weight='bold')

    # Position figures side by side (if using interactive backend)
    try:
        # Try to position windows side by side
        mngr1 = fig1.canvas.manager
        mngr2 = fig2.canvas.manager
        mngr1.window.move(100, 100)    # Figure 1 on the left
        mngr2.window.move(1300, 100)   # Figure 2 on the right
    except:
        # If window positioning fails, just continue
        pass

    print("Created two linked figures:")
    print("- Figure 1: 3 subplots (velocity, acceleration, jerk)")
    print("- Figure 2: 1 subplot (combined signal)")
    print("Move mouse over any subplot to see synchronized cursors across ALL plots!")

    return unified_cursor


def main():
    # Keep references to cursor objects so they don't get garbage collected
    cursor1 = test_simple_cursor()
    cursor2 = test_blitted_cursor()
    cursor3 = test_snapping_cursor()
    cursor4 = test_snapping_blitted_cursor()
    cursor5 = test_snapping_blitted_cursor2()
    cursor6 = test_snapping_blitted_cursor_multiple_subplots()
    cursor7 = test_snapping_blitted_cursor_multiple_subplots_and_figures()
    plt.show()


if __name__ == "__main__":
    main()
