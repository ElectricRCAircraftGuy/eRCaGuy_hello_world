#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world
#
# GS
# Feb. 2026
#
# Build the Docker image for cross-compiling executables from Linux to Windows.
# Tag the image as "mingw-gcc-cross:latest".
#
# NB:
# 1. Rebuild the docker image via `./docker_build.sh` whenever the following files are changed:
#    1. `Dockerfile` - Any change to the Dockerfile itself. Especially needed if changes are made to
#       the `COPY`, `ADD`, `RUN`, `WORKDIR`, `ENTRYPOINT`, or `CMD` instructions.
#    1. `entrypoint.sh` - This is COPY'd into the image during the Docker image build.
#    1. `docker_build.sh` - any changes to the `docker build` command or its arguments change how
#        the image is built.
#

# See my answer: https://stackoverflow.com/a/60157372/4561887
FULL_PATH_TO_SCRIPT="$(realpath "${BASH_SOURCE[0]}")"
SCRIPT_DIRECTORY="$(dirname "$FULL_PATH_TO_SCRIPT")"

# Source (import) libraries
. "${SCRIPT_DIRECTORY}/../bash/ansi_color_codes_simple_lib.sh" # `echo_green` et al
. "${SCRIPT_DIRECTORY}/docker_config.sh"  # For `IMAGE_NAME` and `IMAGE_TAG` variables

echo "Building Docker image: ${IMAGE_NAME}:${IMAGE_TAG}"
echo "From Dockerfile: ${SCRIPT_DIRECTORY}/Dockerfile"
echo ""

# NB: the last (positional) argument to `docker build` is the "build context" directory, which is
# the directory that Docker will use as the root for resolving any `COPY` commands in the
# Dockerfile.
time docker build \
    --tag "${IMAGE_NAME}:${IMAGE_TAG}" \
    --file "${SCRIPT_DIRECTORY}/Dockerfile" \
    "${SCRIPT_DIRECTORY}"

EXIT_CODE="$?"

if [ "$EXIT_CODE" -eq "0" ]; then
    echo ""
    echo_green "✓ Build successful!"
    echo "Image: ${IMAGE_NAME}:${IMAGE_TAG}"
    echo ""
    echo "To run the container:"
    echo_blue "${SCRIPT_DIRECTORY}/docker_run.sh"
else
    echo ""
    echo_red "✗ Build failed with exit code: $EXIT_CODE"
fi

exit "$EXIT_CODE"
