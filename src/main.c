#include "../includes/my.h"


int main(int argc, char* argv[])
{
    sfVideoMode mode = {2000, 1500, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode, "my_car", sfDefaultStyle, NULL);
    sfEvent event;
    // sfVertex road_right[] = {
    //     {{1282, 742}, sfColor_fromRGB(255, 255, 255)},
    //     {{1293, 1206}, sfColor_fromRGB(255, 255, 255)},
    //     {{1580, 1436}, sfColor_fromRGB(255, 255, 255)},
    //     {{2133, 1460}, sfColor_fromRGB(255, 255, 255)},
    //     {{2424, 1168}, sfColor_fromRGB(255, 255, 255)},
    //     {{2430, 766}, sfColor_fromRGB(255, 255, 255)},
    //     {{2136, 497}, sfColor_fromRGB(255, 255, 255)},
    //     {{1582, 493}, sfColor_fromRGB(255, 255, 255)}
    // };
    sfVertexArray *road_r = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(road_r, sfLines);
    sfVector2i window_pos = sfRenderWindow_getPosition(window);
    bool ended = false;
    bool clicked = false;
    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }
        if (sfKeyboard_isKeyPressed(sfKeyA) && !clicked && !ended) {
            clicked = true;
            sfVector2i mouse_vec = sfMouse_getPosition(NULL);
            sfVertex tmp = {
                {mouse_vec.x - window_pos.x, mouse_vec.y - window_pos.y},
                sfWhite,
                {0, 0}
            };
            sfVertexArray_append(road_r, tmp);
            if (sfVertexArray_getVertexCount(road_r) > 1)
                sfVertexArray_append(road_r, tmp);
        } else if (clicked && !sfKeyboard_isKeyPressed(sfKeyA))
            clicked = false;
        if (sfKeyboard_isKeyPressed(sfKeyZ) && !ended) {
            sfVertexArray_append(road_r, sfVertexArray_getVertex(road_r, 0));
            ended = true;
            clicked = false;
        }
        sfRenderWindow_clear(window, sfColor_fromRGBA(44, 44, 44, 128));
        sfRenderWindow_drawVertexArray(window, road_r, NULL);
        sfRenderWindow_display(window);
    }
    sfRenderWindow_destroy(window);
    return 0;
}