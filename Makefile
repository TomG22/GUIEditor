PROJ_NAME := GUIEditor

### Unix makefile targets ###

all: $(PROJ_NAME)


# CMake configuration step
configure:
	mkdir -p build
	cmake -S . -B build \
		-DCMAKE_TOOLCHAIN_FILE=toolchain.cmake


# CMake build step
$(PROJ_NAME): configure
	$(MY_CMAKE) --build build


rebuild: clean $(PROJ_NAME)


clean:
	rm -rf build/*


.PHONY: all configure $(PROJ_NAME) rebuild clean



###  Windows makefile targets ###

all-win64: $(PROJ_NAME)-win64


# CMake configuration step
configure-win64:
	cmd.exe /C "build.bat configure"


# CMake build step
$(PROJ_NAME)-win64:
	cmd.exe /C "build.bat build"


rebuild-win64:
	cmd.exe /C "build.bat rebuild"


clean-win64:
	cmd.exe /C "build.bat clean"


.PHONY: all-win64 configure-win64 $(PROJ_NAME)-win64 rebuild-win64 clean-win64
