#include "../../includes/my.h"

void my_car_create(my_car_t *car, my_map_t *map)
{
    max_rota_speed = 0;
    max_speed = 0;
    velocity = 0;
    angle_velocity = 0;
    acceleration = 0;
    angle_acceleration = 0;
    find_current_gate(car, map);
    reward = 0;
}
