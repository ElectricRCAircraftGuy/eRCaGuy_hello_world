# This file is part of https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/

# GS
# Oct. 2026
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
