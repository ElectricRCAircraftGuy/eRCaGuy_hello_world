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

if [ -f "/.dockerenv" ]; then
    echo "Now running inside a Docker container."
else
    echo "Not running inside a Docker container. Exiting with error so we don't screw up the"\
        "host system."
    exit 1
fi

echo "Running entrypoint script: ${FULL_PATH_TO_SCRIPT}"
echo "pwd (bind-mounted to host system): $(pwd)"
echo "Command being run by entrypoint script:"
echo "$*"
echo ""

# Copy over Ubuntu skel files if they are not already bind-mounted as read-only from the
# host system.
# - Use gosu to copy as the non-root user so they have correct ownership and permissions.
copy_skel_file() {
    local username="$1"
    local file="$2"
    if [ -f "/home/$username/$file" ]; then
        echo "Skel file '/etc/skel/$file' already exists in home directory '/home/$username/'." \
            "Not copying."
    else
        echo "Copying skel file '/etc/skel/$file' to home directory '/home/$username/'"
        gosu "$USER_ID:$GROUP_ID" cp "/etc/skel/$file" "/home/$username/"
    fi
}

# If USER_ID and GROUP_ID are provided, create a user and switch to it
if [ -n "$USER_ID" ] && [ -n "$GROUP_ID" ]; then
    echo "Preparing to run the command as as non-root user $USER_NAME:$USER_ID,"\
        "group $GROUP_NAME:$GROUP_ID."

    # NB: The Ubuntu 24.04 base image already has a default `ubuntu` user with UID 1000.
    # So, it conflicts with my user ID 1000 on my host machine. Handle deleting existing users
    # and groups if necessary before recreating them with my own names copied from my host
    # machine.

    # Delete existing user, then group, in that order, THEN add a new group, then user, in that
    # order.
    # We do NOT want the user ID to be already taken under a different username, nor the group ID
    # to be already taken under a different group name.

    # 1. Delete existing user, then group, in that required order.

    EXISTING_USER_WITH_THIS_ID=$(getent passwd "$USER_ID" | cut -d: -f1)
    if [ -n "$EXISTING_USER_WITH_THIS_ID" ] && [ "$EXISTING_USER_WITH_THIS_ID" != "$USER_NAME" ];
    then
        echo "Deleting existing user '$EXISTING_USER_WITH_THIS_ID' with conflicting UID $USER_ID."
        # -r removes home dir
        userdel -r "$EXISTING_USER_WITH_THIS_ID"
        echo ""
    fi

    EXISTING_GROUP_WITH_THIS_ID=$(getent group "$GROUP_ID" | cut -d: -f1)
    if [ -n "$EXISTING_GROUP_WITH_THIS_ID" ] && [ "$EXISTING_GROUP_WITH_THIS_ID" != "$GROUP_NAME" ];
    then
        echo "Deleting existing group '$EXISTING_GROUP_WITH_THIS_ID' with conflicting GID" \
            "$GROUP_ID."
        groupdel "$EXISTING_GROUP_WITH_THIS_ID"
        echo ""
    fi

    # 2. Add new group, then user, in that required order.

    if ! getent group "$GROUP_ID" > /dev/null 2>&1; then
        echo "Adding group '$GROUP_NAME' with GID $GROUP_ID."
        groupadd -g "$GROUP_ID" "$GROUP_NAME"
        echo ""
    fi

    if ! getent passwd "$USER_ID" > /dev/null 2>&1; then
        # Create a new user account inside the container with:
        #
        # -u "$USER_ID" - Sets the user's numeric ID (UID) to match your host user (e.g., 1000).
        # -g "$GROUP_ID" - Sets the user's primary group ID (GID) to match your host group
        #    (e.g., 1000).
        # --create-home - Creates a home directory for the user (e.g., /home/builder).
        # --shell /bin/bash - Sets the default shell to bash.
        # "$USER_NAME" - The username (e.g., "builder").
        echo "Adding user '$USER_NAME' with UID $USER_ID and GID $GROUP_ID."
        useradd -u "$USER_ID" -g "$GROUP_ID" --create-home --shell /bin/bash "$USER_NAME"

        # Fix ownership of home directory (Docker may have created it as root for volume mounts
        # already mounted here)
        echo "Fixing ownership of home directory."
        # First, the home dir itself.
        chown "$USER_ID:$GROUP_ID" "/home/$USER_NAME"
        ///////// fix ownership only of dirs ABOVE the bind mount; that were auto-created by it!
        # Then, any existing directories in the home dir that are owned by root.
        # find "/home/$USER_NAME" -mindepth 1 -writable -exec chown "$USER_ID:$GROUP_ID" {} +
        echo ""
    fi

    # Print the user's home directory (need bash -c to expand $HOME in the new user's context)
    gosu "$USER_ID:$GROUP_ID" bash -c 'echo "HOME dir is now: $HOME"'

    copy_skel_file "$USER_NAME" ".bash_logout"
    copy_skel_file "$USER_NAME" ".bashrc"
    copy_skel_file "$USER_NAME" ".profile"

    # Run the main command as non-root via gosu
    # - Use `exec` to replace the shell with the command so it receives signals properly.

    echo ""
    # Enable color in the PS1 prompt string for the non-root user; this variable is read by Ubuntu's
    # default `~/.bashrc` file which we copy over via `copy_skel_file` just above, or bind mount in
    # from the host system in `docker_run.sh`.
    export force_color_prompt="yes"
    exec gosu "$USER_ID:$GROUP_ID" "$@"
else
    # Run the main command as root since no user is specified (default behavior)
    # - Use `exect` to replace the shell with the command so it receives signals properly.
    exec "$@"
fi
