<!--
GS
31 Oct. 2023

https://stackoverflow.com/q/71045716/4561887
-->

_Tested on the latest version of MSYS2, `msys2-x86_64-20231026.exe`, from https://www.msys2.org/, on Windows 11, on 31 Oct. 2023, as a spooky treat._

As a more beginner-friendly, thorough, and customized version of [@Weed Cookie's answer](https://stackoverflow.com/a/71171561/4561887), here are additional details I and other beginners are sure to need. 

We will add **7** new MSYS2 profiles to Windows Terminal, one for each of the 7 MSYS2 shell types:
1. msys and msys2 (same thing now)
1. mingw32
1. mingw64
1. ucrt64
1. clang64
1. clang32
1. clangarm64

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

In those lines, we see the 7 shell types listed above. You can see that `x-msys` and `x-msys2` are the same thing, because they both call `set MSYSTEM=MSYS`. `x-mingw` is a special case, because it checks for the existence of the `mingw64` directory, and if it exists, it sets `MSYSTEM=MINGW64`, otherwise it sets `MSYSTEM=MINGW32`.

If you check the help menu for this batch file by running `C:\msys64\msys2_shell.cmd --help` in a Command Prompt, you'll see the following:



## Setting up MSYS2 to run in Windows Terminal

1. Download and install the latest version of MSYS2. 
    1. You can get it here: https://www.msys2.org/. 
    1. Note that MSYS2 includes [MinGW-w64](https://www.mingw-w64.org/) and the Pacman package manager, and is a powerful, Linux-like terminal and GCC and LLVM (clang) build environment for Windows. It is akin to Cygwin, and more powerful than Git Bash from [Git for Windows](https://gitforwindows.org/). You can think of MSYS2 as a more powerful version of Git Bash, with a package manager, or, as a light version of Linux running inside Windows.

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

1. Open Windows Terminal. 
    
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

    Here, we will add *5* new MSYS2 profiles. Use a unique GUID from your previously-generated list above for each entry. Here are my 5 new entries in the JSON `"profiles"` list above. Your GUIDs should be different, based on what you generated above (I actually don't know if yours need to be different from mine; I just know each entry needs a unique GUID one from another). Ensure you put a comma after each entry, including adding a comma after the ending `}` of the last entry just above. Notice the Linux-like forward slashes in the paths.

    My 5 new MSYS2 profiles:

    ```json
    "profiles":
    {
        "defaults": {},
        "list":
        [
            // previous profiles above here

            // -mingw32
            {
                "commandline": "C:/msys64/msys2_shell.cmd -defterm -here -no-start -mingw32 -shell bash",
                "guid": "{6f0ee3d1-ac4f-48ca-bcf5-a9795f9942d2}",
                "hidden": false,
                "name": "MSYS2: mingw32",
                "startingDirectory": "C:/msys64/home/%USERNAME%",
                "icon": "C:/msys64/mingw32.ico",
                "font": 
                {
                    "size": 11
                }
            },

            // -mingw64
            {
                "commandline": "C:/msys64/msys2_shell.cmd -defterm -here -no-start -mingw64 -shell bash",
                "guid": "{80414396-5ef4-490b-af88-29600c19ca4a}",
                "hidden": false,
                "name": "MSYS2: mingw64",
                "startingDirectory": "C:/msys64/home/%USERNAME%",
                "icon": "C:/msys64/mingw64.ico",
                "font": 
                {
                    "size": 11
                }
            },

            // -ucrt64
            {
                "commandline": "C:/msys64/msys2_shell.cmd -defterm -here -no-start -ucrt64 -shell bash",
                "guid": "{aef16ae0-7dd1-4ac7-abd8-60a646abb9ca}",
                "hidden": false,
                "name": "MSYS2: ucrt64",
                "startingDirectory": "C:/msys64/home/%USERNAME%",
                "icon": "C:/msys64/ucrt64.ico",
                "font": 
                {
                    "size": 11
                }
            },

            // -clang64
            {
                "commandline": "C:/msys64/msys2_shell.cmd -defterm -here -no-start -clang64 -shell bash",
                "guid": "{a718a3d5-9e77-4d0d-b7b6-69ec3d190206}",
                "hidden": false,
                "name": "MSYS2: clang64",
                "startingDirectory": "C:/msys64/home/%USERNAME%",
                "icon": "C:/msys64/clang64.ico",
                "font": 
                {
                    "size": 11
                }
            },

            // -msys and -msys2 (same thing now: both options run msys2)
            {
                "commandline": "C:/msys64/msys2_shell.cmd -defterm -here -no-start -msys2 -shell bash",
                "guid": "{1f2869c0-1310-403b-93a7-9227f42eeb24}",
                "hidden": false,
                "name": "MSYS2: msys2",
                "startingDirectory": "C:/msys64/home/%USERNAME%",
                "icon": "C:/msys64/msys2.ico",
                "font": 
                {
                    "size": 11
                }
            },
    ```

    Save the JSON file, and close it.

    Back in Windows Terminal, click the little drop-down arrow at the top right of your tabs at the top. You'll now see these 5 new MSYS2 entries you just added!:

    [![enter image description here][2]][2]


## Configuration notes

[The answer by @Weed Cookie](https://stackoverflow.com/a/71171561/4561887) helped me. It shows me how to use PowerShell to generate GUIDs, and how to specify the shell with `-shall bash`. 

This MSYS2 documentation was the most useful: https://www.msys2.org/docs/terminals/. It showed me how to specify the commandline, icon, font, starting directory, and "shell type" with `-ucrt64`, `-msys2`, etc. 

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




  


  [1]: https://i.stack.imgur.com/zVHmj.png
  [2]: https://i.stack.imgur.com/wBlD1.png
