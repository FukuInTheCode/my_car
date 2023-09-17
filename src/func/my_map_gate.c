#define MATRIX_CHECK_ALLOC
#include "../../includes/my.h"

void my_map_alloc_gate(my_map_t *map)
{
    sfVertexArray **tmp_gates = map->gates;
    map->gates = calloc(map->gates_n + 1, sizeof(sfVertexArray *));
    check_alloc(map->gates);
    for (uint32_t i = 0; i < map->gates_n; ++i)
        map->gates[i] = tmp_gates[i];
    map->gates_n += 1;
    map->gates[map->gates_n - 1] = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(map->gates[map->gates_n - 1], sfLines);
}

void my_map_add_gate(my_map_t *map, sfRenderWindow *window)
{
    if (sfKeyboard_isKeyPressed(sfKeyE)) {
        map->status = no_mode;
        my_map_alloc_gate(map);
        map->last_action = gate_mode;
    } else if (sfKeyboard_isKeyPressed(sfKeySpace)) {
        sfVector2i window_pos = sfRenderWindow_getPosition(window);
        sfVector2i pos = sfMouse_getPosition(NULL);
        pos.x -= window_pos.x;
        pos.y -= window_pos.y;
        sfVertex pt = {{pos.x, pos.y}, sfGreen, {0, 0}};
        sfVertexArray_append(map->gates[map->gates_n - 1], pt);
        if (sfVertexArray_getVertexCount(map->gates[map->gates_n - 1]) > 1)
            sfVertexArray_append(map->gates[map->gates_n - 1], pt);
    }
}
