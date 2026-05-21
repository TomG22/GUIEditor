BUILD_DIR ?= build
BUILD_EXAMPLES ?=
BUILD_TYPE ?= Debug
GENERATOR ?=
TARGET ?=


ifeq ($(TARGET),windows)
    TOOLCHAIN := toolchains/windows-mingw.cmake
endif


CMAKE_ARGS := -B $(BUILD_DIR) \
			  -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)


ifdef BUILD_EXAMPLES
    CMAKE_ARGS += -DBUILD_EXAMPLES=$(BUILD_EXAMPLES)
endif

ifdef GENERATOR
    CMAKE_ARGS += -DCMAKE_GENERATOR=$(GENERATOR)
endif

ifdef TOOLCHAIN
    CMAKE_ARGS += -DCMAKE_TOOLCHAIN_FILE=$(TOOLCHAIN)
endif


.DEFAULT_GOAL := build


build: $(BUILD_DIR)/CMakeCache.txt
	cmake --build $(BUILD_DIR)


$(BUILD_DIR)/CMakeCache.txt: CMakeLists.txt $(TOOLCHAIN) Makefile
	cmake -E make_directory $(BUILD_DIR)
	cmake $(CMAKE_ARGS)


rebuild:
	$(MAKE) clean
	$(MAKE) build


clean:
	cmake -E remove_directory $(BUILD_DIR)


.PHONY: build rebuild clean
