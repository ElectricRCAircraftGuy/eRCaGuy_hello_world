# See: 
# https://github.com/ElectricRCAircraftGuy/eRCaGuy_Linux_Windows_CMake_Sockets_MSYS2

# Makefile to call a script which calls CMake

# Mark all targets as PHONY (not real files)
.PHONY: all clean debug release portable test
all: \
	debug \
	release \
	portable \
	test

clean:
	rm -rf build/

debug:
	cmake -S . -B build/Debug -DCMAKE_BUILD_TYPE=Debug
	cmake --build build/Debug --config Debug

release:
	cmake -S . -B build/Release -DCMAKE_BUILD_TYPE=Release
	cmake --build build/Release --config Release

portable: release
	./make_portable.sh "poll_server"

# Run the unit tests
test: release
	ctest --test-dir build/Release/ --output-on-failure
