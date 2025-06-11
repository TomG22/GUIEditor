#include <Window.h>
#include "ListenerExample.h"
#include <cstdio>

int main() {
    printf("Example Listener starting...\n");

    Window window = Window();

    ListenerExample listener = ListenerExample();
    window.RegisterListener(&listener);

    window.startWindowLoop();

    printf("Example Listener terminated\n");
}
