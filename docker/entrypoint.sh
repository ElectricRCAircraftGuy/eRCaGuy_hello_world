#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# Docker entrypoint script.
# - This file runs **every time** a container starts.
# - Uses gosu and other tools to establish the user and group inside the container to match the host
#   user's UID and GID, so that files created by the container have the correct ownership and
#   permissions on the host system when bind-mounted via `docker run --volume
#   /HOST-DIR:/CONTAINER-DIR`.
# - Also copies over Ubuntu skel files to the user's home directory if they are not already
#   bind-mounted as read-only from the host system, so that the user has a nice interactive bash
#   experience with color in the PS1 prompt string and other features of the default Ubuntu
#   bash configuration.
# - Takes ownership of the new Docker user's HOME dir and all parent directories up to `/home`
#   to ensure that the Docker user can control their own home dir without `sudo`, even if bind
#   mounts were auto-created by Docker as root inside the Docker user's home dir.
# - Uses gosu to run the passed-in command to `docker run` or to my custom `docker_run.sh` wrapper
#   as a non-root user.
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

# QUIET is passed in as an env var from docker_run.sh. Default to "false" if not set.
QUIET="${QUIET:-"false"}"

# Print only when not in quiet mode.
log() { [ "$QUIET" != "true" ] && echo "$@" || true; }

# See my answer: https://stackoverflow.com/a/60157372/4561887
FULL_PATH_TO_SCRIPT="$(realpath "${BASH_SOURCE[0]}")"
SCRIPT_DIRECTORY="$(dirname "$FULL_PATH_TO_SCRIPT")"
SCRIPT_FILENAME="$(basename "$FULL_PATH_TO_SCRIPT")"

if [ -f "/.dockerenv" ]; then
    log "Running inside a Docker container..."
else
    echo "Error: not running inside a Docker container. Exiting with error so we don't screw"\
        "up the host system." >&2
    exit 1
fi

# Import (source) libraries
. "${REPO_ROOT_DIR}/bash/ansi_color_codes_simple_lib.sh" # `echo_green` et al

# Color log helpers (require ansi_color_codes_simple_lib.sh to be sourced first)
log_blue()   { [ "$QUIET" != "true" ] && echo_blue "$@"   || true; }
log_yellow() { [ "$QUIET" != "true" ] && echo_yellow "$@" || true; }

log "Running entrypoint script: ${FULL_PATH_TO_SCRIPT}"
log "pwd (bind-mounted to host system): $(pwd)"
log "Command being run by entrypoint script:"
log "$*"
log ""

# Copy over Ubuntu skel files if they are not already bind-mounted as read-only from the
# host system.
# - Use gosu to copy as the non-root user so they have correct ownership and permissions.
copy_skel_file() {
    local username="$1"
    local file="$2"
    if [ -f "/home/$username/$file" ]; then
        log "Skel file '/etc/skel/$file' already exists in home directory '/home/$username/'." \
            "Not copying."
    else
        log "Copying skel file '/etc/skel/$file' to home directory '/home/$username/'"
        gosu "$USER_ID:$GROUP_ID" cp "/etc/skel/$file" "/home/$username/"
    fi
}

