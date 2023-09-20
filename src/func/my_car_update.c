#include "../../includes/my.h"

uint32_t my_car_update(void *car, void *pop, uint32_t pop_size, void *map)
{
    if (sfKeyboard_isKeyPressed(sfKeyA) && car->angle_velocity > - car->max_rota_speed)
        car->angle_acceleration = -1;
    if (sfKeyboard_isKeyPressed(sfKeyD) && car->angle_velocity < car->max_rota_speed)
        car->angle_acceleration = 1;
    if (sfKeyboard_isKeyPressed(sfKeyW) && car->velocity < car->max_speed)
        car->acceleration = 1;
    if (sfKeyboard_isKeyPressed(sfKeyS) && car->velocity > - car->max_speed)
        car->acceleration = -1;

    if (car->acceleration < 0)
        car->acceleration = my_min_between(car->acceleration + 0.3, 0);
    else if (car->acceleration > 0)
        car->acceleration = my_max_between(car->acceleration - 0.3, 0);
    car->velocity += car->acceleration;
    if (car->velocity < 0)
        car->velocity = my_min_between(car->velocity + 0.3, 0);
    else if (car->velocity > 0)
        car->velocity = my_max_between(car->velocity - 0.3, 0);
    if (car->angle_acceleration < 0)
        car->angle_acceleration = my_min_between(car->angle_acceleration + 0.4, 0);
    else if (car->angle_acceleration > 0)
        car->angle_acceleration = my_max_between(car->angle_acceleration - 0.4, 0);
    car->angle_velocity += car->angle_acceleration;
    if (car->angle_velocity < 0)
        car->angle_velocity = my_min_between(car->angle_velocity + 0.4, 0);
    else if (car->angle_velocity > 0)
        car->angle_velocity = my_max_between(car->angle_velocity - 0.4, 0);
    sfRectangleShape_rotate(car->rect, car->angle_velocity);
    double angle = sfRectangleShape_getRotation(car->rect) * PI / 180.;
    sfVector2f dir_vec = {
        cos(angle + PI / 2.) * car->velocity,
        sin(angle + PI / 2.) * car->velocity
    };
    sfRectangleShape_move(car->rect, dir_vec);
}
