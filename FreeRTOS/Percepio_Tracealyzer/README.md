This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world


# References

1. https://percepio.com/tracealyzer/
1. https://percepio.com/running-tracealyzer-4-on-linux-hosts-2022/ - Linux installation instructions. 
1. https://www.mono-project.com/download/stable/#download-lin


# 1. Install Tracealyzer on your PC

#### On Linux Ubuntu 22.04

1. Install Mono, a dependency:

    Note the following important information: https://percepio.com/running-tracealyzer-4-on-linux-hosts-2022/:

    > Note that Mono 6.8 is known to cause issues. Make sure to check your mono version by typing “mono -V”. We strongly recommend to use the latest Mono version (6.12 or newer) available from the mono-project repository.
    > 
    > You find instructions for Ubuntu and Debian distributions at https://www.mono-project.com/download/stable/#download-lin. The instructions for Ubuntu 20 have been used successfully also for Ubuntu 22.

    Instructions: 

    https://www.mono-project.com/download/stable/#download-lin:

    ```bash
    sudo apt install ca-certificates gnupg
    sudo gpg --homedir /tmp --no-default-keyring --keyring /usr/share/keyrings/mono-official-archive-keyring.gpg --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys 3FA7E0328081BFF6A14DA29AA6A19B38D3D831EF
    echo "deb [signed-by=/usr/share/keyrings/mono-official-archive-keyring.gpg] https://download.mono-project.com/repo/ubuntu stable-focal main" | sudo tee /etc/apt/sources.list.d/mono-official-stable.list

    sudo apt update
    sudo apt install mono-devel
    
    # Check the version. "You should have Mono JIT compiler version 6.12.0.200" or later!
    mono -V
    ```

1. Install other dependencies:
    ```bash
    sudo apt update
    sudo apt install libcanberra-gtk-module
    ```

1. Download the latest version of Tracealyzer from https://percepio.com/tracealyzer/update/. My downloaded file is `Tracealyzer-4.8.2-linux64.tgz`, for instance. 

1. Note: you may need to buy a license for $5k or so. I think they will provide a free license for like 10 days otherwise. 

1. Extract the `.tgz` file:
    ```bash
    time tar -xf Tracealyzer-4.8.2-linux64.tgz
    ```

1. Run it!: 
    ```bash
    Tracealyzer-4.8.2-linux64/launch-tz.sh
    ```

    If you get this error when you try to run it:

    ```bash
    Tracealyzer$ Tracealyzer-4.8.2-linux64/launch-tz.sh 
    Failed to initialize CEF! This is usually caused by missing libraries, such as libgconf (package libgconf-2-4) or libXss (included in the libXScrnSaver package).
    ```

    ...then try using `sudo`: 
    ```bash
    sudo Tracealyzer-4.8.2-linux64/launch-tz.sh
    ```


# 2. Add Tracealyzer code for FreeRTOS to your Microchip MPLAB X project

#### References

1. https://percepio.com/tracealyzer/gettingstarted/
    1. https://percepio.com/getstarted/latest/html/freertos.html
1. Official source code on GitHub: https://github.com/percepio/TraceRecorderSource

#### Steps

1. Find the latest release tag here: https://github.com/percepio/TraceRecorderSource/tags. 

    Ex: let's assume it is `Tz4/4.8/v4.8.2`. 

1. Get the code from GitHub: 
    ```bash
    mkdir percepio
    cd percepio
    git clone https://github.com/percepio/TraceRecorderSource.git
    cd TraceRecorderSource
    
    # Checkout the latest release tag you found above
    git checkout Tz4/4.8/v4.8.2
    ```

1. Now follow the instructions here: https://percepio.com/getstarted/latest/html/freertos.html


# 3. Install the MPLAB X plugin for Tracealyzer

#### References

From here: https://percepio.com/getstarted/latest/html/freertos.html:

> The MPLAB x plugin can be downloaded [here](https://percepio.com/downloads/mplab-plugin.zip) then it can be installed following [these](https://microchipdeveloper.com/mplabx:tools-plugins-downloaded) instructions. To save a snapshot first open the Tracealyzer plugin by going to Tools -> Embedded -> Tracealyzer Export Plugin. Then start a debugging session, halt it, and press the "Save Trace" button.

#### Steps

1. Download the plugin from here: https://percepio.com/downloads/mplab-plugin.zip. Extract it. Inside, you'll find `v2_3_0-percepio-tracealyzerexportplugin.nbm`, or similar. 

1. Install it: 

    In MPLAB X IDE: Tools --> Plugins --> click "Downloaded" tab --> click "Add Plugins" --> select or paste in the path to the .nbm file above --> click "Ok" --> you'll now see the plugin selected. It has the name "Tracealyzer Export Plugin". 
    
    Click "Install" --> "Next >" --> check the box to accept the license terms --> click "Install" --> "Continue" --> "Finish" --> "Close". 

1. You can now open the plugin via Tools --> Embedded --> Tracealyzer Export Plugin.
