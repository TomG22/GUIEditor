#include "Window.h"
#include "ListenerExample.h"
#include <cstdio>

int main() {
    printf("Listener starting...\n");

    Window window = Window();

    ListenerExample listener = ListenerExample();
    window.RegisterListener(&listener);


    window.startWindowLoop();

    printf("Listener terminated\n");
}
