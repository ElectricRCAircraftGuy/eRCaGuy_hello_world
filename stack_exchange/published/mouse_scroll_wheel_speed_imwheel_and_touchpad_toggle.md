<!--
GS
1 June 2023

How to permanently fix scroll speed in Chrome, Sublime Text, Foxit PDF reader, and any other application you see fit

https://askubuntu.com/a/991680/327339
-->


## How to permanently fix scroll speed in Chrome, Sublime Text, Foxit PDF reader, and any other application you see fit

#### New answer:

- Update 2020: just use this script from my repo here and be done: [eRCaGuy_dotfiles...`touchpad_toggle.sh`][1]
- Update Dec. 2022: the script now handles Ubuntu 22.04 as well, and both the X11 and Wayland window manager servers.

_Tested 1 June 2023 on a brand new Ubuntu 22.04 install:_

```bash
# 1. Install the imwheel dependency
sudo apt update
sudo apt install imwheel

# 2. Install my configuration file

# Get my whole repo, and symlink the .imwheelrc config
# file to your home dir
git clone https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles.git
cd eRCaGuy_dotfiles/home
ln -si "${PWD}/.imwheelrc" ~

# 3. Get my touchpad toggle script too
mkdir -p ~/bin
cd ../useful_scripts
ln -si "${PWD}/touchpad_toggle.sh" ~/bin/gs_touchpad_toggle
# re-source your ~/.profile bash profile to automatically add ~/bin to your PATH
. ~/.profile

# 4. test it
# Note: if the imwheel mouse scroll speed settings don't properly toggle, first
# log out of Ubuntu and log back in, or reboot, and they should work now.
gs_touchpad_toggle  # toggle touchpad off, and imwheel on
gs_touchpad_toggle  # toggle touchpad back on again, and imwheel back off
```

Now follow my instructions (originally from the top of the [`touchpad_toggle.sh`][1] file) to disable the touchpad at boot, and to add the `Ctrl` + `Alt` + `P` shortcut to toggle the touchpad on and off: 

1. Create a custom keyboard shortcut to associate `Ctrl` + `Alt` + `P` with the touchpad toggle script. 
    1. In Ubuntu 22.04, for instance, adding custom keyboard shortcuts is found in Settings --> Keyboard --> "Keyboard Shortcuts" section at the bottom --> "View and Customize Shortcuts" --> "Custom Shortcuts" at the bottom --> click "Add Shortcut". Name it "Touchpad Toggle", give it the command "gs_touchpad_toggle", and associate it with the Ctrl + Alt + P keyboard shortcut. Click the "Add" button when done. 
        1. Test this shortcut now to ensure it works! If it doesn't work, log out of Ubuntu and log back in, or reboot, then test the shortcut again and it should now work.
1. Edit the Startup Applications GUI tool to add a startup call to toggle the touchpad OFF with every boot: press Windows (Super) key --> search for "Startup Applications", and open it --> click "Add" to create a new entry --> Name it "disable touchpad (Ctrl + Alt + P)", enter `gs_touchpad_toggle --off` for the "Command", and "found in ~/bin" for the "Comment." Click "Add" to save this new entry, then "Close". 
1. Done! 
    1. Your Touchpad and Touchscreen will automatically become DISABLED at every boot! 
    1. To toggle it on/off manually, use the Ctrl + Alt + P shortcut you set up. 
    1. This is very useful to quickly swap between using an external mouse vs the built-in touchpad or touchscreen, and it solves the mouse wheel scroll speed simultaneously too. 
    1. The reason we need `imwheel` to be *disabled* whenever the touchpad is *enabled* is because it interferes with the scrolling ability of the touchpad otherwise, breaking two-finger touchpad scrolling. So, the idea is that when the touchpad is disabled, you should use your external mouse, and its scroll wheel should work well, and when the touchpad is enabled, you should use your touchpad, and two-finger touchpad scrolling should work well.


---

#### Original answer:

