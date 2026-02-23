# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world
#
# GS
# Feb. 2026
#
# An Ubuntu 24.04 Docker image with mingw-w64 and build tools installed, for cross-compiling from
# Linux for Windows.
#
# NB:
# 1. Rebuild the docker image via `./docker_build.sh` whenever the following files are changed:
#    1. `Dockerfile` - Any change to the Dockerfile itself. Especially needed if changes are made to
#       the `COPY`, `ADD`, `RUN`, `WORKDIR`, `ENTRYPOINT`, or `CMD` instructions.
#    1. `entrypoint.sh` - This is COPY'd into the image during the Docker image build.
#    1. `docker_build.sh` - any changes to the `docker build` command or its arguments change how
#        the image is built.
# 1. Relative paths herein, such as those used in `COPY` and `RUN` commands, are relative to the
#    build context directory, which is passed as the last (positional) argument to the `docker
#    build` command.

FROM ubuntu:24.04

# Install mingw-w64 and build tools, then remove apt lists to reduce image size when done
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
    autoconf \
    build-essential \
    # compiler cache to speed up repeated builds; auto-caches in container at path `/root/.ccache/`
    ccache \
    curl \
    # mingw-w64: for cross-compiling from Linux for Windows
    g++-mingw-w64-x86-64-posix \
    gcc-mingw-w64-x86-64-posix \
    # gcovr \
    git \
    gosu \
    # libssl-dev \
    # libtool \
    # mingw-w64-tools \
    nano \
    # ninja-build \
    # pkg-config \
    # plocate \
    python3 \
    tar \
    unzip \
    vim \
    wget \
    zip \
    # zlib1g-dev \
    # Remove apt lists to reduce image size
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

# Copy and set up entrypoint script for user switching with gosu
COPY entrypoint.sh /usr/local/bin/entrypoint.sh
RUN chmod +x /usr/local/bin/entrypoint.sh

# Set the **default working directory** for the container.
#
# It determines:
# 1. **Where you land** when the container starts (if no override via `--workdir` to `docker run` is
#    provided).
# 2. **Where relative paths resolve** in subsequent Dockerfile instructions (RUN, COPY, etc.).
# 3. **The default `pwd`** inside a running container.
#
# NB: The `--workdir` flag passed to `docker run` at runtime always wins over the Dockerfile's
# `WORKDIR`.
#
WORKDIR /workspace

# vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
# NOTES/STUDY:
#
# Set ENTRYPOINT and CMD:
#
# ```dockerfile
# ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]
# CMD ["/bin/bash"]
# ```
#
# **What happens when you run...:**
# ```bash
# docker run myimage
# # Runs: /usr/local/bin/entrypoint.sh /bin/bash
#
# docker run myimage ls -la
# # Runs: /usr/local/bin/entrypoint.sh ls -la
#
# docker run myimage x86_64-w64-mingw32-g++ --version
# # Runs: /usr/local/bin/entrypoint.sh x86_64-w64-mingw32-g++ --version
# ```
#
# **Inside entrypoint.sh:**
# ```bash
# exec gosu "$USER_ID:$GROUP_ID" "$@"
# #                                 └─ This receives /bin/bash (or whatever you pass)
# ```
# ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

# Set entrypoint, or startup script for when the container starts.
#
# - This runs **every time** the container starts.
# - The container always runs it as root.
# - You can use `gosu` inside of the entrypoint script to switch to a non-root user, and then run
#   the command passed to `docker run` as that non-root user.
# - The `CMD` specified farther below gets passed as an argument to the entrypoint script.
# - In my case, my `entrypoint.sh` script handles user switching.
#
ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]

# Default command if you run `docker run IMAGE_NAME:IMAGE_TAG` without additional commands.
# - This will run the container and drop you into a bash shell. You can override this by passing
#   additional commands to `docker run`, such as `docker run IMAGE_NAME:IMAGE_TAG ls -la` to run `ls
#   -la` instead of dropping into a bash shell.
# - If `ENTRYPOINT` exists, as it does above, then the `CMD` gets passed as an argument to the
#   `ENTRYPOINT` script.
CMD ["/bin/bash"]
