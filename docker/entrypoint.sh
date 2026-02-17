#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# Docker entrypoint script.
# - This runs **every time** a container starts.
# - Uses gosu to run the passed-in command as a non-root user.
#
# NB:
# 1. Rebuild the docker image via `./docker_build.sh` whenever the following files are changed:
#    1. `Dockerfile` - Any change to the Dockerfile itself. Especially needed if changes are made to
#       the `COPY`, `ADD`, `RUN`, `WORKDIR`, `ENTRYPOINT`, or `CMD` instructions.
#    1. `entrypoint.sh` - This is COPY'd into the image during the Docker image build.
#    1. `docker_build.sh` - any changes to the `docker build` command or its arguments change how
#        the image is built.
#

# Exit immediately if any command herein exits with a non-zero status. See `help set`.
set -e

# See my answer: https://stackoverflow.com/a/60157372/4561887
FULL_PATH_TO_SCRIPT="$(realpath "${BASH_SOURCE[0]}")"
SCRIPT_DIRECTORY="$(dirname "$FULL_PATH_TO_SCRIPT")"
SCRIPT_FILENAME="$(basename "$FULL_PATH_TO_SCRIPT")"

echo "Running entrypoint script: ${FULL_PATH_TO_SCRIPT}"

# If USER_ID and GROUP_ID are provided, create a user and switch to it
if [ -n "$USER_ID" ] && [ -n "$GROUP_ID" ]; then
    echo "Command: $*"
    echo "Running command as non-root user $USER_NAME:$USER_ID, group $GROUP_NAME:$GROUP_ID"

    # Create group if it doesn't exist
    if ! getent group "$GROUP_ID" > /dev/null 2>&1; then
        groupadd -g "$GROUP_ID" "$GROUP_NAME"
    fi

    # Create user if it doesn't exist
    if ! getent passwd "$USER_ID" > /dev/null 2>&1; then
        # Create a new user account inside the container with:
        #
        # -u "$USER_ID" - Sets the user's numeric ID (UID) to match your host user (e.g., 1000).
        # -g "$GROUP_ID" - Sets the user's primary group ID (GID) to match your host group
        #    (e.g., 1000).
        # --create-home - Creates a home directory for the user (e.g., /home/builder).
        # --shell /bin/bash - Sets the default shell to bash.
        # "$USER_NAME" - The username (e.g., "builder").
        useradd -u "$USER_ID" -g "$GROUP_ID" --create-home --shell /bin/bash "$USER_NAME"
    fi

    echo ""
    # Use gosu to execute the command as the non-root user
    exec gosu "$USER_ID:$GROUP_ID" "$@"
else
    # No user specified, run as root (default behavior)
    echo ""
    exec "$@"
fi
