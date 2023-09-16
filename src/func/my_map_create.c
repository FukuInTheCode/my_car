#include "../../includes/my.h"

static void handle_event(sfRenderWindow *window)
{
    sfEvent event;
    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
    }
}

static void handle_keyboard(my_map_t *map, sfRenderWindow *window)
{
    if (sfKeyboard_isKeyPressed(sfKeyW))
        map->status = wall_mode;
    if (sfKeyboard_isKeyPressed(sfKeyG))
        map->status = gate_mode;
    if (sfKeyboard_isKeyPressed(sfKeyS))
        map->status = start_mode;
    if (sfKeyboard_isKeyPressed(sfKeyR))
        map->status = race_mode;
    if (sfKeyboard_isKeyPressed(sfKeyN))
        map->status = no_mode;
}

void my_map_create(my_map_t *map, sfVideoMode mode)
{
    sfRenderWindow *window = sfRenderWindow_create(mode, "create race", sfDefaultStyle, NULL);
    while (sfRenderWindow_isOpen(window)) {
        handle_event(window);
        handle_keyboard(map, window);
        if (map->status == wall_mode)
            my_map_draw_wall(map, window);
    }
    sfRenderWindow_destroy(window);
}
