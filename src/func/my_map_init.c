#define MATRIX_CHECK_ALLOC
#include "../../includes/my.h"

void my_map_init(my_map_t *map)
{
    map->walls = calloc(1, sizeof(sfVertexArray));
    check_alloc(map->walls);
    map->walls_n = 1;
}
