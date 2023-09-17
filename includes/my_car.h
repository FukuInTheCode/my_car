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
} my_status_t;

typedef struct {
    sfVector2f start;
    sfVertexArray **walls;
    sfVertexArray **gates;
    uint32_t walls_n;
    uint32_t gates_n;
    my_status_t status;
} my_map_t;

void my_map_init(my_map_t *map);
void my_map_alloc_wall(my_map_t *map);
void my_map_add_wall(my_map_t *map, sfRenderWindow *window);
void my_map_create(my_map_t *map, sfVideoMode mode);
void my_map_alloc_gate(my_map_t *map);
void my_map_add_gate(my_map_t *map, sfRenderWindow *window);
void my_map_place_start(my_map_t *map, sfRenderWindow *window);
void my_map_del_wall(my_map_t *map);
void my_map_del_gate(my_map_t *map);
bool my_map_is_intersecting_wall(my_map_t *map, sfVertex *line,\
                                                    sfVector2f *res);

#ifdef MAP_INTERSECT
static bool is_intersecting(sfVertex *line1, sfVertex *line2, sfVector2f *res)
{
    sfVector2f s1 = {line1[1].position.x - line1[0].position.x, line1[1].position.y - line1[0].position.y};
    sfVector2f s2 = {line2[1].position.x - line2[0].position.x, line2[1].position.y - line2[0].position.y};
    double s = (s1.y * (line2[0].position.x - line1[0].position.x) - s1.x * (line2[0].position.y - line1[0].position.y)) / (s1.x * s2.y - s2.x * s1.y);
    double t = (s2.x * (line1[0].position.y - line2[0].position.y) - s2.y * (line1[0].position.x - line2[0].position.x)) / (s1.x * s2.y - s2.x * s1.y);
    if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
        (*res).x = line1[0].position.x + (t * s1.x);
        (*res).y = line1[0].position.y + (t * s1.y);
        return true;
    }
    return false;
}
#endif

#endif
