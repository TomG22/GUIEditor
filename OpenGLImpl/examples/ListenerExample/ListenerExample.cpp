#include "ListenerExample.h"
#include <iostream>

ListenerExample::ListenerExample() {}

void ListenerExample::OnKey(int key, int scancode, int action, int mods) {
    std::cout << "Key: " << key << ", action: " << action << "\n";
}
