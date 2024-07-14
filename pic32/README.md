This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world


# See also

1. My work: https://github.com/ElectricRCAircraftGuy/eRCaGuy_Engineering/blob/main/Datasheets/Microchip/README_exceptions_and_handlers.md
1. My work: https://github.com/ElectricRCAircraftGuy/eRCaGuy_Engineering/blob/main/Datasheets/Microchip/PIC32MZ2048EFM144/exception_handlers.c
1. My answer: [How to configure a `preBuildSteps.sh` Bash script that runs as part of the pre-build process in the MPLAB X IDE on both Windows and Linux](https://stackoverflow.com/a/78485243/4561887)
1. My notes on how to remotely power cycle USB devices, such as the [PICKit 5](https://www.microchip.com/en-us/development-tool/pg164150) debugger: https://github.com/ElectricRCAircraftGuy/eRCaGuy_Engineering/tree/main/USB_Managed_Hubs/CG-10PU3MGD_managed_USB_hub
    1. See the "PICKit 5 debugger notes" section here too!
1. Device Configuration Registers: https://developerhelp.microchip.com/xwiki/bin/view/products/mcu-mpu/32bit-mcu/PIC32/configuration-registers/
    1. For 32mz2048efm144: HTML: [root/opt/microchip/xc32/v4.45/docs/config_docs/32mz2048efm144.html](root/opt/microchip/xc32/v4.45/docs/config_docs/32mz2048efm144.html)
    1. For 32mz2048efm144: PDF: [root/opt/microchip/xc32/v4.45/docs/config_docs/32mz2048efm144--Config-Bit Settings for PIC32MZ2048EFM144.pdf](<root/opt/microchip/xc32/v4.45/docs/config_docs/32mz2048efm144--Config-Bit Settings for PIC32MZ2048EFM144.pdf>)


# Microchip MPLAB X IDE notes, including license manager (`xclm`) issues

See also my personal (not shared) notes here: [Microchip (& Atmel) MPLAB X IDE for PIC mcus et al configuration and setup info](https://docs.google.com/document/d/1fzDxL7aJk8aQDf5d6zT39GE9GySWb7lOfG7v8Dn93fI/edit).

1. To build the XC32 compiler from source in either Windows (using MSYS2) or Linux, see my repo here: https://github.com/ElectricRCAircraftGuy/Microchip_XC32_Compiler.
1. Your paid XC32 Pro license is located here: `/opt/microchip/xclm/license/microchip-1.lic`.

1. [This probably *is* needed] In MPLAB X IDE under Tools --> Licenses --> Change Licensing Type, if you see any little warning that says `xclm can not be configured without setuid root.`, then it means you need to force it to run as root by setting the owner, and possibly the setuid bit too, as shown below. If you do _not_ do this fix, **you will be blocked from specifying the XC32 "Network" license Server Address and Port**. So, here is how to fix that:

    ```bash
    # see what it looks like first
    ll /opt/microchip/xc32/v1.42/bin/xclm

    # set the owner to root, while leaving the group alone
    sudo chown root /opt/microchip/xc32/v1.42/bin/xclm

    # see what it looks like now
    ll /opt/microchip/xc32/v1.42/bin/xclm
    ```

    You'll see: 
    ```
    -rwxrwxr-x  1 root           myusername 7582952 Dec 25 20:21 xclm*
    ```
    
    Now close and re-open MPLAB X IDE and the warning should be gone. That was my case at least! If so, skip the next command.
    
    If the warning is still there when you go to Tools --> Licenses --> Change Licensing Type, however, then also do this:
    
    ```bash
    # set the setuid (`u+s`) bit so that no matter who runs it, it always runs as the owner (root)
    sudo chmod u+s /opt/microchip/xc32/v1.42/bin/xclm

    # see what it looks like now
    ll /opt/microchip/xc32/v1.42/bin/xclm
    ```

1. [This probably isn't needed, but you can play with this in case it helps] The XC32 compiler license manager (`xclm`) executable is located here, for instance: `/opt/microchip/xc32/v4.35/bin/xclm`. 

    The `xclm` version that comes with v4.35 of the compiler is version 3.14, as can be seen when you open MPLAB X IDE and go to Tools --> Licenses --> Change Licensing Type --> select "XC32 (v4.35)" in the left-hand pane --> you'll see the "xclm path" at the top of the window, the "xclm version" underneath that, and under the "License status" section farther below, you'll see the xclm version there too. 

    Since the license manager is packaged with the compiler, you can "upgrade" your xclm license manager simply by installing a later version of the compiler, then copying its `xclm` executable in place of the old one. 

    Ex: (use `sudo` only if needed):
    ```bash
    # back up the old xclm executable
    mv /opt/microchip/xc32/v1.42/bin/xclm /opt/microchip/xc32/v1.42/bin/xclm.bak
    # copy the new xclm executable from the new compiler version
    cp /opt/microchip/xc32/v4.35/bin/xclm /opt/microchip/xc32/v1.42/bin/xclm
    ```


# Example `.gitignore` file for your `myProject.X` MPLAB X project directory

```bash
# Ignore MPLAB X-generated and auto-edited files, like they recommend here:
# https://microchipdeveloper.com/mplabx:version-control-working-with
#
# See also: https://microchipdeveloper.com/mplabx:work-outside-create-makefiles-info
# 
# > We recommend that you do not commit these nbproject/Makefile* files into revision control. 
# > Instead use the IDE or prjMakefilesGenerator to reproduce them as needed. For more 
# > information, see Working with Version Control Systems:
# > https://microchipdeveloper.com/mplabx:version-control-working-with
# 
/.generated_files/
/build/
/dist/
/nbproject/Makefile-*
/nbproject/Package-*
/nbproject/private/
/private/

# other dirs
/debug/
```


# See also

1. My answer: [Electronics Stack Exchange: How to renew your paid Microchip XC32 Compiler Pro license when it has expired or is about to expire](https://electronics.stackexchange.com/a/695772/26234)
1. My answer: [How do I make my Microchip MPLAB X IDE project use the free version of the XC32 compiler?](https://electronics.stackexchange.com/a/696172/26234)
1. [Microchip: How to obtain a license file](https://onlinedocs.microchip.com/oxy/GUID-7A7E8B19-1D3A-4880-88ED-ACA262E1EB09-en-US-1/GUID-4F00D32A-941E-4E46-8CA4-31B1FF3A334C.html)


# My ritualistic [superstitious] guaranteed clean build process in the MPLAB X IDE

This is required each time you do a `git checkout` to a new branch where any project configuration settings (found in `MyProject.X/nbproject/configurations.xml`) have changed, for example. 

If you do a `git checkout` and change branches where any project configuration files have changed, the IDE will not pick them up. It only reads new settings on project open, or when you change them in the IDE directly, _not_ when you change them from the command-line, nor when doing a `git checkout` or editing them via a file editor.

1. Delete all breakpoints in the Breakpoints (<kbd>Alt</kbd>+<kbd>Shift</kbd>+<kbd>5</kbd>) tab. 
1. Close the project.
1. Close the IDE.
1. `git reset --hard`. WARNING: will cause permanent loss of any uncommitted changes in any tracked files!
1. `git clean -fd`. WARNING: will cause permanent loss of any uncommitted changes in any untracked files!
1. `git checkout my_branch_to_debug`
1. `git clean -fd`. WARNING: will cause permanent loss of any uncommitted changes in any untracked files!
1. [`git rm_ignored_files`](https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles/blob/master/useful_scripts/git-rm_ignored_files.sh)
    1. Then chose `Y`es to delete ignored files. 
1. `prjMakefilesGenerator MyProject.X`
1. Re-open the IDE.
1. Re-open the project.
1. Right-click the project --> "Set as Main Project".
1. Click the "Clean and Build Project" button (is in a dropdown from the button called "Clean and Build for Debugging Project" unless you've added this button explicitly).

Now, you are guaranteed to get a clean build so long as your `.gitignore` file is set up correctly (as described above) and ignores all build output.


# Debugging notes


## See also
1. [../FreeRTOS/README.md](../FreeRTOS/README.md)


## References
1. https://developerhelp.microchip.com/xwiki/bin/view/software-tools/programmers-and-debuggers/archive/realice/ - MPLAB® REAL ICE™ In-Circuit Emulator (DV244005) [this programmer/debugger is no longer available]


## Notes

If the debugger fails to jump to the currently-executing line (PC, or "Program Counter") in your code when you pause (halt) the debugger, then try the following. 

See also the "Troubleshooting Q&A" section below for things to try. 

1. Delete all breakpoints. 

    To get to the "Breakpoints" tab/window, either:
    1. Be in debug mode, or 
    1. Click Window --> Debugging --> Breakpoints (<kbd>Alt</kbd>+<kbd>Shift</kbd>+<kbd>5</kbd>)

    Then, right-click in the "Breakpoints" Window --> and click "Delete All" to delete all breakpoints. 

    ALL BREAKPOINTS MUST BE CLEARED BEFORE STARTING, OR ELSE AN INVALID BREAKPOINT LEFT OVER FROM A PREVIOUS DEBUG SESSION, ESPECIALLY WHEN POINTING TO **CODE WHICH NO LONGER EXISTS**, OR **MACROS WHICH ARE NO LONGER DEFINED OR TRUE**, CAN CAUSE STRANGE DEBUGGER ERRORS! 

    Example debugger errors when a breakpoint is set to a macro which is no longer defined or which defines a compile-time code block which is no longer entered:

    ```
    Running
    Reception on endpoint 3 failed (err = -121)
    ```

    Or:
    ```
    Halting...

    MPLAB has gotten out of synch with the REAL ICE. Please unplug and reconnect the 
    REAL ICE to the USB cable and try the operation again. 
    ```

1. Ensure you have the main project selected in the "Projects" window/tab at the top-left before you click the "Debug Project" button. 

    If you have the bootloader project selected, then the debugger will not work properly, and you will inadvertently load and debug just the bootloader project instead of the unified build of the bootloader+main project. 

1. Close the bootloader project and main project (assuming you were doing a unified build). 
1. Close the IDE. 
1. Run [`git rm_ignored_files`](https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles/blob/master/useful_scripts/git-rm_ignored_files.sh) to delete all `.gitignore`-ed files.
1. Ensure `git status` is clean in the main project. Delete or clean up any files as needed to make it clean. 
1. Run `prjMakefilesGenerator MyProject.X/` to regenerate the Makefiles.
1. Check `git status` again and make sure it looks as expected. 
1. Re-open the IDE. 
1. Re-open the bootloader project and main project.
1. Check `git status` and make sure there are no new changes. 
1. Re-configure the unified build settings. In the project settings for the main project:
    1. In the primary configuration setting, choose the ICE/debugger from the "Connected Hardware Tool" dropdown menu. 
    1. Under "Loading", check the box for "Load symbols when programming or building for production (slows process)", and click the "Add Loadable Project..." button and add the bootloader project to the main code project. 
    1. Under "XC32 (Global Options)" --> "xc32-ld" --> "Option categories" dropdown --> "Symbols & Macros" --> "Symbols" dropdown --> choose "Keep all" [for the debugging info].
1. Check `git status` again and make sure all changes are as expected.
1. Re-build the project.
1. Click the "Debug Project" button to start debugging.
1. Click the Pause (Halt) button to stop the debugger. After 4 or 5 seconds it should now stop on the line where it is executing, highlighting it in green! 
    1. Each time you continue and then pause the debugger again, it should automatically jump to and highlight in green the currently-executing line!
1. Done! The debugger is working again!


## Troubleshooting Q&A

#### If your debugger loses connection, and you are repeatedly getting this "Connection Failed" error:

> *****************************************************  
> Reception on endpoint 1 failed (err = -10121)  
> Connection Failed.  
> If the problem persists, please disconnect and reconnect the REAL ICE to the USB cable. If this does not fix the problem verify that the proper MPLAB X USB drivers have been installed.  

Then unplug and plug back in the large USB-B connector which plugs into the ICE programmer/debugger/emulator, from your computer. 

If you are remote, and cannot do this, then you can buy one of these remotely-controllable USB hubs for $175: [recommended!] https://www.usbgear.com/cg-10pu3mgd.html. 


[No-cost solution] Alternatively: 

1. Download `UsbTreeView.exe` for free from here: https://usb-device-tree-viewer.en.lo4d.com/windows
1. Right click it and run it as an admin. 
1. Find the ICE programmer as "Microchip WinUSB Device" in the list. 
1. Right-click the USB controller it is on (such as `Intel(R) USB 3.1 eXtensible Host Controller - 1.10 (Microsoft) - USB xHCI Compliant Host Controller`), and click "Restart Device", as shown here:

    <p align="left" width="100%">
        <a href="https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/assets/6842199/485b7edf-2202-49b9-8d51-968cf624cea9">
            <img width="75%" src="https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/assets/6842199/485b7edf-2202-49b9-8d51-968cf624cea9"> 
        </a>
    </p>

1. Watch the status bar at the very bottom of the USB Device Tree Viewer window to ensure it says it was successful.
1. Back in the MPLAB X IDE (ex: v6.20) click the green circular arrows in the bottom-left window to "Refresh Debug Tool Status":

    [![](https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/assets/6842199/60f6b7e2-8625-4e7a-b26e-ef78cc3daf0e)](https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/assets/6842199/60f6b7e2-8625-4e7a-b26e-ef78cc3daf0e)

1. In the "Output" window, you should now see a good debug tool status message, such as this shown below, instead of the error message shown above: 

    ```
    *****************************************************

    Connecting to MPLAB REAL ICE...

    Currently loaded firmware on REAL ICE
    Firmware Suite Version.....01.56.10
    Firmware type..............PIC32MZ

    Target voltage detected
    Target device PIC32MZ2048EFM144 found.
    Device ID Revision = B2
    DEVSN0 = 012345ab
    DEVSN1 = abcdef01
    ```

1. If you see the above message, the debugger is working again! You can now click the "Debug Project" button to start debugging again!


TODO: 

1. [ ] Try restarting the USB controller from the command line using `devcon` from the Windows Driver Kit (WDK) or Windows Driver Framework (WDF) as well. 

    Get `devcon.exe` as shown here: https://superuser.com/a/1099688/425838 --> see my comment under the answer. 

    According to GitHub copilot, you can then run it from the Windows Command Prompt *as admin* like this:

    ```bash
    # Show the status and device ID of all devices
    devcon status *

    # Show the device ID of all devices
    devcon find *

    # Restart the device with the given device ID
    devcon disable <DeviceID>
    devcon enable <DeviceID>

    # Example
    devcon disable "USB\VID_04D8&PID_0053"
    devcon enable "USB\VID_04D8&PID_0053"
    ```

#### Why did I end up inside an infinite `for` loop inside `_general_exception_handler()`? 

One cause of this is that you forgot to pass the size argument (argument 2) to [`snprintf()`](https://cplusplus.com/reference/cstdio/snprintf/). If this happens, then you may get a general exception at run-time!

To fix this, simply add `-Wall -Wextra -Werror` to your build flags and instead you'll get a compile-time error!

