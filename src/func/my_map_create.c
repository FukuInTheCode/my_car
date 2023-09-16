#include "../../includes/my.h"

static void handle_event(sfRenderWindow *window)
{
    sfEvent event;
    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
    }
}

static void handle

void my_map_create(my_map_t *map, sfVideoMode mode)
{
    sfRenderWindow *window = sfRenderWindow_create(mode, "create race", sfDefaultStyle, NULL);
    while (sfRenderWindow_isOpen(window)) {
        handle_event(window);
        handle_keyboard(map, window);
        if (wall_mode)
            my_map_draw_wall(map, window);
    }
    sfRenderWindow_destroy(window);
}
