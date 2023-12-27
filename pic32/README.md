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



