#include "../../includes/my.h"

void my_map_draw(sfRenderWindow *window, void *map_ptr)
{
    sfRenderWindow_clear(window, sfBlack);
    for (uint32_t i = 0; i < map->walls_n; ++i)
        sfRenderWindow_drawVertexArray(window, map->walls[i], NULL);
    for (uint32_t i = 0; i < map->gates_n; ++i)
        sfRenderWindow_drawVertexArray(window, map->gates[i], NULL);
    sfRectangleShape *start_rect = sfRectangleShape_create();
    sfVector2f rect_size = {30, 5};
    sfRectangleShape_setSize(start_rect, rect_size);
    sfRectangleShape_setPosition(start_rect, map->start);
    sfRenderWindow_drawRectangleShape(window, start_rect, NULL);
    sfRectangleShape_destroy(start_rect);
}
