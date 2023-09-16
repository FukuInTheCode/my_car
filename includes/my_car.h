#ifndef MY_CAR_H
#define MY_CAR_H

#include "my_neuralnetwork.h"
#include "my_matrix.h"
#include "SFML/Graphics.h"

typedef enum {
    no_mode,
    wall_mode,
    gate_mode,
    start_mode,
    race_mode
} m_status_t;

typedef struct {
    sfVector2f start;
    sfVertexArray **walls;
    sfVertexArray **gates;
    uint32_t walls_n;
    uint32_t gates_n;
    m_status_t status;
} my_map_t;

void my_map_init(my_map_t *map);
void my_map_alloc_wall(my_map_t *map);
void my_map_add_wall(my_map_t *map, sfRenderWindow *window);
void my_map_create(my_map_t *map, sfVideoMode mode);
void my_map_alloc_gate(my_map_t *map);
void my_map_add_gate(my_map_t *map, sfRenderWindow *window);
void my_map_place_start(my_map_t *map, sfRenderWindow *window);

#endif
