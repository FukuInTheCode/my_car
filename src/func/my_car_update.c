#include "../../includes/my.h"

uint32_t my_car_update(my_car_t *car, void *pop, uint32_t pop_size, my_map_t *map)
{
    if (car_acceleration < 0 && draw_car)
        car_acceleration = my_min_between(car_acceleration + 0.3, 0);
    else if (car_acceleration > 0 && draw_car)
        car_acceleration = my_max_between(car_acceleration - 0.3, 0);
    car_velocity += car_acceleration;
    if (car_velocity < 0 && draw_car)
        car_velocity = my_min_between(car_velocity + 0.3, 0);
    else if (car_velocity > 0 && draw_car)
        car_velocity = my_max_between(car_velocity - 0.3, 0);
    if (car_angular_acceleration < 0 && draw_car)
        car_angular_acceleration = my_min_between(car_angular_acceleration + 0.4, 0);
    else if (car_angular_acceleration > 0 && draw_car)
        car_angular_acceleration = my_max_between(car_angular_acceleration - 0.4, 0);
    car_angular_velocity += car_angular_acceleration;
    if (car_angular_velocity < 0 && draw_car)
        car_angular_velocity = my_min_between(car_angular_velocity + 0.4, 0);
    else if (car_angular_velocity > 0 && draw_car)
        car_angular_velocity = my_max_between(car_angular_velocity - 0.4, 0);
    sfRectangleShape_rotate(car->rect, car->angle_velocity);
    double angle = sfRectangleShape_getRotation(car->rect) * PI / 180.;
    sfVector2f dir_vec = {
        cos(angle + PI / 2.) * car->velocity,
        sin(angle + PI / 2.) * car->velocity
    };
    sfRectangleShape_move(car->rect, dir_vec);
}
