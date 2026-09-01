# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world
#
# GS
# Aug. 2026
#
# ANSI color codes for message printing.
# - Inspired by:
#   https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/bash/ansi_color_codes.sh
#
# Example usage:
# ```cmake
# include("${CMAKE_SOURCE_DIR}/path/to/eRCaGuy_hello_world/cmake/ansi_colors.cmake")
# message_yellow(STATUS "This is a yellow message printed during CMake configuration.")
# ```
#

string(ASCII 27 ANSI_ESCAPE)

set(ANSI_START "${ANSI_ESCAPE}[")
set(ANSI_END "m")
# The combination of ANSI_START + ANSI_END with no numeric codes in between.
set(ANSI_OFF "${ANSI_START}${ANSI_END}")

set(ANSI_BOLD ";1")
set(ANSI_SLOW_BLINK ";5")
set(ANSI_FAST_BLINK ";6")  # Not widely supported.
set(ANSI_FG_BLK ";30")     # Foreground color black.
set(ANSI_BG_BLK ";40")     # Background color black.
set(ANSI_FG_RED ";31")     # Foreground color red.
set(ANSI_FG_BR_RED ";91")  # Foreground color bright red.
set(ANSI_BG_RED ";41")     # Background color red.
set(ANSI_FG_GRE ";32")     # Foreground color green.
set(ANSI_BG_GRE ";42")     # Background color green.
set(ANSI_FG_BLU ";34")     # Foreground color blue.
set(ANSI_FG_BR_BLU ";94")  # Foreground color bright blue.
set(ANSI_BG_BLU ";44")     # Background color blue.
set(ANSI_BG_BR_BLU ";104") # Background color bright blue.
set(ANSI_FG_BR_YLW ";93")  # Foreground color bright yellow.
set(ANSI_BG_BR_YLW ";103") # Background color bright yellow.

set(ANSI_BLUE "${ANSI_START}${ANSI_FG_BR_BLU}${ANSI_END}")
set(ANSI_GREEN "${ANSI_START}${ANSI_FG_GRE}${ANSI_END}")
set(ANSI_YELLOW "${ANSI_START}${ANSI_FG_BR_YLW}${ANSI_END}")
set(ANSI_RED "${ANSI_START}${ANSI_FG_BR_RED}${ANSI_END}")

# See CMake `message` modes here: https://cmake.org/cmake/help/latest/command/message.html
set(ANSI_MESSAGE_MODES
	# General messages:
	FATAL_ERROR
	SEND_ERROR
	WARNING
	AUTHOR_WARNING
	DEPRECATION
	NOTICE
	STATUS
	VERBOSE
	DEBUG
	TRACE

	# Reporting checks:
	CHECK_START
	CHECK_PASS
	CHECK_FAIL

	# Configure Log:
	CONFIGURE_LOG
)

function(_message_in_color ansi_formatting_str mode)
	list(FIND ANSI_MESSAGE_MODES "${mode}" mode_index)
	if(mode_index EQUAL -1)
		message(
			FATAL_ERROR
			"Colored message helpers only support message(<mode> <text>...) forms. "
			"Got first argument: ${mode}"
		)
	endif()

    # Call the built-in `message()` function with the captured `mode` and the ANSI color formatting
    # applied to the message text.
    # - See: https://cmake.org/cmake/help/latest/command/message.html
	message(${mode} "${ansi_formatting_str}" ${ARGN} "${ANSI_OFF}")
endfunction()


# message_blue, message_green, message_yellow, and message_red are wrappers around the
# `_message_in_color` function, which is a wrapper around the built-in `message()` function.
#
# NB: "ARGN holds the list of arguments past the last expected argument."
# See: https://cmake.org/cmake/help/latest/command/function.html
#
# Example usage:
#  message_yellow(STATUS "This is a yellow message.")
#

function(message_blue mode)
	_message_in_color("${ANSI_BLUE}" "${mode}" ${ARGN})
endfunction()

function(message_green mode)
	_message_in_color("${ANSI_GREEN}" "${mode}" ${ARGN})
endfunction()

function(message_yellow mode)
	_message_in_color("${ANSI_YELLOW}" "${mode}" ${ARGN})
endfunction()

function(message_red mode)
	_message_in_color("${ANSI_RED}" "${mode}" ${ARGN})
endfunction()
