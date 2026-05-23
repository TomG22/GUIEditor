BUILD_DIR ?= build
BUILD_EXAMPLES ?=
BUILD_TYPE ?= Debug
GENERATOR ?=
TARGET ?=
WAYLAND ?= OFF


ifeq ($(TARGET),windows)
    TOOLCHAIN := windows-mingw.cmake
endif


CMAKE_ARGS := -B $(BUILD_DIR) \
			  -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) \
			  -DGLFW_BUILD_WAYLAND=$(WAYLAND)


ifdef BUILD_EXAMPLES
    CMAKE_ARGS += -DBUILD_EXAMPLES=$(BUILD_EXAMPLES)
endif

ifdef GENERATOR
    CMAKE_ARGS += -G $(GENERATOR)
endif

ifdef TOOLCHAIN
    CMAKE_ARGS += -DCMAKE_TOOLCHAIN_FILE=$(TOOLCHAIN)
endif


.DEFAULT_GOAL := build


$(BUILD_DIR)/.cmake_args: .cmake_args_check
	cmake -E make_directory $(BUILD_DIR)
	@echo "$(CMAKE_ARGS)" > $(BUILD_DIR)/.cmake_args.tmp
	cmake -E compare_files $(BUILD_DIR)/.cmake_args.tmp $(BUILD_DIR)/.cmake_args || \
		cmake -E copy $(BUILD_DIR)/.cmake_args.tmp $(BUILD_DIR)/.cmake_args
	cmake -E remove $(BUILD_DIR)/.cmake_args.tmp


$(BUILD_DIR)/.cmake_stamp: CMakeLists.txt $(TOOLCHAIN) $(BUILD_DIR)/.cmake_args Makefile
	cmake $(CMAKE_ARGS)
	cmake -E touch $@


build: $(BUILD_DIR)/.cmake_stamp
	cmake --build $(BUILD_DIR)


rebuild:
	$(MAKE) clean
	$(MAKE) build


clean:
	cmake -E remove_directory $(BUILD_DIR)


.PHONY: build rebuild clean .cmake_args_check
