#include "../../includes/my.h"

static void handle_event(sfRenderWindow *window)
{
    sfEvent event;
    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
    }
}

void my_map_create(my_map_t *map, sfVideoMode mode)
{
    sfRenderWindow *window = sfRenderWindow_create(mode, "create race", sfDefaultStyle, NULL);
    bool wall_mode = false;
    bool gate_mode = false;
    bool start_mode = false;
    while (sfRenderWindow_isOpen(window)) {
        handle_event(window);
    }
    sfRenderWindow_destroy(window);
}
