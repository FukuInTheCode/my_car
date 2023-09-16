#include "../../includes/my.h"

void my_map_alloc_gate(my_map_t *map)
{
    sfVertexArray **tmp_gates = map->gates;
    map->walls = calloc(map->gates_n + 1, sizeof(sfVertexArray *));
    check_alloc(map->gates);
    for (uint32_t i = 0; i < map->gates_n; ++i)
        map->gates[i] = tmp_gates[i];
    map->gates_n += 1;
    map->gates[map->gates_n - 1] = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(map->gates[map->gates_n - 1], sfLines);
}
