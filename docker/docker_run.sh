#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world
#
# GS
# Feb. 2026
#
# Run the `$IMAGE_NAME:$IMAGE_TAG` Docker container for cross-compiling executables from Linux to
# Windows
#

# See my answer: https://stackoverflow.com/a/60157372/4561887
FULL_PATH_TO_SCRIPT="$(realpath "${BASH_SOURCE[0]}")"
SCRIPT_DIRECTORY="$(dirname "$FULL_PATH_TO_SCRIPT")"

# Source (import) libraries
. "${SCRIPT_DIRECTORY}/docker_config.sh"  # For `IMAGE_NAME` and `IMAGE_TAG` variables

REPO_ROOT="$(realpath "${SCRIPT_DIRECTORY}/..")"

echo "Running Docker container: ${IMAGE_NAME}:${IMAGE_TAG}"
echo ""
echo "Running as user UID=$(id -u) and group GID=$(id -g)"
echo "Mounting host dirs to container dirs:"
echo "- ${REPO_ROOT} -> ${REPO_ROOT}"
echo ""

# Run the docker container with the following options:
#
# * `--rm`: Automatically remove the container when it exits.
# * `-it`: Give the container an interactive terminal.
# * `--env USER_ID=$(id -u)`: Pass the host user's UID to the container (for gosu).
# * `--env GROUP_ID=$(id -g)`: Pass the host user's GID to the container (for gosu).
# * ...other `--env` options.
# * `--volume /HOST-DIR:/CONTAINER-DIR`: Bind mount the workspace directory outside the docker
#    container to inside the container so you can access your code.
# * Also mount the host's `~/.bashrc` file to the container's `~/.bashrc` file as read-only.
# * `--workdir`: Set the working directory inside the container.
# * `"${IMAGE_NAME}:${IMAGE_TAG}"`: Run this container
# * `"$@"`: Pass additional arguments to `docker run`.
#    Ex: `./docker_run.sh bash -c "cd cpp && x86_64-w64-mingw32-g++ --version"`
#
docker run \
    --rm \
    -it \
    --env USER_ID="$(id -u)" \
    --env GROUP_ID="$(id -g)" \
    --env USER_NAME="$(id -un)" \
    --env GROUP_NAME="$(id -gn)" \
    --volume "${REPO_ROOT}:${REPO_ROOT}" \
    --volume "${HOME}/.bashrc:${HOME}/.bashrc:ro" \
    --workdir "${REPO_ROOT}" \
    "${IMAGE_NAME}:${IMAGE_TAG}" \
    "$@"
