#include "../../includes/my.h"

void my_map_alloc_gate(my_map_t *map)
{
    sfVertexArray **tmp_walls = map->walls;
    map->walls = calloc(map->walls_n + 1, sizeof(sfVertexArray *));
    check_alloc(map->walls);
    for (uint32_t i = 0; i < map->walls_n; ++i)
        map->walls[i] = tmp_walls[i];
    map->walls_n += 1;
    map->walls[map->walls_n - 1] = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(map->walls[map->walls_n - 1], sfLines);
}
