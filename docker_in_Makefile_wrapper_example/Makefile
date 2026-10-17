# This file is part of https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/

# GS
# Oct. 2026
# SEE THIS FILE IN MY STACK OVERFLOW ANSWER HERE:
# How to auto-stop/auto-kill a Docker container or set of Docker Compose
# services/containers after a set amount of time:
# https://stackoverflow.com/a/80005935/4561887
#
# Example usage:
# ```bash
# # View the help menu
# make
# # or
# make help
#
# # Run the container and auto-stop after 3600 sec
# make docker_run
#
# # Run the container with a custom auto-stop time
# make AUTOKILL_TIME_SEC=5 docker_run
# ```


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

# Run a Docker container with auto-kill after `AUTOKILL_TIME_SEC` seconds.
# - See my answer: https://stackoverflow.com/a/80005935/4561887
docker_run:
	@bash -c \
	' \
		AUTOKILL_STILL_ACTIVE_FLAGFILE=$$( \
			mktemp /dev/shm/docker-autokill.XXXXXX \
		) || exit; \
		set -m; \
		( \
			sleep $(AUTOKILL_TIME_SEC) \
				&& rm -- "$$AUTOKILL_STILL_ACTIVE_FLAGFILE" \
				&& docker kill "ubuntu-latest"; \
		) & \
		timer_pgid=$$!; \
		set +m; \
		docker run --name "ubuntu-latest" -it --rm ubuntu bash; \
		docker_status=$$?; \
		if [[ -e "$$AUTOKILL_STILL_ACTIVE_FLAGFILE" ]]; then \
			kill -- "-$$timer_pgid" 2>/dev/null || true; \
			wait -f "$$timer_pgid" 2>/dev/null || true; \
			rm -f -- "$$AUTOKILL_STILL_ACTIVE_FLAGFILE"; \
		elif wait -f "$$timer_pgid"; then \
			printf "\nAutokilling complete...\n"; \
		fi; \
		exit "$$docker_status" \
	'
