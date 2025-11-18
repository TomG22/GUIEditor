PROJ_NAME := GUIEditor
ROOT_DIR :=	..
BUILD_DIR := $(ROOT_DIR)/build
TOOLCHAIN_FILE := $(ROOT_DIR)/toolchain.cmake
MY_CMAKE := cmake


### Unix makefile targets ###

all: $(PROJ_NAME)


# CMake configuration step
configure:
	mkdir -p $(BUILD_DIR)
	cmake -S $(ROOT_DIR) -B $(BUILD_DIR) \
		-DCMAKE_TOOLCHAIN_FILE=$(TOOLCHAIN_FILE)


# CMake build step
$(PROJ_NAME): configure
	$(MY_CMAKE) --build $(BUILD_DIR)


rebuild: clean $(PROJ_NAME)


clean:
	rm -rf $(BUILD_DIR)/*


.PHONY: all configure $(PROJ_NAME) rebuild clean
