# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world
#
# GS
# Feb. 2026
#
# An Ubuntu 24.04 Docker image with mingw-w64 and build tools installed, for cross-compiling from
# Linux for Windows.
#

FROM ubuntu:24.04

# Install mingw-w64 and build tools, then remove apt lists to reduce image size when done
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
    autoconf \
    build-essential \
    ccache \
    curl \
    # mingw-w64: for cross-compiling from Linux for Windows
    g++-mingw-w64-x86-64-posix \
    gcc-mingw-w64-x86-64-posix \
    # gcovr \
    git \
    # gosu \
    # libssl-dev \
    # libtool \
    # mingw-w64-tools \
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

# Set working directory
WORKDIR /workspace

# Default command
CMD ["/bin/bash"]
