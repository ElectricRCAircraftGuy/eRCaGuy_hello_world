<!--
GS
July 2024

https://superuser.com/a/1849905/425838

-->


## Enable long paths (> `MAX_PATH` of 260 chars) in Windows

1. Press <kbd>Win</kbd> and search for `powershell`. Right-click on "Windows PowerShell" and select "Run as administrator". Type in your username and password to continue. 
1. Run this command in the elevated PowerShell terminal to enable long paths: 
    ```powershell
    New-ItemProperty -Path "HKLM:\SYSTEM\CurrentControlSet\Control\FileSystem" -Name "LongPathsEnabled" -Value 1 -PropertyType DWORD -Force
    ```

    You'll see this as an output: 

    > ```powershell
    > LongPathsEnabled : 1
    > PSPath           : Microsoft.PowerShell.Core\Registry::HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\FileSystem
    > PSParentPath     : Microsoft.PowerShell.Core\Registry::HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control
    > PSChildName      : FileSystem
    > PSDrive          : HKLM
    > PSProvider       : Microsoft.PowerShell.Core\Registry
    > ```

1. Done. *Some* programs will now allow longer paths, so long as the program developers have enabled this feature in their source code and are complying with adding it to their "application manifest" as well. See: https://learn.microsoft.com/en-us/windows/win32/fileio/maximum-file-path-limitation?tabs=powershell


## Test it in Git Bash, File Explorer, and VSCode

1. Install Git for Windows to get access to the Git Bash terminal. See my instructions here: **[Installing Git For Windows](https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles/issues/27#issue-1950880578)**.
1. Run this in Git Bash
    ```bash
    cd ~

    # create a 400+ char path
    mkdir -p thisssssssssssssssssssssssssssssss/isssssssssssssssssssssssssssssssss/aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa/longggggggggggggggggggggggggg/pathhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh/thatttttttttttttttttttttttttttttttttttttttttttttttttttt/shouldddddddddddddddddddddddddddddddddddddddddddd/workkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk/nowwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
    ```

1. Now manually navigate to there in File Explorer, right-click and go to "New" -> "Folder". 

    1. If you have *not* yet done the fix above, you will see this error in a popup window:

        [![enter image description here][1]][1]

        > Destination Path Too Long
        > 
        > The file name(s) would be too long for the destination folder. You can shorten the file name and try again, or try a location that has a shorter path.

    1. If you *have* done the fix above, you will see the folder created successfully.

////////////




And see if you can create it and open it, edit it, save it, etc. 


1. Now manually navigate to there in File Explorer, right-click and go to "New" -> "Text Document". And see if you can create it and open it, edit it, save it, etc. 

    Note: I open and edit in in [MS VS Code](https://code.visualstudio.com/). 

1. It works for me. Done. Awesome! 


## References

1. https://learn.microsoft.com/en-us/windows/win32/fileio/maximum-file-path-limitation?tabs=powershell



  [1]: https://i.sstatic.net/TkR51pJj.png
