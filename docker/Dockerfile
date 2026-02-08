FROM ubuntu:24.04

# Install mingw-w64 and build tools, then remove apt lists to reduce image size when done
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
    mingw-w64 \
    g++-mingw-w64-x86-64-posix \
    ccache \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /workspace

# Default command
CMD ["/bin/bash"]
