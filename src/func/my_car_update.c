#include "../../includes/my.h"

uint32_t my_car_update(void *car_ptr, void *pop, uint32_t pop_size, void *map_ptr)
{
    my_car_t *car = (my_car_t *)car_ptr;
    if (car->is_dead)
        return pop_size;
    my_map_t *map = (my_map_t *)map_ptr;
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
    sfVector2f car_origin = sfRectangleShape_getOrigin(car->rect);
    sfVertex sides[8];

    sfVector2f center = sfRectangleShape_getPosition(car->rect);
    sfVector2f z1 = {
        center.x - car_origin.x * cos(angle) - car_origin.y * sin(angle),
        center.y - car_origin.x * sin(angle) + car_origin.y * cos(angle)
    };
    sfVector2f z2 = {
        center.x + car_origin.x * cos(angle) - car_origin.y * sin(angle),
        center.y + car_origin.x * sin(angle) + car_origin.y * cos(angle)
    };
    sfVector2f z3 = {
        center.x + car_origin.x * cos(angle) + car_origin.y * sin(angle),
        center.y + car_origin.x * sin(angle) - car_origin.y * cos(angle)
    };
    sfVector2f z4 = {
        center.x - car_origin.x * cos(angle) + car_origin.y * sin(angle),
        center.y - car_origin.x * sin(angle) - car_origin.y * cos(angle)
    };
    sides[0].position = z1;
    sides[1].position = z2;
    sides[2].position = z2;
    sides[3].position = z3;
    sides[4].position = z3;
    sides[5].position = z4;
    sides[6].position = z4;
    sides[7].position = z1;
    for (uint32_t i = 0; i < 8; i += 2) {
        sfVertex line[] = {sides[i], sides[i + 1]};
        sfVector2f inter_pt;
        if (!my_map_is_intersecting_wall(map, line, &inter_pt))
            continue;
        car->is_dead = true;
        break;
    }

    for (uint32_t i = 0; i < car->sight_l_n; ++i) {
        sfVector2f inter_vec;
        sfVertex line[] = {
            {center, sfWhite, {0, 0}},
            {{center.x + car->sight_dist * cos(angle + car->sight_angles[i] + PI / 2), center.y + car->sight_dist * sin(angle + car->sight_angles[i]  + PI / 2)}, sfWhite, {0, 0}},
        };
        if (!my_map_is_intersecting_wall(map, line, &inter_vec))
            continue;
        printf("%lf, %lf\n", inter_vec.x, inter_vec.y);
    }
    return pop_size;
}
