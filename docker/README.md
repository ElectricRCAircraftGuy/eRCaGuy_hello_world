This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world


This `Dockerfile` allows you to easily build and use a docker image to get and use the [mingw-w64](https://www.mingw-w64.org/) cross compiler toolchain to build C and C++ executables for Windows on Linux, for instance. 


# Docker Setup

Much of this comes from [approximately here in my `git & Linux cmds, help, tips & tricks - Gabriel.txt` file](<https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles/blob/master/git%20%26%20Linux%20cmds%2C%20help%2C%20tips%20%26%20tricks%20-%20Gabriel.txt#L4945>) in my [eRCaGuy_dotfiles](https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles) repo, under the section in this file titled `Docker installation instructions (for Linux, and Windows 11 via WSL)`. 


## WSL installation for Windows only; Windows 10 or later

1. Install WSL2 with the latest version of Ubuntu (ex: 24.04) as the Linux distribution:

    Follow my instructions here: https://github.com/microsoft/WSL/issues/9420#issuecomment-1707393924. 
   
    See also Microsoft's instructions here: https://learn.microsoft.com/en-us/windows/wsl/install. 

1. Do some initial Ubuntu setup in WSL2: 
    ```bash
    # Upgrade the system
    sudo apt update
    sudo apt upgrade

    # Install basic build tools 
    sudo apt install build-essential git curl wget
    ```


## Docker installation instructions (for Linux, and Windows 10 or 11+ via WSL)

References: 

1. Docker Engine and Docker Compose:
    1. [Install Docker Engine on Ubuntu](https://docs.docker.com/engine/install/ubuntu/)
    1. [Linux post-installation steps for Docker Engine](https://docs.docker.com/engine/install/linux-postinstall/)
1. https://docs.docker.com/get-started/
1. https://hub.docker.com/

In short: 

```bash
# Uninstall conflicting older versions of Docker
for pkg in docker.io docker-doc docker-compose docker-compose-v2 podman-docker containerd runc; do sudo apt-get remove $pkg; done

# Add Docker's official GPG key
sudo apt-get update
sudo apt-get install ca-certificates curl
sudo install -m 0755 -d /etc/apt/keyrings
sudo curl -fsSL https://download.docker.com/linux/ubuntu/gpg -o /etc/apt/keyrings/docker.asc
sudo chmod a+r /etc/apt/keyrings/docker.asc

# Add Docker repository to Apt sources
echo \
    "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/ubuntu \
    $(. /etc/os-release && echo "$VERSION_CODENAME") stable" | \
    sudo tee /etc/apt/sources.list.d/docker.list > /dev/null

# Install the latest version of Docker Engine
sudo apt-get update
sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin

# Add user to docker group (to avoid requiring `sudo` for docker commands)
sudo groupadd docker
sudo usermod -aG docker $USER

# IMPORTANT: Log out and log back in or restart the machine

# Test Docker installation
docker run --rm hello-world
```

Done! You have now successfully installed and started Docker Engine.


## Other Docker checks and commands

#### Checks

```bash
# The Docker service starts automatically after installation. To verify that Docker is running, run
# the following command which shows the status of the Docker service:
# - If running, the first few lines will show the following:
#   
#   ● docker.service - Docker Application Container Engine
#        Loaded: loaded (/lib/systemd/system/docker.service; enabled; vendor preset: enabled)
#        Active: active (running) since Tue 2025-09-30 16:45:24 MST; 51s ago
#   
systemctl status docker  # Press `q` to exit the status output

# Verify that the installation is successful by running the hello-world image:
# - This command downloads a test image and runs it in a container. When the container runs, 
#   it prints a confirmation message and exits.
docker run --rm hello-world

# Try an Ubuntu bash terminal in Docker
docker run -it --rm ubuntu bash
# Type `exit` to exit the container when done
```

#### [Highly recommended!] Install and open [`lazydocker`](https://github.com/jesseduffield/lazydocker)
```bash
# Install lazydocker
curl https://raw.githubusercontent.com/jesseduffield/lazydocker/master/scripts/install_update_linux.sh | bash

# Run lazydocker
# - NB: press `q` to exit the lazydocker interface when done
lazydocker
```

#### Misc. commands

```bash
# See docker images
docker images

# See docker containers (instances of images)
docker ps -a

# See only running containers
docker ps

# See the reclaimable space if you delete unused images and containers
docker system df
```