# Take ownership of all directories from the target path up to `/home/<username>`, inclusive, but
# NOT `/home`, as the non-root user.
# - This is useful when Docker bind mounts (set via calls to
#   `docker run --volume /HOST-DIR:/CONTAINER-DIR`) create parent directories inside the user's
#    home dir as root.
# - It will exit if the target path is not within the user's home directory to avoid taking
#   ownership of unintended directories OUTSIDE the user's home directory.
# - NB: call this function as root. Don't use `gosu`.
#
# Example Usage:
# `take_ownership_of_dirs "/home/gabriel/GS/dev/eRCaGuy_hello_world" "$USER_ID" "$GROUP_ID"`
#
# Example Result: the above example command will take ownership of the following dirs as the
# non-root user:
# - /home/gabriel/
# - /home/gabriel/GS/
# - /home/gabriel/GS/dev/
#
take_ownership_of_dirs() {
    local target_path="$1"
    local user_id="$2"
    local group_id="$3"

    local username=$(getent passwd "$user_id" | cut -d: -f1)

    log "Taking ownership of all parent directories of dir '$target_path' up to dir"
    log "  '/home/$username' as user '$username' with UID $user_id and GID $group_id."

    # First, ensure that path `/home/$username` is part of the passed-in target path. If it is NOT,
    # exit, so we don't modify any dirs outside of the user's home dir.
    # - Note that the `*` below is part of a glob search pattern.
    if [[ "$target_path" != "/home/$username"* ]]; then
        echo "Error: target path '$target_path' is not within '/home/$username'. Exiting" \
            "with error to avoid taking ownership of unintended directories."
        exit 1
    fi

    # Get parent directory (don't include the target itself)
    local current_dir="$(dirname "$target_path")"

    # Collect all parent directories until we reach `/home` or `/`.
    # - We do NOT want to include and chown these dirs!
    local dirs_to_chown=()
    # NB: do NOT put a slash after `/home` or it won't ever match.
    while [ "$current_dir" != "/home" ] && \
          [ "$current_dir" != "/" ]; do
        dirs_to_chown+=("$current_dir")
        current_dir="$(dirname "$current_dir")"
    done

    # Chown directories in reverse order (from /home/user down to parent of target)
    for ((i=${#dirs_to_chown[@]}-1; i>=0; i--)); do
        log "Taking ownership of: ${dirs_to_chown[i]}"
        chown "$user_id:$group_id" "${dirs_to_chown[i]}"
    done

    log ""
}

# If USER_ID and GROUP_ID are provided, create a user and switch to it
if [ -n "$USER_ID" ] && [ -n "$GROUP_ID" ] && [ -n "$USER_NAME" ] && [ -n "$GROUP_NAME" ]; then
    log "Preparing to run the command as as non-root user $USER_NAME:$USER_ID,"\
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
        log "Deleting existing user '$EXISTING_USER_WITH_THIS_ID' with conflicting UID $USER_ID."
        # -r removes home dir; redirect stderr to /dev/null in quiet mode to suppress warnings
        # like `"userdel: ubuntu mail spool (/var/mail/ubuntu) not found"`
        if [ "$QUIET" = "true" ]; then
            userdel -r "$EXISTING_USER_WITH_THIS_ID" 2>/dev/null
        else
            userdel -r "$EXISTING_USER_WITH_THIS_ID"
        fi
        log ""
    fi

    EXISTING_GROUP_WITH_THIS_ID=$(getent group "$GROUP_ID" | cut -d: -f1)
    if [ -n "$EXISTING_GROUP_WITH_THIS_ID" ] && [ "$EXISTING_GROUP_WITH_THIS_ID" != "$GROUP_NAME" ];
    then
        log "Deleting existing group '$EXISTING_GROUP_WITH_THIS_ID' with conflicting GID" \
            "$GROUP_ID."
        if [ "$QUIET" = "true" ]; then
            groupdel "$EXISTING_GROUP_WITH_THIS_ID" 2>/dev/null
        else
            groupdel "$EXISTING_GROUP_WITH_THIS_ID"
        fi
        log ""
    fi

    # 2. Add new group, then user, in that required order.

    if ! getent group "$GROUP_ID" > /dev/null 2>&1; then
        log "Adding group '$GROUP_NAME' with GID $GROUP_ID."
        if [ "$QUIET" = "true" ]; then
            groupadd -g "$GROUP_ID" "$GROUP_NAME" 2>/dev/null
        else
            groupadd -g "$GROUP_ID" "$GROUP_NAME"
        fi
        log ""
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
        log "Adding user '$USER_NAME' with UID $USER_ID and GID $GROUP_ID."
        # Redirect stderr to /dev/null in quiet mode to suppress warnings like:
        # ```
        # useradd: warning: the home directory /home/gabriel already exists.
        # useradd: Not copying any file from skel directory into it.
        # ```
        if [ "$QUIET" = "true" ]; then
            useradd -u "$USER_ID" -g "$GROUP_ID" --create-home --shell /bin/bash "$USER_NAME" 2>/dev/null
        else
            useradd -u "$USER_ID" -g "$GROUP_ID" --create-home --shell /bin/bash "$USER_NAME"
        fi
        log ""
    fi

    # Print the user's home directory (need bash -c to expand $HOME in the new user's context)
    if [ "$QUIET" != "true" ]; then
        gosu "$USER_ID:$GROUP_ID" bash -c 'echo "HOME dir is now: $HOME"'
    fi

    # Fix ownership of home directory.
    # - Docker may have created it as root for all `--volume` bind mounts already mounted therein,
    #   and we need to take user ownership of the mounts' parent dirs within our user's home dir.
    log "Fixing ownership of parent directories inside \"/home/$USER_NAME\" already created"\
        "by Docker bind mounts."
    take_ownership_of_dirs "$TAKE_OWNERSHIP_OF_DIR1" "$USER_ID" "$GROUP_ID"

    copy_skel_file "$USER_NAME" ".bash_logout"
    copy_skel_file "$USER_NAME" ".bashrc"
    copy_skel_file "$USER_NAME" ".profile"

    # Git configuration
    gosu "$USER_ID:$GROUP_ID" git config --global core.editor "nano"

    log ""
    log_yellow "NOTICE: you are now running in Docker as user '$USER_NAME' with UID $USER_ID and"
    log_yellow "GID $GROUP_ID. Home dir is '/home/$USER_NAME'. The current working directory"
    log_yellow "is BIND-MOUNTED to the host system, so any files you create, modify, or delete"
    log_yellow "in '$(pwd)' will also be affected"
    log_yellow "on your host system!"
    log ""

    # Enable color in the PS1 prompt string for the non-root user; this variable is read by Ubuntu's
    # default `~/.bashrc` file which we copy over via `copy_skel_file` just above, or bind mount in
    # from the host system in `docker_run.sh`.
    export force_color_prompt="yes"
    # Run the main command as non-root via gosu
    # - Use `exec` to replace the shell with the command so it receives signals properly.
    exec gosu "$USER_ID:$GROUP_ID" "$@"
else
    # Run the main command as root since no user is specified (default behavior)
    # - Use `exec` to replace the shell with the command so it receives signals properly.
    exec "$@"
fi
