#include "../includes/my.h"


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

int main(int argc, char* argv[])
{
    my_map_t map;
    my_map_init(&map);
    sfVideoMode mode = {2500, 1500, 32};
    my_map_create(&map, mode);
#if 0
    // env var
    // car var
    double max_angular_speed = 6;
    double max_speed = 15;
    double car_acceleration = 0;
    double car_angular_acceleration = 0;
    double car_velocity = 0;
    double car_angular_velocity = 0;
    sfVector2f car_pos;
    sfVector2f car_size = {10, 30};
    sfVector2f car_origine = {car_size.x / 2., car_size.y / 2.};
    sfRectangleShape *car_rect = sfRectangleShape_create();
    sfRectangleShape_setSize(car_rect, car_size);
    sfRectangleShape_setFillColor(car_rect, sfRed);
    sfRectangleShape_setOrigin(car_rect, car_origine);
    sfVertex sides[8];
    double sight_angles[] = {0, PI / 8, - PI / 8, PI / 8 * 2, - PI / 8 * 2,\
            PI / 8 * 3, - PI / 8 * 3, PI / 8 * 4, - PI / 8 * 4, PI / 8 * 5,\
            - PI / 8 * 5, PI / 8 * 6, - PI / 8 * 6, PI / 8 * 7, - PI / 8 * 7};
    uint32_t sight_l_n = sizeof(sight_angles) / sizeof(double);
    double sight_powah = 100.;
    NN_DECLA(car_brain);
    car_brain.acti_type = base_type;
    car_brain.funcs.af = my_nn_sin;
    car_brain.funcs.grad_af = my_nn_sin_grad;
    uint32_t dims[] = {sight_l_n + 2, 16, 8, 4};
    car_brain.dims = dims;
    car_brain.size = sizeof(dims) / sizeof(dims[0]);
    my_nn_create(&car_brain);
    // main
    sfVideoMode mode = {3000, 2000, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode, "my_car", sfDefaultStyle, NULL);
    sfEvent event;
    sfRenderWindow_setFramerateLimit(window, 60);
    // road var
    sfVertexArray *road_r = sfVertexArray_create();
    sfVertexArray *road_l = sfVertexArray_create();
    sfVertexArray *current_border = road_r;
    sfVertexArray_setPrimitiveType(road_l, sfLines);
    sfVertexArray_setPrimitiveType(road_r, sfLines);
    sfVector2i window_pos = sfRenderWindow_getPosition(window);
    // bool & loop
    bool ended = false;
    bool ended2 = false;
    bool clicked = false;
    bool draw_car = false;
    bool is_crash = false;
    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }
        // road drawing
        if (sfKeyboard_isKeyPressed(sfKeySpace) && !clicked && !ended) {
            clicked = true;
            sfVector2i mouse_vec = sfMouse_getPosition(NULL);
            sfVertex tmp = {
                {mouse_vec.x - window_pos.x, mouse_vec.y - window_pos.y},
                sfWhite,
                {0, 0}
            };
            sfVertexArray_append(current_border, tmp);
            if (sfVertexArray_getVertexCount(current_border) > 1)
                sfVertexArray_append(current_border, tmp);
        } else if (clicked && !sfKeyboard_isKeyPressed(sfKeySpace))
            clicked = false;
        if (sfKeyboard_isKeyPressed(sfKeyZ) && !ended) {
            if (sfVertexArray_getVertexCount(current_border) > 1) {
                sfVertexArray_append(current_border, *sfVertexArray_getVertex(current_border, 0));
                clicked = false;
                if (current_border == road_l)
                    ended = true;
                else
                    current_border = road_l;
            }
        }

        if (ended2 && sfKeyboard_isKeyPressed(sfKeySpace) && !draw_car) {
            sfVector2i mouse_vec = sfMouse_getPosition(NULL);
            car_pos.x = mouse_vec.x - window_pos.x;
            car_pos.y = mouse_vec.y - window_pos.y;
            draw_car = true;
            sfRectangleShape_setPosition(car_rect, car_pos);
        }
        if (sfKeyboard_isKeyPressed(sfKeyR))
            is_crash = false;

        if (draw_car && sfKeyboard_isKeyPressed(sfKeyA) && car_angular_velocity > - max_angular_speed)
            car_angular_acceleration = -1;
        if (draw_car && sfKeyboard_isKeyPressed(sfKeyD) && car_angular_velocity < max_angular_speed)
            car_angular_acceleration = 1;
        if (draw_car && sfKeyboard_isKeyPressed(sfKeyW) && car_velocity < max_speed)
            car_acceleration = 1;
        if (draw_car && sfKeyboard_isKeyPressed(sfKeyS) && car_velocity > - max_speed)
            car_acceleration = -1;

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
        // draw
        sfRenderWindow_clear(window, sfColor_fromRGBA(44, 44, 44, 128));
        sfRenderWindow_drawVertexArray(window, road_r, NULL);
        sfRenderWindow_drawVertexArray(window, road_l, NULL);
        if (draw_car) {
            sfRectangleShape_rotate(car_rect, car_angular_velocity);
            float angle = sfRectangleShape_getRotation(car_rect) * 3.14159265359 / 180.0;
            sfVector2f dir_vec = {
                cos(angle + PI / 2.) * car_velocity,
                sin(angle + PI / 2.) * car_velocity
            };
            sfRectangleShape_move(car_rect, dir_vec);
            sfVector2f center = sfRectangleShape_getPosition(car_rect);
            sfVector2f z1 = {
                center.x - car_origine.x * cos(angle) - car_origine.y * sin(angle),
                center.y - car_origine.x * sin(angle) + car_origine.y * cos(angle)
            };
            sfVector2f z2 = {
                center.x + car_origine.x * cos(angle) - car_origine.y * sin(angle),
                center.y + car_origine.x * sin(angle) + car_origine.y * cos(angle)
            };
            sfVector2f z3 = {
                center.x + car_origine.x * cos(angle) + car_origine.y * sin(angle),
                center.y + car_origine.x * sin(angle) - car_origine.y * cos(angle)
            };
            sfVector2f z4 = {
                center.x - car_origine.x * cos(angle) + car_origine.y * sin(angle),
                center.y - car_origine.x * sin(angle) - car_origine.y * cos(angle)
            };

            sides[0].position = z1;
            sides[1].position = z2;
            sides[2].position = z2;
            sides[3].position = z3;
            sides[4].position = z3;
            sides[5].position = z4;
            sides[6].position = z4;
            sides[7].position = z1;

            bool is_intersec = false;
            for (uint32_t i = 0; i < 8; i += 2) {
                sfVertex side[] = {sides[i], sides[i + 1]};
                sfVector2f intersection_pt;
                for (uint32_t j = 0; j < sfVertexArray_getVertexCount(road_l); j += 2) {
                    sfVertex line[] = {
                        *sfVertexArray_getVertex(road_l, j),
                        *sfVertexArray_getVertex(road_l, j + 1)
                    };
                    if (!is_intersecting(side, line, &intersection_pt))
                        continue;
                    is_intersec = true;
                    break;
                }
                for (uint32_t j = 0; j < sfVertexArray_getVertexCount(road_r) && !is_intersec; j += 2) {
                    sfVertex line[] = {
                        *sfVertexArray_getVertex(road_r, j),
                        *sfVertexArray_getVertex(road_r, j + 1)
                    };
                    if (!is_intersecting(side, line, &intersection_pt))
                        continue;
                    is_intersec = true;
                }
            }
            if (is_intersec) {
                sfRectangleShape_setFillColor(car_rect, sfGreen);
                is_crash = true;
            } else
                sfRectangleShape_setFillColor(car_rect, sfRed);

            MAT_DECLA(inputs);
            my_matrix_create(sight_l_n + 2, 1, 1, &inputs);
            my_matrix_set(&inputs, 0, 0, car_velocity);
            my_matrix_set(&inputs, 1, 0, car_angular_velocity);
            for (uint32_t i = 0; i < sight_l_n; ++i) {
                sfVector2f inter_vec;
                bool see_road = false;
                sfVertex tmp_sl[] = {
                    {center, sfWhite, {0, 0}},
                    {{center.x + sight_powah * cos(angle + sight_angles[i] + PI / 2), center.y + sight_powah * sin(angle + sight_angles[i]  + PI / 2)}, sfWhite, {0, 0}},
                };
                for (uint32_t j = 0; j < sfVertexArray_getVertexCount(road_l); j += 2) {
                    sfVertex line[] = {
                        *sfVertexArray_getVertex(road_l, j),
                        *sfVertexArray_getVertex(road_l, j + 1)
                    };
                    if (!is_intersecting(tmp_sl, line, &inter_vec))
                        continue;
                    see_road = true;
                    tmp_sl[0].color = sfGreen;
                    tmp_sl[1].color = sfGreen;
                    break;
                }
                for (uint32_t j = 0; j < sfVertexArray_getVertexCount(road_r) && !see_road; j += 2) {
                    sfVertex line[] = {
                        *sfVertexArray_getVertex(road_r, j),
                        *sfVertexArray_getVertex(road_r, j + 1)
                    };
                    if (!is_intersecting(tmp_sl, line, &inter_vec))
                        continue;
                    see_road = true;
                    tmp_sl[0].color = sfGreen;
                    tmp_sl[1].color = sfGreen;
                    break;
                }
                sfRenderWindow_drawPrimitives(window, tmp_sl, 2, sfLines, NULL);
                if (see_road) {
                    inter_vec.x -= 10;
                    inter_vec.y -= 10;
                    sfCircleShape *pt = sfCircleShape_create();
                    sfCircleShape_setFillColor(pt, sfRed);
                    sfCircleShape_setPosition(pt, inter_vec);
                    sfCircleShape_setRadius(pt, 10);
                    sfRenderWindow_drawCircleShape(window, pt, NULL);
                    sfCircleShape_destroy(pt);
                    double dist = sqrt(pow(inter_vec.x - center.x, 2) + pow(inter_vec.y - center.y, 2));
                    my_matrix_set(&inputs, i + 2, 0, dist);
                }
            }
            MAT_DECLA(pred);
            my_nn_predict(&car_brain, &inputs, &pred);
            uint32_t id = my_matrix_find_row_index(&pred, 0, my_matrix_max(&pred));
            if (is_crash) {
                car_velocity = 0;
                car_angular_velocity = 0;
            }
            if (id == 0 && car_angular_velocity > - max_angular_speed && !is_crash)
                car_angular_acceleration = -1;
            if (id == 1 && car_angular_velocity < max_angular_speed && !is_crash)
                car_angular_acceleration = 1;
            if (id == 2 && car_velocity < max_speed && !is_crash)
                car_acceleration = 1;
            if (id == 3 && car_velocity > - max_speed && !is_crash)
                car_acceleration = -1;
            sfRenderWindow_drawRectangleShape(window, car_rect, NULL);
        }
        sfRenderWindow_display(window);
    }
    sfRenderWindow_destroy(window);
#endif
    return 0;
}