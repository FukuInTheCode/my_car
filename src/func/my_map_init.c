#include "../../includes/my.h"

void my_map_init(my_map_t *map)
{
    map->status = no_mode;
    map->walls_n = 0;
    my_map_alloc_wall(map);
    map->gates_n = 0;
    my_map_alloc_gate(map);
}
