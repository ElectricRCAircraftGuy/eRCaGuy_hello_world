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

EXECUTABLE_NAME="$(basename "$0")"
print_help() {
    cat <<EOF
Usage: $EXECUTABLE_NAME [OPTIONS] [-- COMMAND [ARGS...]]

Run a Docker container instance of '${IMAGE_NAME}:${IMAGE_TAG}' for cross-compiling
from Linux to Windows.

If no COMMAND is given, drops into an interactive bash shell inside the container.

OPTIONS:
  -h, -?, --help   Show this help menu and exit.
  -q, --quiet      Suppress all informational log messages (errors still print).
  --               Mark the end of options. Everything after this is passed verbatim as the
                   container command and its arguments.

EXAMPLES:
  # Drop into an interactive bash shell:
  $EXECUTABLE_NAME

  # Drop into an interactive bash shell, suppressing startup log messages:
  $EXECUTABLE_NAME --quiet

  # Run the single command inside the container, then exit:
  $EXECUTABLE_NAME -- x86_64-w64-mingw32-g++ --version

  # Run a build command quietly (first '-q'/'--quiet' is ours; '--quiet' at end goes to make):
  $EXECUTABLE_NAME -q -- make --quiet

  # Run a command that itself uses '--quiet' (without '--', it would be consumed by us):
  $EXECUTABLE_NAME -- myprogram --quiet

  # Compile a C++ file for Windows:
  $EXECUTABLE_NAME -- bash -c "cd cpp && x86_64-w64-mingw32-g++ myfile.cpp -o myfile.exe"

DOCKER IMAGE:
  Image:    ${IMAGE_NAME}
  Tag:      ${IMAGE_TAG}
  Full:     ${IMAGE_NAME}:${IMAGE_TAG}

HOST BIND MOUNTS: HOST-DIR -> CONTAINER-DIR:
  ${REPO_ROOT_DIR}  ->  ${REPO_ROOT_DIR}
  ${HOME}/.bashrc   ->  ${HOME}/.bashrc  (read-only)

EOF
}

# Parse our own flags that come BEFORE `--`.
# Everything after `--` is passed through verbatim to the container command.
# This follows the POSIX/Unix convention used by git, ssh, find, etc.
#
# Usage examples:
#   ./docker_run.sh                        # interactive bash shell, verbose
#   ./docker_run.sh --quiet                # interactive bash shell, quiet
#   ./docker_run.sh -- myprogram --quiet   # passes --quiet to myprogram, not us
#   ./docker_run.sh -q -- make --quiet     # quiet docker_run.sh; passes --quiet to make
#
QUIET="false"
while [[ $# -gt 0 ]]; do
    case "$1" in
        # Help menu
        "--help"|"-h"|"-?")
            print_help
            exit 0
            ;;
        # Quiet: don't echo nor print log messages
        "--quiet"|"-q")
            QUIET="true"
            shift # past argument
            ;;
        # End of our flags; everything remaining is passed through to the container command
        "--")
            shift # past argument
            break
            ;;
        # Stop parsing our flags at the first unrecognized arg; pass it and everything after through
        *)
            break
            ;;
    esac
done
# Remaining args in "$@" are now passed through verbatim to the container command

# Print only when not in quiet mode
# - Return true if if `$QUIET` is not "true", to return a non-error exit code regardless.
log()      { [ "$QUIET" != "true" ] && echo "$@"      || true; }
log_blue() { [ "$QUIET" != "true" ] && echo_blue "$@" || true; }

echo "Running Docker image: ${IMAGE_NAME}:${IMAGE_TAG}"
echo ""
log "Running as user UID=$(id -u) and group GID=$(id -g)"
log_blue "Mounting host dirs to container dirs:"
log_blue "- ${REPO_ROOT_DIR} -> ${REPO_ROOT_DIR}"
log ""

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
    --env QUIET="${QUIET}"
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
