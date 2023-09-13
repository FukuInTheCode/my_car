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
    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }
        if (sfKeyboard_isKeyPressed(sfKeyA)) {
            sfVertex tmp = {
                sfMouse_getPosition(window),
                sfWhite,
                {0, 0}
            };
            sfVertexArray_append(road_r, tmp);
        }

        sfRenderWindow_clear(window, sfColor_fromRGBA(44, 44, 44, 128));
        sfRenderWindow_drawVertexArray(window, road_r, NULL);
        sfRenderWindow_display(window);
    }
    sfRenderWindow_destroy(window);
    return 0;
}