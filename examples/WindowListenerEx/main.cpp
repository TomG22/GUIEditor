#include <string>

#include <WindowManager.h>
#include "WindowListenerEx.h"

int main(int argc, char* argv[]) {
    WindowManager winManager = WindowManager();

    int winCount = 0;
    if (argc > 1) {
        winCount = std::stoi(argv[1]);
    }

    for (int i = 0; i < winCount; i++) {
        Window* window = winManager.createWindow();
        WindowListenerEx* listener = new WindowListenerEx();
        window->RegisterListener(listener);
    }

    winManager.startEventLoop();
}
