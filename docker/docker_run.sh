#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world
#
# GS
# Feb. 2026
#
# Run a Docker container instance of the Docker Image and Tag named `$IMAGE_NAME:$IMAGE_TAG`
# for cross-compiling executables from Linux to Windows.
#

# See my answer: https://stackoverflow.com/a/60157372/4561887
FULL_PATH_TO_SCRIPT="$(realpath "${BASH_SOURCE[0]}")"
SCRIPT_DIRECTORY="$(dirname "$FULL_PATH_TO_SCRIPT")"

# Source (import) libraries
. "${SCRIPT_DIRECTORY}/../bash/ansi_color_codes_simple_lib.sh" # `echo_green` et al
. "${SCRIPT_DIRECTORY}/docker_config.sh"  # For `IMAGE_NAME` and `IMAGE_TAG` variables

REPO_ROOT_DIR="$(git rev-parse --show-toplevel)"

echo "Running Docker image: ${IMAGE_NAME}:${IMAGE_TAG}"
echo ""
echo "Running as user UID=$(id -u) and group GID=$(id -g)"
echo_blue "Mounting host dirs to container dirs:"
echo_blue "- ${REPO_ROOT_DIR} -> ${REPO_ROOT_DIR}"
echo ""

# Replicate a container name somewhat similar to what `docker compose run` would do if we were
# using `docker compose run` instead of `docker run`
#
# Last 8 chars of a hash over the "sec.ns" timestamp since epoch.
UNIQUE_HASH="$(date "+%s.%N" | sha256sum | cut -c1-8)"
CONTAINER_NAME="${IMAGE_NAME}-${IMAGE_TAG}-${UNIQUE_HASH}"

# Run a container instance of the Docker image and tag "${IMAGE_NAME}:${IMAGE_TAG}" with the
# following options:
#
# * --rm = Automatically remove the container when it exits.
# * -it = Give the container an interactive terminal.
# * --env USER_ID=$(id -u) = Pass the host user's UID to the container (for gosu).
# * --env GROUP_ID=$(id -g) = Pass the host user's GID to the container (for gosu).
# * --env ... = other environmental variable options.
# * --volume /HOST-DIR:/CONTAINER-DIR = Bind mount the workspace directory outside the docker
#     container to inside the container so you can access your code.
# *   Also mount the host's `~/.bashrc` file to the container as read-only, to be used by the
#     container's ENTRYPOINT script if desired.
# * --workdir = Set the working directory inside the container. This is where the interactive
#     prompt will start.
# * --name = set this as the container name as shown by `docker ps` outside the container but
#     while it is running.
# * --hostname = set the container's hostname, as shown by `hostname` and in the PS1
#     prompt string as `user@hostname` inside the running container.
# * "${IMAGE_NAME}:${IMAGE_TAG}" = The name of the already-built Docker image and tag to run.
# * "$@" = All additional arguments passed to this script, forwarded to `docker run`.
#      Ex: `./docker_run.sh bash -c "cd cpp && x86_64-w64-mingw32-g++ --version"`
#
docker_args=(
    --rm
    -it
    # Pass user/group IDs and names for proper file permissions (used by gosu in ENTRYPOINT)
    --env USER_ID="$(id -u)"
    --env GROUP_ID="$(id -g)"
    --env USER_NAME="$(id -un)"
    --env GROUP_NAME="$(id -gn)"
    # Directory to take ownership of inside the container
    --env TAKE_OWNERSHIP_OF_DIR1="${REPO_ROOT_DIR}"
    --env REPO_ROOT_DIR="${REPO_ROOT_DIR}"
    # Bind mount the workspace and bashrc file
    --volume "${REPO_ROOT_DIR}:${REPO_ROOT_DIR}"
    --volume "${HOME}/.bashrc:${HOME}/.bashrc:ro"
    # Set working directory and container identity
    --workdir "${REPO_ROOT_DIR}"
    --name "$CONTAINER_NAME"
    --hostname "$CONTAINER_NAME"
)

docker run "${docker_args[@]}" "${IMAGE_NAME}:${IMAGE_TAG}" "$@"
