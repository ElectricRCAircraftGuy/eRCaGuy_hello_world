#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# Feb. 2026

# Build the Docker image for cross-compiling executables from Linux to Windows.
# Tag the image as "mingw-gcc-cross:latest".

FULL_PATH_TO_SCRIPT="$(realpath "${BASH_SOURCE[0]}")"
SCRIPT_DIRECTORY="$(dirname "$FULL_PATH_TO_SCRIPT")"

# Source (import) libraries
. "${SCRIPT_DIRECTORY}/../bash/ansi_color_codes_simple_lib.sh"

IMAGE_NAME="mingw-gcc-cross"
IMAGE_TAG="latest"

echo "Building Docker image: ${IMAGE_NAME}:${IMAGE_TAG}"
echo "From Dockerfile: ${SCRIPT_DIRECTORY}/Dockerfile"
echo ""

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
    echo_blue "  ${SCRIPT_DIRECTORY}/docker_run.sh"
else
    echo ""
    echo_red "✗ Build failed with exit code: $EXIT_CODE"
fi

exit "$EXIT_CODE"
