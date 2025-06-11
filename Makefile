GUIEditor:
	mkdir -p build
	cmake -S . -B build
	cmake --build build

.PHONY: rebuild
rebuild: clean GUIEditor

.PHONY: clean
clean:
	rm -rf build/*
