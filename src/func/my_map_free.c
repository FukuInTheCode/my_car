#include "../../includes/my.h"

void my_map_free(my_map_t *map)
{
    for (uint32_t i = 0; i < map->walls_n; i++)
        sfVertexArray_destroy(map->walls[i]);

    free(map->walls);
    map->walls = NULL;
    map->walls_n = 0;
    for (uint32_t i = 0; i < map->gates_n; i++)
        sfVertexArray_destroy(map->gates_n[i]);
    free(map->gates_n);
    map->gates = NULL;

    map->gates_n = 0;
}
