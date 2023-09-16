#ifndef MY_CAR_H
#define MY_CAR_H

#include "my_neuralnetwork.h"
#include "my_matrix.h"

typedef enum {
    no_mode,
    wall_mode,
    gate_mode,
    start_mode,
    race_mode
} m_status_t;

typedef struct {
    sfVertexArray *walls;
    sfVector2f start;
    sfVertex *gates;
    uint32_t walls_n;
    uint32_t gates_n;
    m_status_t status;
} my_map_t;

void my_map_init(my_map_t *map);
void my_map_add_wall(my_map_t *map);
void my_map_draw_wall(my_map_t *map, sfRenderWindow *window);

#endif