(Try this to gain more insight, or if you need to try to manually fix things if the above steps don't work).

Here is a solution which works perfectly (tested recently in Ubuntu 14.04, 18.04, and 20.04):

```bash
sudo apt update
sudo apt install imwheel
gedit ~/.imwheelrc
```

Copy and paste the following into the newly-created `.imwheelrc` file (that you just made in your home directory via the `gedit` command above):

```bash
".*-chrome*"
None,      Up,   Button4, 3
None,      Down, Button5, 3
Control_L, Up,   Control_L|Button4
Control_L, Down, Control_L|Button5
Shift_L,   Up,   Shift_L|Button4
Shift_L,   Down, Shift_L|Button5
```

`3` is the "scroll speed multiplier." Use a larger number for faster scrolling, or a smaller number for slower scrolling. The `".*-chrome*"` part says to apply these scroll wheel speed increase changes ONLY to chrome.

Run `imwheel -b "4 5"` to test your settings. When done testing, run `killall imwheel` to kill it, then make your edits to `.imwheelrc`, as desired, and run `imwheel -b "4 5"` again for more testing. Be sure to fully close and re-open Chrome each time you restart `imwheel` too, to ensure its new settings take effect. This must be done by right-clicking the little Chrome icon in the top-right of your desktop pane and going to "Exit". 

*Also keep in mind that if you are using a cheap mouse, your scroll wheel decoder may be lousy and miss encoder counts when moving the wheel fast. Therefore, in such a case, move the wheel at a reduced speed when testing the effect of imwheel, so that your mouse doesn't miss encoder counts on the scroll wheel, making you think imwheel isn't working right when it's really just your cheap hardware's problem.*

**Add `imwheel -b "4 5"` to Ubuntu's "Startup Applications" to get it to run every time the computer starts.** 

[As Steven C. Howell says here][2]:

> Note that using the option `-b "4 5"` restricts imwheel to only affect the scroll wheel, discussed [here](https://askubuntu.com/a/514466/195243). 

Another answer by "tvn" here: https://askubuntu.com/a/304653/327339.  
More answers here: https://askubuntu.com/questions/285689/increase-mouse-wheel-scroll-speed.  

### Reference notes: 

I am not the original author of the answers linked-to above, rather, user "tvn" and others are, although tvn's answer is lacking in that it replaces mouse scroll wheel movements with multiple arrow-key <kbd>Arrow Up</kbd> and <kbd>Arrow Down</kbd> key presses, which means you have to click in a window for it to take effect, and some things like the browser-based [Jupyter Notebook][3] Python programming environment scroll *horribly* like this! Therefore, [Steven C. Howell][2] gave an improved answer which keeps the scroll wheel mapping to the scroll wheel, instead of to keyboard up and down keys, but his answer is lacking in that it applies this new scroll wheel scaling to *everything* on your computer, so I just modified this answer 27 Aug. 2018 to reflect Steven Howell's answer, but with the *addition* of adding `".*-chrome*"` to the top of the `~/.imwheelrc` file so that these new scroll setting apply only to your Chrome browser, which is really what I want. Note also, I have made several significant and important edits and contributions to tvn's answer linked to above, but now I think this answer here is much better, and it's deviated too much from tvn's answer to even attempt to edit his answer further.

Tested in **Ubuntu 14.04 LTS**.

Update 3 Mar. 2019: tested in **Ubuntu 18.04 LTS** as well, and it seems the effect takes place immediately in Chrome now each time you run `killall imwheel` and then `imwheel -b "4 5"` to test new settings.


## Help, my touchpad/trackpad is glitchy when scrolling!
- This section added 22 June 2019:

Depending on your computer and hardware, the above settings *may* work best with a mouse with a scroll wheel. On a track pad (again, this may or may not apply to you or your computer) it *may* make the result **very glitchy when trying to do two-finger scrolling on the touch pad**. I have a shortcut key (<kbd>Ctrl</kbd> + <kbd>Alt</kbd> + <kbd>P</kbd>) set up to run a script which enables/disables my track pad so I don't bump it while typing and using a mouse, yet so I can still easily enable it for when I don't have a mouse and/or someone else who loves touch pads wants to use my computer. To fix the glitchy scrolling caused by `imwheel` when using the touchpad, I've just added the following to my script:

When the touchpad is *disabled*, *enable* imwheel so my mouse scroll wheel will work well:
```bash
imwheel -b "4 5"
```

When the touchpad is *enabled*, *disable* imwheel so my touchpad two-finger scrolling will work well and not be glitchy:
```bash
killall imwheel
```
Doing the above is *especially important* for my HP Spectre x360 Ultrabook (Model 13-4193nr, and running Ubuntu 18.04), which otherwise has *horribly glitchy* two-finger touchpad scrolling when `imwheel` is enabled.

Here is **my full touchpad toggle script** with those 2 imwheel lines added as described just above: 

File "**~/bin/toggle_touchpad**":   
(I keep the latest version updated here: [eRCaGuy_dotfiles/.../touchpad_toggle.sh][1]).

```bash
#!/bin/bash

# GS_toggle_touchpad.sh
# - toggle the touchpad on and off

# Gabriel Staples
# Written: 2 Apr. 2018 
# Updated: 12 Sept. 2019 

# References:
# - https://askubuntu.com/a/874865/327339
# - https://askubuntu.com/questions/844151/enable-disable-touchpad/1109515#1109515

# Search for id number of "TouchPad" OR "Touchpad" in `xinput` list; manually type `xinput` to see all your devices
read TouchPadDeviceId <<< $( xinput | sed -nre '/TouchPad|Touchpad/s/.*id=([0-9]*).*/\1/p' ) 

state=$( xinput list-props "$TouchPadDeviceId" | grep "Device Enabled" | grep -o "[01]$" )

echo "TouchPadDeviceId = $TouchPadDeviceId"
echo "state = $state"

if [ "$state" -eq '1' ];then
    xinput --disable "$TouchPadDeviceId"
    zenity --info --text "Touchpad DISABLED" --timeout=2
    imwheel -b "4 5"
else
    xinput --enable "$TouchPadDeviceId"
    zenity --info --text "Touchpad ENABLED" --timeout=2
    killall imwheel
fi
```

Touchpad toggle script source: https://askubuntu.com/questions/844151/enable-disable-touchpad/1109515#1109515

Now just run `toggle_touchpad` from the command line, or associate it with a keyboard shortcut like <kbd>Ctrl</kbd> + <kbd>Alt</kbd> + <kbd>P</kbd> like I have.


## References:
1. Get the latest version of this script from my repo here! [eRCaGuy_dotfiles...touchpad_toggle.sh][1]
1. https://askubuntu.com/questions/844151/enable-disable-touchpad/1109515#1109515
1. For new entries to fix scroll speed for **Slack** and **Sublime Text 3** as well, see [my latest **~/.imwheelrc** file in my project here][4], and see also my new answer here answer: [How do I change the mouse wheel scroll speed in Sublime Text 3?](https://stackoverflow.com/a/64289511/4561887).
1. My answer on disabling the trackpad in Ubuntu 22.04: [How to enable/disable the touchpad in Ubuntu 22.04 from the command-line](https://askubuntu.com/a/1446479/327339)


## Known bugs/issues:
- [AMAZON PLEASE FIX THIS!] Amazon designed their website with your _discomfort_ in mind, and their website is extremely slow and glitchy when using the above fix. I haven't noticed a single issue with this fix _except on Amazon.com_. So, when using Amazon, you might want to just use Firefox, or temporarily disable imwheel with the <kbd>Ctrl</kbd> + <kbd>Alt</kbd> + <kbd>P</kbd> shortcut I helped you set up above.
    - Amazon, why are you so lousy?
    - Note: the behavior is that after scrolling with the mouse wheel on Amazon.com, while imwheel is enabled, you may see: 
        1. you cannot click on any links for a few seconds after you stop scrolling 
        1. images take a long time to load
        1. CPU usage on Amazon webpages is **extremely high**. See the Chrome Task Manager to see tabs or pages using lots of CPU time. Open the Chrome Task Manager with <kbd>Shift</kbd> + <kbd>Esc</kbd>, or by going to the 3 dots in the top-right of Chrome --> "More tools" --> "Task manager".



  [1]: https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles/blob/master/useful_scripts/touchpad_toggle.sh
  [2]: https://askubuntu.com/a/621140/327339
  [3]: http://jupyter.org/
  [4]: https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles/blob/master/home/.imwheelrc
