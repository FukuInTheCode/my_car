#include "../../includes/my.h"

static void find_current_gate(my_car_t *car, my_map_t *map)
{
    sfFloatRect gate_rect = sfVertexArray_getBounds(map->gates[0]);
    double closer_dist = pow(gate_rect.top + gate_rect.height / 2., 2);
    closer_dist += pow(gate_rect.left + gate_rect.width / 2., 2);
    closer_dist = sqrt(closer_dist);
    car->current_gate = 0;
    for (uint32_t i = 1; i < map->gates_n; ++i) {
        sfFloatRect tmp_rect = sfVertexArray_getBounds(map->gates[i]);
        double tmp_dist = pow(tmp_rect.top + tmp_rect.height / 2., 2);
        tmp_dist += pow(tmp_rect.left + tmp_rect.width / 2., 2);
        tmp_dist = sqrt(tmp_dist);
        if (closer_dist > dist) {
            closer_dist = dist;
            car->current_gate = i;
        }
    }
}

void my_car_create(my_car_t *car, my_map_t *map)
{
    car->max_rota_speed = 0;
    car->max_speed = 0;
    car->velocity = 0;
    car->angle_velocity = 0;
    car->acceleration = 0;
    car->angle_acceleration = 0;
    car->reward = 0;
    car->pos.x = 0;
    car->pos.y = 0;
    car->size.y = 0;
    car->size.x = 0;
    find_current_gate(car, map);
}
