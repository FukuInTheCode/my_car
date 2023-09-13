#include "../includes/my.h"


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
            sfRenderWindow_drawRectangleShape(window, car_rect, NULL);
            // sfVector2f tmp = {-1 * car_origine.x, -1 * car_origine.y};
            // sfRectangleShape_setOrigin(car_rect, tmp);
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
            sides[3].position = z4;
            sides[4].position = z4;
            sides[5].position = z3;
            sides[6].position = z3;
            sides[7].position = z1;

            for (int i = 0; i < 8; i++)
                sides[i].color = sfWhite;
            for (uint32_t i = 0; i < 8; i += 2) {
                sfVertex side[] = {sides[i], sides[i + 1]};
                sfRenderWindow_drawPrimitives(window, side, 2, sfLines, NULL);
            }
            // sfRectangleShape_setOrigin(car_rect, car_origine);
        }
        sfRenderWindow_display(window);
    }
    sfRenderWindow_destroy(window);
    return 0;
}