<!--
https://stackoverflow.com/a/80005935/4561887
-->


## How to auto-stop/auto-kill a Docker container or set of Docker Compose services/containers after a set amount of time

After much trial and error and effort, this is what I finally settled on. It works perfectly!

The [main answer](https://stackoverflow.com/a/48299490/4561887) says to use `timeout`. That only works in interactive shells. In scripts, however, it does not work properly. From [my comment](https://stackoverflow.com/questions/48299352/how-to-limit-docker-run-execution-time/80005935#comment141181416_48299490):

> I tried `timeout` for hours. Unfortunately, while it _does_ work in an active shell, it does not work inside a script or Makefile. Even with `timeout --foreground`, Docker Compose captures the kill signal and it never gets forwarded to the individual running containers. After hours of terrible and hacky solutions, finally, I came up with this answer which does work everywhere I need it to and is _super simple_: [How to auto-kill a set of Docker Compose services/containers after a set amount of time](https://stackoverflow.com/a/80005935/4561887).


## Quick summary

Here's the most basic fully-functional example, and _unlike `timeout`_, this technique works inside of scripts and `Makefile`s too!:

1. In Bash:

    `docker_run_with_autokill.sh`:
    ```bash
    # 1. Start autokill timer
    set -m  # enable job control
    sleep 30 && docker kill "ubuntu-latest" &
    timer_pgid="$!"
    set +m  # disable job control

    # 2. Run the container
    docker run --name "ubuntu-latest" -it --rm ubuntu bash
    docker_status="$?"

    # 3. In case the user stops the Docker container early with Ctrl+C, 
    #    kill the timer and exit
    kill -- "-$timer_pgid" 2>/dev/null
    wait -f "$timer_pgid" 2>/dev/null
    exit "$docker_status"
    ```

2. In a `Makefile`:

    Here is a full `Makefile` example. If you copy-paste this, be sure to convert spaces to tabs for indentation in the `Makefile`!:

    [`docker_in_Makefile_wrapper_example/Makefile`](https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/docker_in_Makefile_wrapper_example/Makefile) in my [eRCaGuy_hello_world](https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world) repo:
    ```make
    # Automatically kill running docker containers after this long: 1 hour
    AUTOKILL_TIME_SEC := 3600

    # Specify the default target to run when you just run `make`
    .DEFAULT_GOAL := help

    # Help target to show available commands
    help:
        @{ \
        echo "Primary targets:"; \
        echo "  help       - show this help message"; \
        echo ""; \
        echo "Docker commands:"; \
        echo "  docker_run - Run the latest version of Ubuntu in Docker; automatically stops after AUTOKILL_TIME_SEC=$(AUTOKILL_TIME_SEC) seconds, which is adjustable:"; \
        echo "               Ex: 'make AUTOKILL_TIME_SEC=5 docker_run'"; \
        } | less -RFX

    # Declare which targets are not real files
    .PHONY: \
        help \
        docker_run

    # Run a Docker container with auto-kill after `AUTOKILL_TIME_SEC` seconds
    docker_run:
        @bash -c \
        ' \
            set -m; \
            sleep $(AUTOKILL_TIME_SEC) \
                && docker kill "ubuntu-latest" \
                && echo "Autokilling complete..." & \
            timer_pgid=$$!; \
            set +m; \
            docker run --name "ubuntu-latest" -it --rm ubuntu bash; \
            docker_status=$$?; \
            kill -- "-$$timer_pgid" 2>/dev/null || true; \
            wait -f "$$timer_pgid" 2>/dev/null || true; \
            exit "$$docker_status" \
        '
    ```

    Example usage:
    ```bash
    # View the help menu
    make
    # or
    make help

    # Run the latest version of Ubuntu in a Docker container 
    # and auto-stop after 3600 sec
    make docker_run

    # Run the latest version of Ubuntu in a Docker container
    # with a custom auto-stop time of 5 sec
    make AUTOKILL_TIME_SEC=5 docker_run
    ```


## Details


## 1. Introduction, and `docker run` with auto-kill

**The simplest solution if you will never use <kbd>Ctrl</kbd>+<kbd>C</kbd> to stop the container before the sleep ends:**

To auto-kill the Docker image after a set amount of time, we use `sleep`, `docker kill`, and a named container we can reference with `docker kill`. Notice that putting an ampersand (`&`) at the end of a line causes that line to run in a background process so that the next line after it is run immediately in the main foreground process. That's super important here:

```bash
# Open the latest version of ubuntu in an interactive (`-i`) tty (`-t`) 
# Bash terminal in Docker, in a container named "ubuntu-latest", and
# auto-kill it after 30 seconds.
sleep 30 && docker kill "ubuntu-latest" &
docker run --name "ubuntu-latest" -it --rm ubuntu bash
```

**Problem 1: Sleep still runs after container stops:**

There's a problem here, though. If you use <kbd>Ctrl</kbd>+<kbd>C</kbd> to stop the container before the sleep ends, the sleep command will still run and try to kill the container that is already stopped. This can especially become confusing if you run the whole command again before the first sleep expires, as the old sleep from the previous run will finish and kill your current run at an unexpected time. 

You can monitor all `sleep` processes live and see this in effect using this command:
```bash
# Monitor `sleep` processes, updating them every 1 second (`-n 1`).
# - NB: the `[s]leep` trick avoids matching the `grep` itself.
watch --color -n 1 'ps aux | grep --color=always "[s]leep"'
```

**The solution** is to auto-kill the sleep command if the user manually stops the container early. Here's how to do that. We now have 3 steps:
```bash
# 1. Start the autokill sleep timer in the background.
#
# Enable process "job control"; see: `set --help` and
# https://www.gnu.org/software/bash/manual/html_node/Job-Control-Basics.html
set -m  # enable job control
sleep 30 && docker kill "ubuntu-latest" &
# Grab the sleep timer Process Group ID (PGID) so we can kill
# the whole process group above later.
timer_pgid="$!"
set +m  # disable job control

# 2. Start the Docker container
docker run --name "ubuntu-latest" -it --rm ubuntu bash
docker_status="$?"

# 3. In case Ctrl+C is pressed to exit the Docker container early,
#    clean up / kill the sleep timer and exit with Docker's status.
#   - The dash in `-$timer_pgid` is required to specify to kill the 
#     whole process group, not just a single process. 
kill -- "-$timer_pgid" 2>/dev/null
wait -f "$timer_pgid" 2>/dev/null
# Do NOT use this line if copy-pasting these commands directly into an 
# interactive shell! The `exit` is for usage within scripts only.
exit "$docker_status"
```

Here is what that looks like with minimal comments:
```bash
# 1. Start autokill timer
set -m  # enable job control
sleep 30 && docker kill "ubuntu-latest" &
timer_pgid="$!"
set +m  # disable job control

# 2. Run the container
docker run --name "ubuntu-latest" -it --rm ubuntu bash
docker_status="$?"

# 3. In case the user stops the Docker container early with Ctrl+C, 
#    kill the timer and exit
kill -- "-$timer_pgid" 2>/dev/null
wait -f "$timer_pgid" 2>/dev/null
exit "$docker_status"
```

**Problem 2: running many containers at once doesn't work if they all have the same container name:**

If you need to run many containers at once, each needs their own unique container `--name` to be auto-killed after the sleep. An easy way to do this is to append to the container name a timestamp down to the nanoseconds, with format `YYYY.MM.DD-HH.MM.SS.NNNNNNNNN`. That can be achieved with the `date` command in Bash, like this: `date +%Y.%m.%d-%H.%M.%S.%N`. 

Here is that full Docker command:
```bash
TIMESTAMP=$(date +%Y.%m.%d-%H.%M.%S.%N)
CONTAINER_NAME="ubuntu-latest-$TIMESTAMP"

# 1. Start autokill timer
set -m  # enable job control
sleep 30 && docker kill "$CONTAINER_NAME" &
timer_pgid="$!"
set +m  # disable job control

# 2. Run the container
docker run --name "$CONTAINER_NAME" -it --rm ubuntu bash
docker_status="$?"

# 3. In case the user stops the Docker container early with Ctrl+C, 
#    kill the timer and exit
kill -- "-$timer_pgid" 2>/dev/null
wait -f "$timer_pgid" 2>/dev/null
exit "$docker_status"
```


## 2. `docker compose run` with auto-kill

Here's an example with `docker compose run` to start and auto-kill a single service/container defined in a custom `compose.yml` file. It follows the same principles as above. Here I choose to use `docker stop` to send the `INT` <kbd>Ctrl</kbd>+<kbd>C</kbd> interrupt signal to the running container instead of the default and harsher `KILL` signal. This is because I programmed the executable running in this container to explicitly terminate the program when the <kbd>Ctrl</kbd>+<kbd>C</kbd> `INT` interrupt signal is received. If the container doesn't stop within a default time of 10 seconds on Linux (see: https://docs.docker.com/reference/cli/docker/container/stop/), `docker stop` then automatically sends the harsher `KILL` signal. 

```bash
# 1. Start autokill timer
set -m  # enable job control
sleep 30 && docker stop -s INT my-container-name \
    && echo "" && echo "Autokilling complete..." &
timer_pgid="$!"
set +m  # disable job control

# 2. Run the container
docker compose \
    -f compose.yml \
    --env-file .docker.env \
    run \
    --rm \
    --name my-container-name \
    my-service
docker_status="$?"

# 3. In case the user stops the Docker container early with Ctrl+C, 
#    kill the timer and exit
kill -- "-$timer_pgid" 2>/dev/null
wait -f "$timer_pgid" 2>/dev/null
exit "$docker_status"
```

What's cool about the above auto-stop/auto-kill timer is that you will only see `Autokilling complete...` at the end if the sleep timer is what stops the container. If you stop it manually with <kbd>Ctrl</kbd>+<kbd>C</kbd>, you won't see it. This way, you know easily that the sleep timer is what stopped it.


## 3. `docker compose up` with auto-kill

Here's a super simple example to start and auto-kill many services/containers at once, all defined in your custom `compose.yml` file:

```bash
# 1. Start autokill timer to stop the running containers after 30 seconds
set -m  # enable job control
sleep 30 && docker compose down \
    && echo "" && echo "Autokilling complete...Press Enter to exit." &
timer_pgid="$!"
set +m  # disable job control

# 2. Start the containers
docker compose up
docker_status="$?"

# 3. In case the user stops the Docker container early with Ctrl+C, 
#    kill the timer and exit
kill -- "-$timer_pgid" 2>/dev/null
wait -f "$timer_pgid" 2>/dev/null
exit "$docker_status"
```

Here's a more-complete example with a configurable auto-kill time, and passing more arguments to the `docker compose up` and `docker compose down` commands:

```bash
# Automatically stop/kill docker images after this long; ex: to avoid 
# long log build-up: 1 hour
AUTOKILL_TIME_SEC="3600"

# 1. Configure a background sleep process to wake up and stop/kill the 
#    Docker containers after the specified amount of time.
set -m  # enable job control
sleep "$AUTOKILL_TIME_SEC" \
    && docker compose \
        -f compose.yml \
        --env-file .docker.env \
        down \
    && echo "" \
    && echo "Autokilling complete...All docker containers stopped" \
            "and removed. Press Enter to exit." &
timer_pgid="$!"
set +m  # disable job control

# 2. Now start the Docker containers normally. They will be automatically 
#    killed after the specified amount of time when the sleep process 
#    terminates, OR if you hit Ctrl+C in the terminal manually.
docker compose \
    -f compose.yml \
    --env-file .docker.env \
    up \
        myservice1 \
        myservice2 \
        myservice3
docker_status="$?"

# 3. In case the user stops the Docker container early with Ctrl+C, 
#    kill the timer and exit
kill -- "-$timer_pgid" 2>/dev/null
wait -f "$timer_pgid" 2>/dev/null
exit "$docker_status"
```

It works! I'm very happy to have finally figured out the above patterns and techniques to auto-kill containers, as I have not seen them used before, and it was a lot of work. 


## Process groups 

Remember that what allows us to kill the `sleep && docker stop && echo` type string of commands is using _process groups._ That is enabled in the shell with `set -m` and disabled with `set +m`. It is disabled by default. When enabled, `$!` grabs a Process Group ID, or PGID (instead of a regular Process ID, or PID), and you must put a minus sign (`-`) before it to kill the whole group, as in: `kill -- "-$timer_pgid"`. 

References: 
1. Enable process "job control"; see: `set --help` and:
1. https://www.gnu.org/software/bash/manual/html_node/Job-Control-Basics.html


## A few notes about `docker stop` vs `docker kill`, and also `docker compose down`

1. `docker stop` sends a `SIGTERM` signal to the container, allowing it to gracefully shut down. If the container does not stop within a default timeout (10 seconds on Linux), it then sends a `SIGKILL` signal to forcefully terminate the container.
1. `docker kill` immediately sends a `SIGKILL` signal to the container, forcefully terminating it without giving it a chance to clean up.
1. `docker compose down` stops and removes all the containers defined in the Compose file. It is equivalent to running `docker stop` on all the containers followed by `docker rm` to remove them. This is useful for cleaning up all resources associated with a Compose project. Like `docker stop`, it first sends the graceful `SIGTERM` signal to the containers before forcefully terminating them with `SIGKILL` if they do not stop within the default timeout (10 seconds on Linux). 

See `man docker stop`, `man docker kill`, `docker stop --help`, `docker kill --help`, and `docker compose down --help` for more information. Both `docker stop` and `docker kill` offer a `-s` option to specify the signal to send to the container. Ex: `-s INT` or `-s SIGINT` (same thing) to send the <kbd>Ctrl</kbd>+<kbd>C</kbd> interrupt signal to the running container.

`docker stop` and `docker compose down` both attempt to gracefully stop running containers before harshly killing them. Therefore, both also have a `-t` timeout option to specify the number of seconds to wait for the container to gracefully stop with the first `SIGTERM` signal before sending a harsher `SIGKILL` signal. For example, `docker stop -t 30 mycontainer`, or `docker compose down -t 30`, will wait up to 30 seconds for the container(s) to gracefully shut down with the `SIGTERM` signal before forcefully terminating them with the `SIGKILL` signal.

In general, prefer `docker stop` and `docker compose down` for a graceful shutdown, and use `docker kill` only when you need to instantly forcefully terminate a container.


## Going further
1. There is also a `docker compose kill` that you can use to send a custom signal such as `INT` to a group of services before calling `docker compose down`. See: https://docs.docker.com/reference/cli/docker/compose/kill/. 


## See also

1. My `Makefile` Docker wrapper example: [`docker_in_Makefile_wrapper_example/Makefile`](https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/docker_in_Makefile_wrapper_example/Makefile) in my [eRCaGuy_hello_world](https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world) repo:
1. My answer: [Auto stop Docker container after particular duration](https://stackoverflow.com/a/80005937/4561887)
1. `docker container stop`/`docker stop`: https://docs.docker.com/reference/cli/docker/container/stop/
1. `docker container kill`/`docker kill`: https://docs.docker.com/reference/cli/docker/container/kill/




