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
        printf("true\n");
        return true;
    }
    return false;
}

int main(int argc, char* argv[])
{
    // car var
    sfVector2f car_pos;
    sfVector2f car_size = {10, 30};
    sfVector2f car_origine = {car_size.x / 2., car_size.y / 2.};
    sfRectangleShape *car_rect = sfRectangleShape_create();
    sfRectangleShape_setSize(car_rect, car_size);
    sfRectangleShape_setFillColor(car_rect, sfRed);
    sfRectangleShape_setOrigin(car_rect, car_origine);
    sfVertex sides[8];
    // main
    sfVideoMode mode = {3000, 2000, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode, "my_car", sfDefaultStyle, NULL);
    sfEvent event;
    // road var
    sfVertexArray *road_r = sfVertexArray_create();
    sfVertexArray *road_l = sfVertexArray_create();
    sfVertexArray *current_border = road_r;
    sfVertexArray_setPrimitiveType(road_l, sfLines);
    sfVertexArray_setPrimitiveType(road_r, sfLines);
    sfVector2i window_pos = sfRenderWindow_getPosition(window);
    // bool & loop
    bool ended = false;
    bool clicked = false;
    bool draw_car = false;
    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }
        // road drawing
        if (sfKeyboard_isKeyPressed(sfKeyA) && !clicked && !ended) {
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
        } else if (clicked && !sfKeyboard_isKeyPressed(sfKeyA))
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
        if (ended && sfKeyboard_isKeyPressed(sfKeyA) && !draw_car) {
            sfVector2i mouse_vec = sfMouse_getPosition(NULL);
            car_pos.x = mouse_vec.x - window_pos.x;
            car_pos.y = mouse_vec.y - window_pos.y;
            draw_car = true;
            sfRectangleShape_setPosition(car_rect, car_pos);
        }
        if (draw_car && sfKeyboard_isKeyPressed(sfKeyLeft))
            sfRectangleShape_rotate(car_rect, -1);
        if (draw_car && sfKeyboard_isKeyPressed(sfKeyRight))
            sfRectangleShape_rotate(car_rect, 1);
        if (draw_car && sfKeyboard_isKeyPressed(sfKeyW)) {
            double theta = sfRectangleShape_getRotation(car_rect) * PI / 180.;
            sfVector2f dir_vec = {
                cos(theta + PI / 2.),
                sin(theta + PI / 2.)
            };
            sfRectangleShape_move(car_rect, dir_vec);

        }
        // draw
        sfRenderWindow_clear(window, sfColor_fromRGBA(44, 44, 44, 128));
        sfRenderWindow_drawVertexArray(window, road_r, NULL);
        sfRenderWindow_drawVertexArray(window, road_l, NULL);
        if (draw_car) {
            sfVector2f center = sfRectangleShape_getPosition(car_rect);
            float angle = sfRectangleShape_getRotation(car_rect) * 3.14159265359 / 180.0;
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
                        *sfVertexArray_getVertex(road_l, i),
                        *sfVertexArray_getVertex(road_l, i + 1)
                    };
                    if (!is_intersecting(side, line, &intersection_pt))
                        continue;
                    is_intersec = true;
                    break;
                }
                for (uint32_t j = 0; j < sfVertexArray_getVertexCount(road_r) && !is_intersec; j += 2) {
                    sfVertex line[] = {
                        *sfVertexArray_getVertex(road_r, i),
                        *sfVertexArray_getVertex(road_r, i + 1)
                    };
                    if (!is_intersecting(side, line, &intersection_pt))
                        continue;
                    is_intersec = true;
                }
            }
            if (is_intersec)
                sfRectangleShape_setFillColor(car_rect, sfGreen);
            else
                sfRectangleShape_setFillColor(car_rect, sfRed);
            sfRenderWindow_drawRectangleShape(window, car_rect, NULL);
        }
        sfRenderWindow_display(window);
    }
    sfRenderWindow_destroy(window);
    return 0;
}