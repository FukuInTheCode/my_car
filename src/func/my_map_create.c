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

static void handle_show(my_map_t *map, sfRenderWindow *window)
{
    sfRenderWindow_clear(window, sfBlack);
    for (uint32_t i = 0; i < map->walls_n; ++i)
        sfRenderWindow_drawVertexArray(window, map->walls[i], NULL);
    for (uint32_t i = 0; i < map->gates_n; ++i)
        sfRenderWindow_drawVertexArray(window, map->gates[i], NULL);
    sfRenderWindow_display(window);
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
        handle_show(map, window);
        handle_keyboard(map, window);
    }
    sfRenderWindow_destroy(window);
}
