<!--
GS
2022-2023

https://askubuntu.com/a/1446690/327339
-->

I have discovered how to install and use **two really good Gnome extensions for this**:

1. [**Awesome Tiles**](https://extensions.gnome.org/extension/4702/awesome-tiles/)
    
    Allows window snapping via shortcut keys, just like "Compiz" in Unity in Ubuntu 14.04 and 16.04, and ["Put Windows"](https://askubuntu.com/a/1089033/327339) in Gnome in Ubuntu 18.04 and 20.04.

1. [**WinTile**](https://extensions.gnome.org/extension/1723/wintile-windows-10-window-tiling-for-gnome/) (generally newer and more feature-rich, but [may be buggier and less-usable](https://github.com/Fmstrat/wintile/issues?q=is%3Aissue+author%3AElectricRCAircraftGuy+)) and [**WinTile Reloaded**](https://github.com/ElectricRCAircraftGuy/wintile-reloaded) (a dead WinTile fork with various bug fixes, but more-usable and what I generally use)
    
    Allows resizing, tiling, and snapping windows just by dragging them to the edges or corners of a screen--same as in modern versions of Windows apparently. Very useful and fast for mouse users. Tested and works in Ubuntu 18.04, 20.04, and 22.04.
    
    WinTile also adds to Ubuntu's Gnome window manager the shortcut sequence described in [@Bruni's answer](https://askubuntu.com/a/1464475/327339) for Kubuntu, which Ubuntu doesn't otherwise have, namely:

    > To snap to the top-left corner, for instance: <kbd>Super</kbd> + <kbd>left Arrow</kbd> and then <kbd>Super</kbd> + <kbd>upper Arrow</kbd>

I like to use *both* of the above extensions simultaneously. I've tested _both_ of them in Ubuntu 22.04 with both the X11 and Wayland window manager servers, and both extensions work in both cases.


## Extension 1: Awesome Tiles (uses keyboard shortcuts to resize and snap windows to edges and corners)

_Tested in Ubuntu 22.04 with both the X11 and Wayland window manager servers._

Due to a [known bug in Ubuntu 22.04](https://askubuntu.com/a/1419146/327339), you can _not_ install "Awesome Tiles" from the browser here: https://extensions.gnome.org/. Instead, install it from the `gnome-shell-extension-manager`:

```bash
# install it
sudo apt update
sudo apt install gnome-shell-extension-manager
```

Open its GUI by pressing the <kbd>Windows</kbd> key and typing "Extension Manager". Its icon is a blue puzzle piece:

[![enter image description here][1]][1]

Click the "Browse" tab at the top, then search for "awesome tiles". Click the "Install" button to install it. Here you can see mine is already "Installed":

[![enter image description here][2]][2]

Click the "Installed" tab at the top, ensure the slider shows "Awesome Tiles" as activated (click the slider to activate/deactivate it), then click the gear icon to modify its settings:

[![enter image description here][3]][3]

Here are the default settings and shortcut keys it uses:

[![enter image description here][4]][4]

As you can see, it uses the <kbd>Super</kbd> (<kbd>Windows</kbd>) key + the keypad keys. A lot of smaller laptops and keyboards, however, do not have the keypad on the right side of the keyboard, so I recommend you use the <kbd>Alt</kbd> + <kbd>Windows</kbd> + Letters shortcuts which [I've used in "Put Windows" before](https://askubuntu.com/a/1089033/327339). Also, I really hate the gaps all around the windows (like _a lot_--so much so that I woulnd't recommend this tool _at all_ if I couldn't remove them), so I recommend you remove the gaps by changing "Gap Between Window and Workspace" to 0, and disabling "Gaps Between Windows". 

But, before we can add all of the shortcuts I like, we have to disable the default Ubuntu <kbd>Alt</kbd> + <kbd>Windows</kbd> + <kbd>S</kbd> "screen reader on or off" shortcut, which interferes. Go to your Ubuntu Settings --> Keyboard --> click "View and Customize Shortcuts" --> type in "alt+super+s", as shown here:

[![enter image description here][5]][5]

Click the "Turn screen reader on or off" shortcut you can see which is currently assigned to `Alt+Super+S`, and press <kbd>Backspace</kbd> to disable the shortcut --> click the "Set" button. You can now see it is "Disabled". Perfect:

[![enter image description here][6]][6]

Now go ahead and change your "Awesome Tiles" keyboard shortcuts to be as follows. Remember that the <kbd>Super</kbd> key is the <kbd>Windows</kbd> key on a PC. Here are my new settings. I have highlighted all of the ones I just changed:

[![enter image description here][7]][7]

Update: I just changed this too: I changed 0.35 -> 0.33, and I added 0.25:  
[![enter image description here][8]][8]

**If you ever want to reset all of the settings to their defaults, see my answer here: [How do I reset a Gnome Extension's settings to default? Ex: for "Awesome Tiles" in Ubuntu 22.04?](https://askubuntu.com/a/1446833/327339).**

Two other settings you may want to mess with are the "Center Tiling Steps" and "Side Tiling Steps". If you press the same shortcut repeatedly, it cycles through those multiple size settings as set there. Those are values from 0 to 1, where `0` represents 0% of the full size for that position, and `1` represents the full size for that position, So, press the same shortcut repeatedly to cycle through 3 (as currently set) different sizes for each one, sized according to those settings. 

To get the most consistent results, I like to tile the window to center first. So, if I wanted to resize and snap the window to the top-left corner, I would press first <kbd>Alt</kbd> + <kbd>Windows</kbd> + <kbd>S</kbd> to center the window, and then I'd press <kbd>Alt</kbd> + <kbd>Windows</kbd> + <kbd>Q</kbd> to resize and snap it to the top-left. Centering between each move ensures it's always the correct size for that new position.

That's it! This is an _excellent_ extension to use keyboard shortcuts to resize and snap your windows to edges and corners!


## Extension 2: WinTile (allows you to drag with the mouse your windows to resize and snap them to left, right, or corners)

Note: WinTile also adds the ability to snap to corners with the keyboard using <kbd>Super</kbd> + <kbd>left Arrow</kbd> and then <kbd>Super</kbd> + <kbd>upper Arrow</kbd>, for instance.

_Tested in Ubuntu 22.04 with both the X11 and Wayland window manager servers, and in Ubuntu 18.04 and 20.04 with X11._
 
**If in a hurry, just jump straight down to the "Install WinTile" section below. It's just a few short steps.**

**As of 3 July 2023 it is now up-to-date with the necessary bug-fixes it was missing for a few years, and you no longer have to install [WinTile Reloaded](https://github.com/ElectricRCAircraftGuy/wintile-reloaded)!**

The [**WinTile** tool](https://extensions.gnome.org/extension/1723/wintile-windows-10-window-tiling-for-gnome/) works phenomenally-well in Ubuntu 22.04, with both the X _and_ Wayland window manager servers, and easily snaps windows into corners or edges.

It takes some getting used-to compared to the tools I've been using for the past 8 years: CompizConfig in Unity in Ubuntu 14.04 and 16.04 and the ["Put Windows"](https://askubuntu.com/a/1089033/327339) tool in GNOME in Ubuntu 18.04 and 20.04, but overall it gives a more-natural experience if you're using a mouse. Just drag the window towards the monitor edge or towards the corner and it automatically resizes and snaps accordingly! [Here is an animated gif](https://github.com/Fmstrat/wintile/raw/master/demo.gif) from the GitHub page: https://github.com/Fmstrat/wintile: 

[![enter image description here][9]][9]

Here is the main WinTile repo: https://github.com/Fmstrat/wintile. 

#### Install WinTile from the Gnome Extension Manager

_Note: to see my old "WinTile Reloaded" installation instructions instead, see this older version of this answer here: <https://askubuntu.com/revisions/1446690/19>._

Press your Windows key and search for "Extension Manager". As of Ubuntu 22.04, it's a blue puzzle piece, as previously shown above. Click it. Click the "Browse" tab at the top, then search for "wintile". Click the "Install" button to install it. Here you can see mine is already "Installed":

[![enter image description here][10]][10]

Click the "Installed" tab at the top, ensure the slider shows "WinTile" as activated (click the slider to activate/deactivate it). If you have previously installed WinTile Reloaded and it is still active, disable it by clicking its slider to turn it off. Here's what I see:

[![enter image description here][11]][11]

Click the gear icon next to it now to configure settings. 

#### Two other ways to enable/disable Gnome Extensions: 1) from your browser, 2) from the command line

1. You can also activate extensions from the webpage if desired. Run this so that Chrome can be used to configure your local Gnome extensions:
    ```bash
    sudo apt install chrome-gnome-shell
    ```

    Now, open your Gnome Extension web-page _in Chrome_, as a portal into your locally-running Gnome extensions server: https://extensions.gnome.org/local/

    You'll now see "WinTile" as an option! (note: this is an old image showing "WinTile RELOADED" instead):

    [![enter image description here][12]][12]

    To activate it, you can either click the toggle button from "OFF" to "ON" in that extension webpage (you _must_ do it in this way in Ubuntu 18.04, and you _can_ do it this way in Ubuntu 20.04 or 22.04). 

1. A 3rd way to activate the extension is via the terminal:
    ```bash
    # enable it as a Gnome Extension (this cmd works in Ubuntu 20.04 and 22.04,
    # but not in 18.04; for 18.04 you must manually click to enable the 
    # extension, as described just above)
    gnome-extensions enable wintile@nowsci.com

    # disable the no-longer-needed WinTile Reloaded
    gnome-extensions disable wintile-reloaded@jaajeur.xyz

    # See a list of all gnome-shell extensions you can enable/disable like this
    ls -1 ~/.local/share/gnome-shell/extensions/ | grep '@'
    ```

    If you run the terminal command, you'll see the toggle update live in the browser window.

That's it! Drag windows to the corners of your monitor to your heart's content. 

#### WinTile Configuration options

There are two ways to change the settings:
1. Option 1: via the browser:
    1. Go here: https://extensions.gnome.org/local/
    1. Under the "Installed Extensions" heading, look for <s>"WinTile RELOADED"</s> "WinTile":
        [![enter image description here][12]][12]
    1. Click the little tool (blue screwdriver and wrench) icon: [![enter image description here][13]][13]
1. Option 2 [my preference]: via the `gnome-shell-extension-manager` GUI that you should have installed as part of the "Extension 1" instructions above. 
    1. Press your <kbd>Super</kbd> (<kbd>Windows</kbd>) key, and type in "extensions". Open the "Extensions" tool:
        [![enter image description here][14]][14]
    1. Find "WinTile RELOADED" and click the round settings button, circled here:
        [![enter image description here][15]][15]

In both cases, the below settings window is opened. Here are the possible settings to tweak. **I decreased my "Delay in ms before preview displays" setting from the default 500ms to 100ms to make it much snappier,** and I **decreased my "Number of columns" setting from 3 to 2.**

[![enter image description here][16]][16]


I *love* this tool and use it *extensively*! 

Overall, it's not quite as versatile as "Put Windows" or "Awesome Tiles", but WinTile works great in Ubuntu 22.04, with both Wayland and X window servers, and it's more-intuitive for Windows users and those who like to use trackpads or mice 🖱. 

#### WinTile issues, and WinTile Reloaded references:
1. To see my old "WinTile Reloaded" installation instructions, see this older version of this answer here: https://askubuntu.com/revisions/1446690/19

1. https://github.com/Fmstrat/wintile/issues/81
1. https://github.com/Fmstrat/wintile/issues/91
1. https://github.com/Fmstrat/wintile/issues/168
1. https://github.com/Fmstrat/wintile/pull/82
    1. \*\*\*\*\* https://github.com/Fmstrat/wintile/pull/82#issuecomment-1236829893
    1. My comment: https://github.com/Fmstrat/wintile/pull/82#issuecomment-1358954979


## Graphics driver problems in Ubuntu 22.04?

This is kind of related if you just installed Ubuntu 22.04.

If you find your new 22.04 computer having graphics driver problems or freezing, and you have an NVIDIA graphics card, see my detailed answer here to update your graphics drivers. See: [(Recommended) Option 2: download and install the driver straight from NVIDIA](https://askubuntu.com/a/1446523/327339). 

See also my personal website article: [Common ways to fix video driver (and related) issues in Linux Ubuntu](https://gabrielstaples.com/common-ways-to-fix-linux-video-driver-issues/#gsc.tab=0).


## Problems with the Wayland window manager on your new Dell laptop?

1. See my answer here: [Wayland window manager causes my computer to stay on a black/blank screen and not wake up](https://askubuntu.com/a/1470563/327339).
1. See also my personal website article: [Common ways to fix video driver (and related) issues in Linux Ubuntu](https://gabrielstaples.com/common-ways-to-fix-linux-video-driver-issues/#gsc.tab=0).



  [1]: https://i.stack.imgur.com/G07UN.png
  [2]: https://i.stack.imgur.com/9uIeI.png
  [3]: https://i.stack.imgur.com/2KZOo.png
  [4]: https://i.stack.imgur.com/widZY.png
  [5]: https://i.stack.imgur.com/uGqDi.png
  [6]: https://i.stack.imgur.com/sZugC.png
  [7]: https://i.stack.imgur.com/KrFkO.png
  [8]: https://i.stack.imgur.com/XHMT4.png
  [9]: https://i.stack.imgur.com/uhXCU.gif
  [10]: https://i.stack.imgur.com/g2b5Q.png
  [11]: https://i.stack.imgur.com/jbSFJ.png
  [12]: https://i.stack.imgur.com/waX2x.png
  [13]: https://i.stack.imgur.com/rLCg3.png
  [14]: https://i.stack.imgur.com/pj3Vc.png
  [15]: https://i.stack.imgur.com/EIb2U.png
  [16]: https://i.stack.imgur.com/koD0R.png
