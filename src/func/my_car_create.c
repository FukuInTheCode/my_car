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

void my_car_create(void *car_ptr, void *map)
{
    my_car_t *car = (my_car_t *)car_ptr;
    car->max_rota_speed = 6;
    car->max_speed = 15;
    car->velocity = 0;
    car->angle_velocity = 0;
    car->acceleration = 0;
    car->angle_acceleration = 0;
    car->reward = 0;
    car->pos.x = 0;
    car->pos.y = 0;
    car->size.y = 30;
    car->size.x = 10;
    double sight_angles[] = {0, PI / 8, - PI / 8, PI / 8 * 2, - PI / 8 * 2,\
            PI / 8 * 3, - PI / 8 * 3, PI / 8 * 4, - PI / 8 * 4, PI / 8 * 5,\
            - PI / 8 * 5, PI / 8 * 6, - PI / 8 * 6, PI / 8 * 7, - PI / 8 * 7};
    car->sight_angles = sight_angles;
    car->sight_l_n = sizeof(sight_angles) / sizeof(double);;
    car->sight_dist = 100.;
    car->brain.name = "brain";
    uint32_t dims[] = {car->sight_l_n + 2, 16, 8, 4};
    car->brain.dims = dims;
    car->brain.size = sizeof(dims) / sizeof(dims[0]);
    my_nn_create(&(car->brain));
    find_current_gate(car, (my_map_t *)map);
}
