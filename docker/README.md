This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

_For `ssh` setup, see instead: https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles/tree/master/home/.ssh._


This `Dockerfile` allows you to easily build and use a docker image to get and use the [mingw-w64](https://www.mingw-w64.org/) cross compiler toolchain to build C and C++ executables for Windows on Linux, for instance. 


# Docker Setup (and WSL installation, Windows and Linux setup, installing ZScaler certificates in WSL, etc.)

Much of this comes from [approximately here in my `git & Linux cmds, help, tips & tricks - Gabriel.txt` file](<https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles/blob/master/git%20%26%20Linux%20cmds%2C%20help%2C%20tips%20%26%20tricks%20-%20Gabriel.txt#L4945>) in my [eRCaGuy_dotfiles](https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles) repo, under the section in this file titled `Docker installation instructions (for Linux, and Windows 11 via WSL)`. 


## Docker terminology

Quick reference:

1. **Image** = Template (one per build); like a C++ class definition
1. **Container** = Running instance (many from one image); like a C++ class instance/object
1. **Tag** = Version label (you choose)
1. **ID** = Unique hash (system generated)
1. **Name** = Optional friendly label (you choose); like a friendly `std::string` name inside a C++ class, used to describe the class


## For Windows only

### 1. Install WSL (Windows Subsystem for Linux) (Windows 10 or later)

1. Install WSL2 with the latest version of Ubuntu (ex: 24.04) as the Linux distribution:

    Example: run this in Powershell:

    ```powershell
    # Install the latest version of Ubuntu via WSL
    wsl --update
    wsl --install

    # Or install a specific version, such as Ubuntu 24.04
    wsl --install -d Ubuntu-24.04
    ```
    Restart your computer when done. 

    If you have issues, also see my instructions here: https://github.com/microsoft/WSL/issues/9420#issuecomment-1707393924. 
    
    See also Microsoft's instructions here: https://learn.microsoft.com/en-us/windows/wsl/install. 

1. Do some initial Ubuntu setup in WSL2 in a WSL2 terminal: 
    ```bash
    # Upgrade the system
    sudo apt update
    sudo apt upgrade

    # Install basic build tools 
    sudo apt install build-essential git curl wget
    ```

### 2. (Only if you have ZScaler certificates) Install your ZScaler certificates in WSL

If your computer, company, etc., uses ZScaler for network security, you may need to install your ZScaler certificates from Windows into WSL to allow network access from within WSL. Otherwise, you may get certificate-verification errors when trying to run tools which connect to the internet like `sudo apt-get update`, `sudo apt update`, `curl`, `wget`, `git`, `docker pull`, `pip3 install`, etc. within WSL.

Here is how to import, convert, and install your ZScaler certificate from Windows to WSL. 

References:
1. https://krashanoff.com/2022/09/09/wsl-and-zscaler/
1. https://documentation.ubuntu.com/server/how-to/security/install-a-root-ca-certificate-in-the-trust-store/

In Windows, run `certmgr.msc` -> in the left pane go to `Trusted Root Certification Authorities` -> `Certificates` -> find the `Zscaler Root CA` certificate -> right-click it, select `All Tasks` -> `Export...`. In the "Certificate Export Wizard" choose format `DER encoded binary X.509 (.CER)` and save it as `zscaler-root.cer` into your Windows user's home directory. Example full path: `C:\Users\gabriel\zscaler-root.cer`.

From the WSL terminal, run the following commands to convert and install the ZScaler certificate into your WSL Linux system's trusted certificate store:

```bash
# Find your Windows user's home directory path in WSL
# Example: /mnt/c/Users/gabriel
WINDOWS_HOME_WIN="$(powershell.exe -NoProfile -Command '$env:USERPROFILE' | tr -d '\r')"
WINDOWS_HOME="$(wslpath -u "$windows_home_win")"

# See: https://krashanoff.com/2022/09/09/wsl-and-zscaler/

# Convert the certificate
openssl x509 -inform DER -in "$WINDOWS_HOME/zscaler-root.cer" -out "$WINDOWS_HOME/zscaler.crt"

# Install the certificate
sudo cp "$WINDOWS_HOME/zscaler.crt" /usr/local/share/ca-certificates/
sudo update-ca-certificates
```


## (Only if you need to keep Linux from stealing network ports you want to use) Set the Linux ephemeral port range...
...in WSL Linux or regular Linux to not interfere with you.

Let's say you've written some custom software that binds to certain fixed port numbers; ex: `33000` and `33001`. To prevent Linux from assigning your desired ports as ephemeral ports, you can limit the range of ports that Linux will choose from when making ephemeral ports. 

See `ip_local_port_range` here: https://docs.kernel.org/networking/ip-sysctl.html#ip-variables

Run this in your Linux or WSL terminal to view the current ephemeral port range. Note that the default Linux ephemeral port range is typically `32768`-`60999`.

```bash
# Check the current ephemeral port range.
# Example output: 32768 60999
cat /proc/sys/net/ipv4/ip_local_port_range
```

Change the ephemeral port range to `34000` to `60999`, for example:
```bash
echo 'net.ipv4.ip_local_port_range = 34000 60999' | sudo tee /etc/sysctl.d/99-custom-port-range.conf
# Apply only this configuration file.
sudo sysctl -p /etc/sysctl.d/99-custom-port-range.conf
# OR, reload all system sysctl configuration files, including this one.
sudo sysctl --system

# Verify the new ephemeral port range
cat /proc/sys/net/ipv4/ip_local_port_range
```


## Docker installation instructions (for Linux, and Windows 10 or 11+ via WSL)

References: 

1. Docker Engine and Docker Compose:
    1. \*\*\*\*\*[Install Docker Engine on Ubuntu](https://docs.docker.com/engine/install/ubuntu/)
    1. [Linux post-installation steps for Docker Engine](https://docs.docker.com/engine/install/linux-postinstall/)
1. https://docs.docker.com/get-started/
1. https://hub.docker.com/

In short: 

```bash
# -----------------------------------------------------------
# 1. Install the Docker Engine and Docker Compose
# - See: https://docs.docker.com/engine/install/ubuntu/
# -----------------------------------------------------------

# Uninstall conflicting older versions of Docker
sudo apt remove $(dpkg --get-selections docker.io docker-compose docker-compose-v2 docker-doc docker-buildx podman-docker containerd runc | cut -f1)

# Add Docker's official GPG key:
sudo apt update
sudo apt install ca-certificates curl
sudo install -m 0755 -d /etc/apt/keyrings
sudo curl -fsSL https://download.docker.com/linux/ubuntu/gpg -o /etc/apt/keyrings/docker.asc
sudo chmod a+r /etc/apt/keyrings/docker.asc

# Add the repository to Apt sources:
sudo tee /etc/apt/sources.list.d/docker.sources <<EOF
Types: deb
URIs: https://download.docker.com/linux/ubuntu
Suites: $(. /etc/os-release && echo "${UBUNTU_CODENAME:-$VERSION_CODENAME}")
Components: stable
Architectures: $(dpkg --print-architecture)
Signed-By: /etc/apt/keyrings/docker.asc
EOF

# Install the latest version of Docker Engine
sudo apt update
sudo apt install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin

# After installation, verify that Docker is running:
sudo systemctl status docker
# If Docker is not running, start it manually:
sudo systemctl start docker

# -----------------------------------------------------------
# 2. Linux post-installation steps for Docker Engine
# - See: https://docs.docker.com/engine/install/linux-postinstall/
# -----------------------------------------------------------

# Add user to docker group (to avoid requiring `sudo` for docker commands)
sudo groupadd docker
sudo usermod -aG docker $USER

# IMPORTANT: Log out and log back in or restart the machine

# Test Docker installation
docker run --rm hello-world
```

Done! You have now successfully installed and started Docker Engine.


## Install a Docker credential helper

Install a docker credential helper so Docker doesn't store non-encrypted credentials in `~/.docker/config.json`:

Install the `secretservice` credential helper on Linux with:
```bash
sudo apt update
sudo apt install -y golang-docker-credential-helpers
```

Update your `~/.docker/config.json` file to contain only this, telling Docker to use the `secretservice` credential helper: 
```json
{
    "credsStore": "secretservice"
}
```


## Enable and configure your Github Docker Container Registry, for pulling Docker images from your Github repositories

1. Visit your [Personal access tokens](https://github.com/settings/tokens) page on GitHub and click at the top-right `Generate new token` -> `Generate new token (classic)`. 
1. Enter a name in the "Note" field, and set an Expiration date. Example:
    1. Note: `github-container-registry`
    1. Expiration: set to `Custom`: then select the max date away, which is 1 year out.
1. Under "Select scopes", check the box for `write:packages` if you want read/write access to the GitHub Docker Container Registry, or select only `read:packages` for read-only access.
1. Scroll to the bottom and click `Generate token`. 
1. The token now appears only only. Copy it. 

Run the following command to authenticate Docker with your GitHub Docker Container Registry using the generated personal access token. For security, do NOT store the token in plain text in any file, including your `~/.bashrc` file. 

```bash
# Generic form
echo "<YOUR_PERSONAL_ACCESS_TOKEN>" | docker login ghcr.io -u <YOUR_GITHUB_USERNAME> --password-stdin

# Example
GITHUB_USERNAME="MyGitHubUsername"
GITHUB_PAT="ghp_0123456789ABCDEF0123456789ABCDEF0123"
echo "$GITHUB_PAT" | docker login ghcr.io -u "$GITHUB_USERNAME" --password-stdin
```

Running the above command adds the GitHub Docker Container Registry credentials to your Docker configuration via the `"ghcr.io": {},` line in your `~/.docker/config.json` file, allowing you to pull and push Docker images to and from your GitHub repositories. Here is that file with the added line:

`~/.docker/config.json`:
```jsonc
{
    "auths": {
        "ghcr.io": {}, // <=== GITHUB CONTAINER REGISTRY JUST ADDED
    },
    "credsStore": "secretservice",
}
```


## Docker Usage

```bash
# --------------------------------
# Build the docker image
# --------------------------------
./docker_build.sh   # just build the Docker image

./docker_run.sh     # OR: build and then run/enter the Docker image; see below for more details
./docker_run.sh -h  # See the help menu of this script

# --------------------------------
# Delete the built docker image
# --------------------------------
docker images           # list all docker images
. docker_config.sh      # source the config file to get the `IMAGE_NAME` and `IMAGE_TAG` variables
docker rmi ${IMAGE_NAME}:${IMAGE_TAG}  # remove the image by name and tag

# --------------------------------
# Run and enter a Bash terminal in the docker image (builds the docker image first if necessary)
# --------------------------------
./docker_run.sh    # normal
./docker_run.sh -q # quiet, suppressing all unnecessary log messages while starting Docker container

# --------------------------------
# See the help menu
# --------------------------------
./docker_run.sh -h
./docker_run.sh -?
./docker_run.sh --help

# --------------------------------
# Run commands inside the docker container
# --------------------------------
# A) normal, with tons of output
./docker_run.sh <command> [args...]  
# B) quiet, suppressing all unnecessary log messages while starting up the Docker container
./docker_run.sh -q <command> [args...]

# Examples:
./docker_run.sh -q x86_64-w64-mingw32-g++ --version
# NB: the `time` command is a shell builtin, so to use it you must run a shell to run the command, 
# like this:
./docker_run.sh -q bash -c 'time x86_64-w64-mingw32-g++ --version'
# Note: you can force parsing inside the container by using the `--` separator to mark the end 
# of options for `docker_run.sh`:
./docker_run.sh -q -- x86_64-w64-mingw32-g++ --version

# --------------------------------
# Compiling C++ code in Linux with the docker image
# --------------------------------
cd path/to/eRCaGuy_hello_world/cpp
# see the help menu
../docker/docker_run.sh -h
# Build the code in Docker, for Linux
../docker/docker_run.sh -q -w "$PWD" -- bash -c "time g++ -Wall -Wextra -Werror -O3 -std=gnu++20 hello_world_extra_basic.cpp -o bin/a"
# OR: BUILD AND RUN in Docker in Linux
../docker/docker_run.sh -q -w "$PWD" -- bash -c "time g++ -Wall -Wextra -Werror -O3 -std=gnu++20 -static hello_world_extra_basic.cpp -o bin/a && ./bin/a"
# OR: call the C++ file directly, as an exectuable, letting its hash-bang line do the work
../docker/docker_run.sh -q -w "$PWD" -- bash -c "time ./hello_world_extra_basic.cpp"

# --------------------------------
# Cross-compiling C++ code in Linux for Windows with the docker image
# --------------------------------
cd path/to/eRCaGuy_hello_world/cpp
# see the help menu
../docker/docker_run.sh -h
# Build the code in Docker, for Windows
../docker/docker_run.sh -q -w "$PWD" -- bash -c "time x86_64-w64-mingw32-g++ -Wall -Wextra -Werror -O3 -std=gnu++20 hello_world_extra_basic.cpp -o bin/a.exe"
# OR: BUILD in Docker AND RUN in Docker with Wine, all in one:
../docker/docker_run.sh -q -w "$PWD" -- bash -c "time x86_64-w64-mingw32-g++ -Wall -Wextra -Werror -O3 -std=gnu++20 -static hello_world_extra_basic.cpp -o bin/a_static.exe && WINEDEBUG=-all wine bin/a_static.exe; wineserver -w"
```


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

See: https://github.com/jesseduffield/lazydocker?tab=readme-ov-file#binary-release-linuxosxwindows

```bash
# Install lazydocker
curl https://raw.githubusercontent.com/jesseduffield/lazydocker/master/scripts/install_update_linux.sh | bash

# Run lazydocker
# - NB: press `q` to exit the lazydocker interface when done
lazydocker
```

#### Misc. commands

```bash
# List docker images and their disk usage sizes
docker images

# List all docker containers (running or stopped instances of images)
docker ps -a

# List only running containers
docker ps

# See the reclaimable space if you delete unused images and containers
docker system df

# Copy TO container's `/workspace/` directory
docker cp myfile.txt CONTAINER_ID:/workspace/

# Copy FROM container at path `/workspace/output.exe` to current directory (`./`) on host
docker cp CONTAINER_ID:/workspace/output.exe ./

# Run a docker container from image `myimage` while skipping running the `ENTRYPOINT` 
# script specified in the `Dockerfile`, and running `/bin/bash` directly as the 
# `--entrypoint` instead. 
docker run --entrypoint /bin/bash myimage
```
