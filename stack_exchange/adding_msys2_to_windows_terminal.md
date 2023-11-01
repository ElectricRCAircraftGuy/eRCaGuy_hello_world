<!--
GS
31 Oct. 2023

https://stackoverflow.com/q/71045716/4561887
-->

_Tested on the latest version of MSYS2, `msys2-x86_64-20231026.exe`, from https://www.msys2.org/, on Windows 11, on 31 Oct. 2023, as a spooky treat._

As a more beginner-friendly, thorough, and customized version of [@Weed Cookie's answer](https://stackoverflow.com/a/71171561/4561887), here are additional details I and other beginners are sure to need. 

Note that MSYS2 includes [MinGW-w64](https://www.mingw-w64.org/) and the Pacman package manager, and is a powerful, Linux-like terminal and GCC and LLVM (clang) build environment for Windows. It is akin to Cygwin, and more powerful than Git Bash from [Git for Windows](https://gitforwindows.org/). You can think of MSYS2 as a more powerful version of Git Bash, with a package manager, or, as a light version of Linux running inside Windows.

## How to add *all 7* new MSYS2 profiles to Windows Terminal

...one for each of the 7 MSYS2 shell/environment types:

1. msys and msys2 (same thing now)
1. mingw32
1. mingw64
1. ucrt64
1. clang64
1. clang32
1. clangarm64

From: https://www.msys2.org/docs/environments/ (emphasis added): 

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
    
    Click the little drop-down arrow at the top-right of the open tab, and select "Settings" --> in the Settings tab that opens up, click "Open JSON file" in the bottom-left, as shown here:
    
    [![enter image description here][1]][1]

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
            // new profile entries go here!
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
                    "size": 11
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
                    "size": 11
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
                    "size": 11
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
                    "size": 11
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
                    "size": 11
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
                    "size": 11
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
                    "size": 11
                }
            },
    ```

    Save the JSON file, and close it.

1. Back in Windows Terminal, click the little drop-down arrow at the top right of your tabs at the top. You'll now see these 7 new MSYS2 entries you just added!:

    [![enter image description here][2]][2]




## Configuration notes

[The answer by @Weed Cookie](https://stackoverflow.com/a/71171561/4561887) helped me. It shows me how to use PowerShell to generate GUIDs, and how to specify the shell with `-shall bash`. 

This MSYS2 documentation was the most useful: https://www.msys2.org/docs/terminals/. It showed me how to specify the commandline, icon, font, starting directory, and "shell type" with `-ucrt64`, `-msys2`, etc. 

The _only_ place I am aware of to see that all of these exist, is to open up the `"C:\msys64\msys2_shell.cmd"` Windows batch file in a text editor, and look for these lines: 
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

You can also look at 


## Other references

1. [What is the alternative for `~` (user's home directory) on Windows command prompt?](https://stackoverflow.com/a/9229022/4561887) - answer: `%USERPROFILE%` or `%HOMEDRIVE%%HOMEPATH%` (see [my comment](https://stackoverflow.com/questions/9228950/what-is-the-alternative-for-users-home-directory-on-windows-command-prompt#comment136452010_9229022))





  


  [1]: https://i.stack.imgur.com/zVHmj.png
  [2]: https://i.stack.imgur.com/wBlD1.png
