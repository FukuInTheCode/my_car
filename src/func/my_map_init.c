#include "../../includes/my.h"

void my_map_init(my_map_t *map)
{
    map->walls = malloc(sizeof(sfVertexArray));
    map->walls_n = 1;
}
