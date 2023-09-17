#include "../../includes/my.h"

bool my_map_is_intersecting_wall(my_map_t *map, sfVertex *line, sfVector2f *res)
{
    bool is_intersect = false;
    for (uint32_t i = 0; i < map->walls_n && !is_intersect; ++i) {
        size_t count = sfVertexArray_getVertexCount(map->walls[i]);
        for (uint32_t j = 0; j < count && !is_intersect; j += 2){
            sfVertex wall[] = {
                *sfVertexArray_getVertex(map->walls[i], j),
                *sfVertexArray_getVertex(map->walls[i], j + 1)
            };
            is_intersect = is_intersecting(line, wall, res);
        }
    }
    return is_intersect;
}
