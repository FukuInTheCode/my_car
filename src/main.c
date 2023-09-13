#include "../includes/my.h"


int main(int argc, char* argv[])
{
    sfVideoMode mode = {2000, 1500, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode, "my_car", sfDefaultStyle, NULL);
    sfEvent event;
    sfVertexArray *road_right = sfVertexArray_create();
    VERTEX_DECLA(v1, 1282, 742, sfWhite);
    sfVertexArray_append(road_left, v1);
    VERTEX_DECLA(v2, 1293, 1206, sfWhite);
    sfVertexArray_append(road_left, v2);
    VERTEX_DECLA(v3, 1580, 1436, sfWhite);
    sfVertexArray_append(road_left, v3);
    VERTEX_DECLA(v4, 2133, 1460, sfWhite);
    sfVertexArray_append(road_left, v4);
    VERTEX_DECLA(v5, 2424, 1168, sfWhite);
    sfVertexArray_append(road_left, v5);
    VERTEX_DECLA(v6, 2430, 766, sfWhite);
    sfVertexArray_append(road_left, v6);
    VERTEX_DECLA(v7, 2136, 497, sfWhite);
    sfVertexArray_append(road_left, v7);
    VERTEX_DECLA(v8, 1582, 493, sfWhite);
    sfVertexArray_append(road_left, v8);
    sfVertexArray_setPrimitiveType(road_left, sfLines);
    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }

        sfRenderWindow_clear(window, sfColor_fromRGBA(44, 44, 44, 128));
        sfRenderWindow_drawVertexArray()
        sfRenderWindow_display(window);
    }
    sfRenderWindow_destroy(window);
    return 0;
}