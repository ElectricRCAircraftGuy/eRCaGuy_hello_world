
Oct. 2026  
Claude Opus 5.5 commentary on my answer. 


## Where the article is right

- **Using `set -m` to kill the whole timer group.** With job control on, the background `sleep … && docker kill …` list gets its own process group, so `kill -- "-$pgid"` stops both `sleep` and the pending `docker kill`. Without `set -m`, a background job in a script shares the script's group, so the negative-PGID kill would fail.
- **Its advice on `docker stop`, `docker kill` and `docker compose down`.** The signal and grace-period details are correct.
- **The Makefile escaping.** `$$!` and `$$?` are correct.

## Where it's wrong or misleading

1. **"`timeout` doesn't work in scripts" is the wrong diagnosis.** The actual causes are:
   - **The docker CLI is only a client.** Killing it doesn't stop the container, which keeps running in the daemon.
   - **PID 1 in a container ignores signals it has no handler for.** So `bash` as PID 1 ignores SIGTERM and SIGINT even when docker forwards them. Running with `--init` (tini) fixes this.
   - **Without `--foreground`, `timeout` runs the command in a background process group.** A `-it` docker reading the TTY then gets SIGTTIN and stops.
2. **`$!` doesn't return a PGID.** It's always a PID. With `set -m` it happens to equal the job's PGID because the job leader is the group leader.
3. **`wait -f` needs bash 5.1 or newer.** On older bash it errors with "invalid option". The `2>/dev/null` hides the message but not the non-zero exit, so a script running under `set -e` would abort there.

## Robustness gaps

- **Cleanup can be skipped.** If the script is killed, or bash exits on SIGINT before reaching step 3, the timer lives on in its own process group. Later it kills whatever container has that name, which is the exact problem the author was trying to avoid. A `trap` is safer than inline cleanup:
  ```bash
  set -m
  sleep "$T" && docker stop "$NAME" &
  timer_pgid=$!
  set +m
  trap 'kill -- "-$timer_pgid" 2>/dev/null' EXIT
  docker run --init --name "$NAME" --rm ubuntu ...
  ```
- **Image pull time counts against the timer.** The `sleep` starts before `docker run`. If the pull takes longer than the timeout, `docker kill` fails with "No such container" and the container then runs with no limit. Running `docker pull` first, or starting the container with `-d` before arming the timer, avoids this.
- **`docker stop -s` needs Docker 23.0 or newer.** Older CLIs don't have the `--signal` flag.
- **"Press Enter to exit" is cosmetic.** Background output prints after the shell prompt, so the terminal only looks like it's hanging.

## Simpler alternatives

- **Put the timeout inside the container:**
  ```bash
  docker run --init --rm ubuntu timeout 30 <cmd>
  ```
- **For non-interactive runs, start detached and use `docker wait`.** No process-group tricks are needed:
  ```bash
  id=$(docker run -d --init ubuntu <cmd>)
  timeout 30 docker wait "$id" || docker stop "$id"
  ```
- **For a single container, `timeout --foreground` works** if you add `--init` (or the program handles signals).
