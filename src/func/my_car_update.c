#include "../../includes/my.h"

uint32_t my_car_update(my_car_t *car, void *pop, uint32_t pop_size, my_map_t *map)
{
    sfRectangleShape_rotate(car->rect, car->angle_velocity);
    double angle = sfRectangleShape_getRotation(car->rect) * PI / 180.;
    sfVector2f dir_vec = {
        cos(angle + PI / 2.) * car->velocity,
        sin(angle + PI / 2.) * car->velocity
    };
    sfRectangleShape_move(car->rect, dir_vec);
}
