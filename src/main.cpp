#include "Gui.h"

#include <thread>

int main() {
    Gui gui = Gui();

    std::thread guiThread = std::thread(&Gui::startGuiLoop, &gui);
    guiThread.detach();

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return 0;
}
