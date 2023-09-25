#include "../../includes/my.h"

void my_map_free(my_map_t *map)
{
    for (uint32_t i = 0; i < map->walls_n; i++)
        sfVertexArray_destroy(map->walls[i]);

    free(map->walls);
    map->walls = NULL;
}
