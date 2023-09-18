#include "../../includes/my.h"

void my_map_draw(my_map_t *map, sfRenderWindow *window)
{
    sfRenderWindow_clear(window, sfBlack);
    for (uint32_t i = 0; i < map->walls_n; ++i)
        sfRenderWindow_drawVertexArray(window, map->walls[i], NULL);
    for (uint32_t i = 0; i < map->gates_n; ++i)
        sfRenderWindow_drawVertexArray(window, map->gates[i], NULL);
}
