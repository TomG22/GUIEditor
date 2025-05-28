GUIEditor:
	cmake -S . -B build
	cmake --build build

GUIEditorClean: clean
	cmake -S . -B build
	cmake --build build

.PHONY: clean
clean:
	rm -rf build/*
