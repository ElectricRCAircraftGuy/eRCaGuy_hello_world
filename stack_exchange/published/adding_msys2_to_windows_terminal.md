<!--
GS
31 Oct. 2023

https://stackoverflow.com/q/71045716/4561887

MY ANSWER: https://stackoverflow.com/a/77407282/4561887
-->


## Setting up MSYS2 from scratch, including adding all 7 profiles to Windows Terminal

_Tested on the latest version of MSYS2, `msys2-x86_64-20231026.exe`, from https://www.msys2.org/, on Windows 11, on 31 Oct. 2023, as a spooky treat._

As a more beginner-friendly, thorough, and customized version of [@Weed Cookie's answer](https://stackoverflow.com/a/71171561/4561887), here are additional details I and other beginners are sure to need. 

Note that MSYS2 includes [MinGW-w64](https://www.mingw-w64.org/) and the Pacman package manager, and is a powerful, Linux-like terminal and GCC and LLVM (clang) build environment for Windows. It is akin to Cygwin, and similar to Git Bash from [Git for Windows](https://gitforwindows.org/). However, MSYS2 is optimized for _building software_, and for using Git [they recommend you install and use Git for Windows's Git Bash separately](https://www.msys2.org/docs/git/). So, you can think of MSYS2 as a native Windows build environment, and Git Bash as a native Windows git and developer environment. 

MSYS2 is kind of like a light version of Linux running inside Windows. As compared to WSL (Windows Subsystem for Linux), which _is_ Linux on Windows, MSYS2 has this huge caveat, however: from https://www.msys2.org/docs/what-is-msys2/ (emphasis added):

> MSYS2 allows you to **build native Windows programs**, while with WSL you can only cross compile them which makes things more complicated. 


## Description of *all 7* MSYS2 profiles to add to Windows Terminal

Here are the 7 MSYS2 shell/environment types:

1. `msys` and `msys2` (same thing now) - the base tool; all other environments below inherit from this one; contains the GCC 64-bit compiler and Cygwin C library
1. `mingw32` - Minimalist GNU for Windows 32-bit; contains GCC 32-bit compiler
1. `mingw64` - [Minimalist GNU for Windows 64-bit](https://en.wikipedia.org/wiki/Mingw-w64); contains GCC 64-bit compiler
1. `ucrt64` - [UCRT (Universal C Runtime](https://www.msys2.org/docs/environments/) 64-bit; contains GCC 64-bit compiler; MSYS2 [says](https://www.msys2.org/docs/environments/): "If you are unsure, go with UCRT64 [this one]."
1. `clang64` - contains the [LLVM/Clang](https://clang.llvm.org/) 64-bit compiler
1. `clang32` - contains the LLVM/Clang 32-bit compiler
1. `clangarm64` - contains the LLVM/Clang 64-bit ARM ([AArch64](https://en.wikipedia.org/wiki/AArch64)) compiler

From: https://www.msys2.org/docs/environments/:

[![enter image description here][1]][1]

Also from https://www.msys2.org/docs/environments/ (emphasis added): 

> MSYS2 comes with different environments and the first thing you have to decide is which one to use. The differences among the environments are mainly environment variables, default compilers/linkers, architecture, system libraries used etc. **If you are unsure, go with _UCRT64_.**
> 
> The **MSYS** environment...is always active. All the other environments inherit from the **MSYS** environment and add various things on top of it.
> 
> For example, in the **UCRT64** environment the `$PATH` variable starts with `/ucrt64/bin:/usr/bin` so you get all ucrt64 based tools as well as all msys tools.
> 
> The active environment is selected via the `MSYSTEM` environment variable. Setting `MSYSTEM` to `UCRT64` and starting a login shell will put you in that environment.

For details on **GCC vs LLVM/Clang** and **MSVCRT vs UCRT**, see here: https://www.msys2.org/docs/environments/. 

> **UCRT** (Universal C Runtime) is a newer version which is also used by Microsoft Visual Studio by default. It should work and behave as if the code was compiled with MSVC.
> 
> - It only ships by default on Windows 10 [or later]

Main references:
1. https://www.msys2.org/docs/what-is-msys2/

    > MSYS2 vs WSL  
    > 
    > MSYS2 allows you to build native Windows programs, while with WSL you can only cross compile them which makes things more complicated. 

1. https://www.msys2.org/docs/environments/ - very useful!

1. https://www.msys2.org/docs/who-is-using-msys2/

    > [Git for Windows](https://gitforwindows.org/) is based on MSYS2


## Setting up all 7 MSYS2 shells/environments to run in Windows Terminal

1. Download and install the latest version of MSYS2. 
    1. You can get it here: https://www.msys2.org/. 

1. Ensure Windows Terminal is installed. If you have Windows 11 or later, it's already installed. If you have Windows 10 or older, you'll need to manually install Windows Terminal from the Microsoft Store, here: https://apps.microsoft.com/detail/9N0DX20HK701?hl=en-zm&gl=ZM 

1. Open Windows PowerShell and run `New-Guid` _7 times_, one for each MSYS2 profile entry we will create below. Copy and paste the numbers out into a text editor. You'll need these numbers later. Example: here are my generated GUID numbers:
    ```
    6f0ee3d1-ac4f-48ca-bcf5-a9795f9942d2
    80414396-5ef4-490b-af88-29600c19ca4a
    aef16ae0-7dd1-4ac7-abd8-60a646abb9ca
    a718a3d5-9e77-4d0d-b7b6-69ec3d190206
    1f2869c0-1310-403b-93a7-9227f42eeb24
    10c96d8f-9e6b-48f6-8f59-034c586d7e57
    ada1f939-0f7b-400c-b755-8cbff4fd40a8
    ```

1. Open Windows Terminal, and add 7 new MSYS2 profile entries:

    Open Windows Terminal. 
    
    Then, click the little drop-down arrow at the top-right of the open tab, and select "Settings" --> in the Settings tab that opens up, click "Open JSON file" in the bottom-left, as shown here:
    
    [![enter image description here][2]][2]

    In the JSON settings file that opens up, look for the `"profiles"` section in the JSON file: 

    ```json
    "profiles":
    {
        "defaults": {},
        "list":
        [
            {
                "commandline": "%SystemRoot%\\System32\\WindowsPowerShell\\v1.0\\powershell.exe",
                "guid": "{61c54bbd-c2c6-5271-96e7-009a87ff44bf}",
                "hidden": false,
                "name": "Windows PowerShell"
            },
            {
                "commandline": "%SystemRoot%\\System32\\cmd.exe",
                "guid": "{0caa0dad-35be-5f56-a8ff-afceeeaa6101}",
                "hidden": false,
                "name": "Command Prompt"
            },
            {
                "guid": "{b453ae62-4e3d-5e58-b989-0a998ec441b8}",
                "hidden": false,
                "name": "Azure Cloud Shell",
                "source": "Windows.Terminal.Azure"
            },  // <=== add this comma here!

            // new profile entries go here! <=====
        ]
    },
    ```

    Here, we will add *7* new MSYS2 profiles. Use a unique GUID from your previously-generated list above for each entry. Be sure to add a comma at the end of the last pre-existing profile entry above. 
    
    Here are my new entries in the JSON `"profiles"` list above. Your GUIDs should be different, based on what you generated above (I actually don't know if yours need to be different from mine; I just know each entry needs a unique GUID one from another). Ensure you put a comma after each entry, including adding a comma after the ending `}` of the last entry just above. Notice the Linux-like forward slashes in the paths.

    My 7 new MSYS2 profiles:

    ```json
    "profiles":
    {
        "defaults": {},
        "list":
        [
            // ============================
            // previous profiles above here
            // ============================

            // -msys and -msys2 (same thing now: both options run msys2)
            {
                "commandline": "C:/msys64/msys2_shell.cmd -defterm -here -no-start -msys2 -shell bash",
                "guid": "{6f0ee3d1-ac4f-48ca-bcf5-a9795f9942d2}",
                "hidden": false,
                "name": "MSYS2: msys2",
                // "startingDirectory": "C:/msys64/home/%USERNAME%", // alternative
                "startingDirectory": "%USERPROFILE%", // ie: C:\Users\my_username
                "icon": "C:/msys64/msys2.ico",
                "font": 
                {
                    "size": 10
                }
            },

            // -mingw32
            {
                "commandline": "C:/msys64/msys2_shell.cmd -defterm -here -no-start -mingw32 -shell bash",
                "guid": "{80414396-5ef4-490b-af88-29600c19ca4a}",
                "hidden": false,
                "name": "MSYS2: mingw32",
                // "startingDirectory": "C:/msys64/home/%USERNAME%", // alternative
                "startingDirectory": "%USERPROFILE%", // ie: C:\Users\my_username
                "icon": "C:/msys64/mingw32.ico",
                "font": 
                {
                    "size": 10
                }
            },

            // -mingw64
            {
                "commandline": "C:/msys64/msys2_shell.cmd -defterm -here -no-start -mingw64 -shell bash",
                "guid": "{aef16ae0-7dd1-4ac7-abd8-60a646abb9ca}",
                "hidden": false,
                "name": "MSYS2: mingw64",
                // "startingDirectory": "C:/msys64/home/%USERNAME%", // alternative
                "startingDirectory": "%USERPROFILE%", // ie: C:\Users\my_username
                "icon": "C:/msys64/mingw64.ico",
                "font": 
                {
                    "size": 10
                }
            },

            // -ucrt64 (recommended default)
            {
                "commandline": "C:/msys64/msys2_shell.cmd -defterm -here -no-start -ucrt64 -shell bash",
                "guid": "{a718a3d5-9e77-4d0d-b7b6-69ec3d190206}",
                "hidden": false,
                "name": "MSYS2: ucrt64 (recommended default)",
                // "startingDirectory": "C:/msys64/home/%USERNAME%", // alternative
                "startingDirectory": "%USERPROFILE%", // ie: C:\Users\my_username
                "icon": "C:/msys64/ucrt64.ico",
                "font": 
                {
                    "size": 10
                }
            },

            // -clang64
            {
                "commandline": "C:/msys64/msys2_shell.cmd -defterm -here -no-start -clang64 -shell bash",
                "guid": "{1f2869c0-1310-403b-93a7-9227f42eeb24}",
                "hidden": false,
                "name": "MSYS2: clang64",
                // "startingDirectory": "C:/msys64/home/%USERNAME%", // alternative
                "startingDirectory": "%USERPROFILE%", // ie: C:\Users\my_username
                "icon": "C:/msys64/clang64.ico",
                "font": 
                {
                    "size": 10
                }
            },

            // -clang32
            {
                "commandline": "C:/msys64/msys2_shell.cmd -defterm -here -no-start -clang32 -shell bash",
                "guid": "{10c96d8f-9e6b-48f6-8f59-034c586d7e57}",
                "hidden": false,
                "name": "MSYS2: clang32",
                // "startingDirectory": "C:/msys64/home/%USERNAME%", // alternative
                "startingDirectory": "%USERPROFILE%", // ie: C:\Users\my_username
                "icon": "C:/msys64/clang32.ico",
                "font": 
                {
                    "size": 10
                }
            },

            // -clangarm64
            {
                "commandline": "C:/msys64/msys2_shell.cmd -defterm -here -no-start -clangarm64 -shell bash",
                "guid": "{ada1f939-0f7b-400c-b755-8cbff4fd40a8}",
                "hidden": false,
                "name": "MSYS2: clangarm64",
                // "startingDirectory": "C:/msys64/home/%USERNAME%", // alternative
                "startingDirectory": "%USERPROFILE%", // ie: C:\Users\my_username
                "icon": "C:/msys64/clangarm64.ico",
                "font": 
                {
                    "size": 10
                }
            },
    ```

    Copy and paste those 7 new profiles above into the correct location in your Windows Terminal JSON settings file. 

    Save the JSON file, and close it.
  
1. How to change your default shell:

    Note that if you want to use another shell, such as `fish` or `zsh`, you can use `-shell fish` or `-shell zsh` instead of `-shell bash` in the profile commands above. See here: https://www.msys2.org/docs/terminals/. If you aren't sure, stick with `-shell bash`. 

1. Back in Windows Terminal, click the little drop-down arrow at the top right of your tabs at the top. You'll now see these 7 new MSYS2 entries you just added!:

    [![enter image description here][3]][3]

1. Click each one to test it, and ensure they all run. 

1. Choose an MSYS2 environment as your default Windows Terminal profile:

    Click the little drop-down arrow to the right of the tabs at the top, and go to "Settings" again --> choose the "Startup" tab on the left.

    Change the "Default profile" --> "MSYS2: ucrt64 (recommended default)".

    Turn "Launch on machine startup" to "On".

    Change "When Terminal starts" to "Open windows from a previous session". 

    Click "Save". 
    
    Here are what my Windows Terminal "Startup" settings looks like:

    [![enter image description here][4]][4]

1. Change your `HOME` (`~`) dir from MSYS2's default of `C:\msys64\home\my_username` to your regular Windows home dir of `C:\Users\my_username`:

    Open up `C:\msys64\home\my_username\.bash_profile` in a text editor, such as VSCode. Modify it so that it looks like this. Note: you can just comment everything out with `#` and add this to the _top_:

    ```bash
    # Change your home (`~`) dir to `C:\Users\my_username`
    HOME="/c/Users/$(whoami)"

    # Source your `C:\Users\my_username\.profile` file, if it exists
    if [ -f "$HOME/.profile" ]; then
	    . "$HOME/.profile"
    fi
    ```

    Close and re-open Windows Terminal. Run `echo ~` and `echo "$HOME"` and ensure they now both show `/c/Users/my_username`. Run `ls -a` and ensure you see the contents of your normal Windows home directory for your user. `pwd` should show that you are currently in that directory too, since we set this via `"startingDirectory": "%USERPROFILE%",` in the JSON file above.

1. Install Ubuntu's default `~/.profile` and `~/.bashrc` files: 

    Now, create a `C:\Users\my_username\.profile` file, if you don't already have one, and put the entire contents of this _default Ubuntu `~/.profile` file_ into it, from my repo: https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles/blob/master/etc/skel/.profile

    If you don't have  `~/.profile` file yet, the easiest way to do that is to open up your **MSYS2: ucrt64** terminal and run the following:

    ```bash
    cd ~

    # download Ubuntu's default ~/.profile file
    wget https://raw.githubusercontent.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles/master/etc/skel/.profile
    
    # we might as well get the ~/.bash_logout file too
    wget https://raw.githubusercontent.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles/master/etc/skel/.bash_logout
    ```

    Now, go here for Ubuntu's default `~/.bashrc` file: https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles/blob/master/etc/skel/.bashrc. Copy and paste the entire contents of this file into the _top_ of your `~/.bashrc` file. 

    Put a nice `# ================== END OF UBUNTU'S DEFAULT ~/.bashrc FILE ====================` marker into the end of your `~/.bashrc` file, and add any custom entries you want below that.

1. **IMPORTANT:** we do *not* want to remove the `UCRT64` and `MINGW64` type entries from our `PS1` Prompt String 1 variables (which appear in the terminal before each line where you type), because we like seeing these important markers in our prompt, to remind us which MSYS2 shell we are in. So, go into your `~/.bashrc` file and comment out all changes that Ubuntu does to the `PS1` variable, like this:

    Change this:
    ```bash
    if [ "$color_prompt" = yes ]; then
        PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
    else
        PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
    fi
    unset color_prompt force_color_prompt

    # If this is an xterm set the title to user@host:dir
    case "$TERM" in
    xterm*|rxvt*)
        PS1="\[\e]0;${debian_chroot:+($debian_chroot)}\u@\h: \w\a\]$PS1"
        ;;
    *)
        ;;
    esac
    ```

    ...to this. Notice that the `PS1=` changes are all commented out by doing this:
    ```bash
    # if [ "$color_prompt" = yes ]; then
    #     PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
    # else
    #     PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
    # fi
    unset color_prompt force_color_prompt

    # If this is an xterm set the title to user@host:dir
    case "$TERM" in
    xterm*|rxvt*)
        # PS1="\[\e]0;${debian_chroot:+($debian_chroot)}\u@\h: \w\a\]$PS1"
        ;;
    *)
        ;;
    esac
    ```

1. Now, close and re-open all Windows terminal windows, *or* run `. ~/.profile` in each one to re-source your `~/.profile` file. 
    
    If you don't know what "re-sourcing" means, read my answer here: [`source` (`.`) vs `export` (and also some file lock [`flock`] stuff at the end)](https://stackoverflow.com/a/62626515/4561887).

1. Test your new, beautiful Ubuntu settings: run `ll` and you'll see this alias now works! It is an alias for `ls -alF`, and comes from your `~/.bashrc` file now.

1. Install VSCode and add the `code` executable into your PATH:

    Install VSCode from here, if you don't already have it: https://code.visualstudio.com/

    The `code` executable is found in the `"$HOME/AppData/Local/Programs/Microsoft VS Code/bin"` dir.

    Add it to your PATH by adding this line to the bottom of your `~/.bashrc` file:

    ```bash
    DIR="$HOME/AppData/Local/Programs/Microsoft VS Code/bin"
    if [ -d "$DIR" ] ; then
        PATH="$DIR:$PATH"
    fi
    ```

    Close and re-open all terminals, *or* run `. ~/.profile` in each one to re-source your `~/.profile` and `~/.bashrc` files.

    Now run `code .` in a terminal and it will open up a new instance of VSCode in your current directory. Now we're rockin'.

1. Install and configure git:

    This is beyond the scope of this answer, but oddly enough, MSYS2 currently recommends you install and use Git For Windows and Git Bash (based on MSYS2) instead of trying to install git within MSYS2: https://www.msys2.org/docs/git/

    So, here are some links to resources I've created to help you with that:

    1. Installing Git For Windows: https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles/issues/27#issue-1950880578
    1. [Adding Git-Bash to the new Windows Terminal](https://stackoverflow.com/a/76950661/4561887)
    1. [Running SSH Agent when starting Git Bash on Windows](https://stackoverflow.com/a/76568760/4561887)
    1. [Python not working in the command line of git bash](https://stackoverflow.com/a/76918262/4561887)

1. Now that you have MSYS2 installed and working, your Windows computer is no longer garbage. :)

    But, since I can't easily install git into MSYS2, I guess I'll still be using separate terminals: MSYS2 terminals for building, and the Git Bash terminal for git.

    What a pain Windows is. Just wipe it and install Linux Ubuntu. That's how most of my computers are. :)


## Additional MSYS2 configuration notes

[The answer by @Weed Cookie](https://stackoverflow.com/a/71171561/4561887) helped me. It shows me how to use PowerShell to generate GUIDs, and how to specify the shell with `-shall bash`. 

This MSYS2 documentation was the most useful: https://www.msys2.org/docs/terminals/. It showed me how to specify the commandline, icon, font, starting directory, and "shell type" with `-ucrt64`, `-msys2`, etc. 

There are **3 places I am aware of to see that all of these 7 MSYS2 environments exist.** This was not easy for me to track down. Here they are:

1.  [The most definitive, perhaps] Open up the `"C:\msys64\msys2_shell.cmd"` Windows batch file in a text editor, and look for these lines: 
    ```bat
    rem Shell types
    if "x%~1" == "x-msys" shift& set /a msys2_shiftCounter+=1& set MSYSTEM=MSYS& goto :checkparams
    if "x%~1" == "x-msys2" shift& set /a msys2_shiftCounter+=1& set MSYSTEM=MSYS& goto :checkparams
    if "x%~1" == "x-mingw32" shift& set /a msys2_shiftCounter+=1& set MSYSTEM=MINGW32& goto :checkparams
    if "x%~1" == "x-mingw64" shift& set /a msys2_shiftCounter+=1& set MSYSTEM=MINGW64& goto :checkparams
    if "x%~1" == "x-ucrt64" shift& set /a msys2_shiftCounter+=1& set MSYSTEM=UCRT64& goto :checkparams
    if "x%~1" == "x-clang64" shift& set /a msys2_shiftCounter+=1& set MSYSTEM=CLANG64& goto :checkparams
    if "x%~1" == "x-clang32" shift& set /a msys2_shiftCounter+=1& set MSYSTEM=CLANG32& goto :checkparams
    if "x%~1" == "x-clangarm64" shift& set /a msys2_shiftCounter+=1& set MSYSTEM=CLANGARM64& goto :checkparams
    if "x%~1" == "x-mingw" shift& set /a msys2_shiftCounter+=1& (if exist "%WD%..\..\mingw64" (set MSYSTEM=MINGW64) else (set MSYSTEM=MINGW32))& goto :checkparams
    ```

    In those lines, we see the 7 shell types listed above. You can see that `x-msys` and `x-msys2` are the same thing, because they both call `set MSYSTEM=MSYS`. `x-mingw` is a special case, because it checks for the existence of the `mingw64` directory, and if it exists, it sets `MSYSTEM=MINGW64`; otherwise it sets `MSYSTEM=MINGW32`.

    If you check the help menu for this batch file by running `C:\msys64\msys2_shell.cmd --help` in a Command Prompt, you'll see the following:

    ```
    C:\>.\msys64\msys2_shell.cmd --help
    Usage:
        msys2_shell.cmd [options] [login shell parameters]

    Options:
        -mingw32 | -mingw64 | -ucrt64 | -clang64 | -msys[2]   Set shell type
        -defterm | -mintty | -conemu                            Set terminal type
        -here                            Use current directory as working
                                        directory
        -where DIRECTORY                 Use specified DIRECTORY as working
                                        directory
        -[use-]full-path                 Use full current PATH variable
                                        instead of trimming to minimal
        -no-start                        Do not use "start" command and
                                        return login shell resulting
                                        errorcode as this batch file
                                        resulting errorcode
        -shell SHELL                     Set login shell
        -help | --help | -? | /?         Display this help and exit

    Any parameter that cannot be treated as valid option and all
    following parameters are passed as login shell command parameters.
    ```

    Notice that the "shell type" options are `-mingw32`, `-mingw64`, `-ucrt64`, `-clang64`, `-msys[2]`. The `-msys[2]` part means that you can use either `-msys` or `-msys2` to specify the MSYS2 shell type. But, they are missing two of the types!: `-clang32` and `-clangarm64`! So, the only way to see those is to look inside the `C:\msys64\msys2_shell.cmd` batch file itself, rather than looking at its help menu. 

    If you look inside `C:\Users\my_username\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\MSYS2`, you'll see these 6 start menu entries: 
    ```
    'MSYS2 CLANG64.lnk'
    'MSYS2 CLANGARM64.lnk'
    'MSYS2 MINGW32.lnk'
    'MSYS2 MINGW64.lnk'
    'MSYS2 MSYS.lnk'
    'MSYS2 UCRT64.lnk'
    ```

    Again, they are missing one!--this time: `clang32`. 

1. You can see all 7 `.exe` executables here: `C:\msys64`.

    Here is what that looks like from the **MSYS2: ucrt64** command line. You can see all 7 here:

    ```bash
    ls -1 /c/msys64/*.exe
    ```

    Output:
    ```
    /c/msys64/clang32.exe
    /c/msys64/clang64.exe
    /c/msys64/clangarm64.exe
    /c/msys64/mingw32.exe
    /c/msys64/mingw64.exe
    /c/msys64/msys2.exe
    /c/msys64/ucrt64.exe
    /c/msys64/uninstall.exe
    ```

1. You can also look online and see all 7 in the table here: https://www.msys2.org/docs/environments/


## Other references

1. [What is the alternative for `~` (user's home directory) on Windows command prompt?](https://stackoverflow.com/a/9229022/4561887) - answer: `%USERPROFILE%` or `%HOMEDRIVE%%HOMEPATH%` (see [my comment](https://stackoverflow.com/questions/9228950/what-is-the-alternative-for-users-home-directory-on-windows-command-prompt#comment136452010_9229022))
1. Oddly enough: even though Git Bash is based on MSYS2, you can't easily install git into MSYS2. MSYS2 actually recommends you install Git for Windows and use Git Bash: https://www.msys2.org/docs/git/



  [1]: https://i.stack.imgur.com/qAFiC.png
  [2]: https://i.stack.imgur.com/zVHmj.png
  [3]: https://i.stack.imgur.com/DHRFm.png
  [4]: https://i.stack.imgur.com/c8fFZ.png
