This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world


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


# Debugging notes

If the debugger fails to jump to the currently-executing line (PC, or "Program Counter") in your code when you pause (halt) the debugger, then try this:

1. While debugging, delete all breakpoints. 
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
