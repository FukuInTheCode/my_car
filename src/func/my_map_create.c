#define MATRIX_CHECK_ALLOC
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
    if (sfKeyboard_isKeyPressed(sfKeyW) && !sfKeyboard_isKeyPressed(sfKeyLControl))
        map->status = wall_mode;
    if (sfKeyboard_isKeyPressed(sfKeyG) && !sfKeyboard_isKeyPressed(sfKeyLControl))
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
        if (map->status == wall_mode)
            my_map_add_wall(map, window);
        if (map->status == gate_mode)
            my_map_add_gate(map, window);
        if (map->status == start_mode)
            my_map_place_start(map, window);
        if (map->status == no_mode && sfKeyboard_isKeyPressed(sfKeyW)\
                                && sfKeyboard_isKeyPressed(sfKeyLControl))
            my_map_del_wall(map);
        if (map->status == no_mode && sfKeyboard_isKeyPressed(sfKeyG)\
                                && sfKeyboard_isKeyPressed(sfKeyLControl))
            my_map_del_gate(map);
        if (map->status == race_mode)
            sfRenderWindow_close(window);
        my_map_draw(window, map);
        handle_keyboard(map, window);
        sfRenderWindow_display(window);

    }
    sfRenderWindow_destroy(window);
}
