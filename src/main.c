#include "../includes/my.h"


int main(int argc, char* argv[])
{
    sfVideoMode mode = {2000, 1500, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode, "my_car", sfDefaultStyle, NULL);
    sfEvent event;
    sfVertexArray *road_r = sfVertexArray_create();
    sfVertexArray *road_l = sfVertexArray_create();
    sfVertexArray *current_border = road_r;
    sfVertexArray_setPrimitiveType(current_border, sfLines);
    sfVector2i window_pos = sfRenderWindow_getPosition(window);
    bool ended = false;
    bool clicked = false;
    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }
        if (sfKeyboard_isKeyPressed(sfKeyA) && !clicked && !ended) {
            printf("%zu\n", sfVertexArray_getVertexCount(current_border));
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
            sfVertexArray_append(current_border, *sfVertexArray_getVertex(current_border, 0));
            clicked = false;
            if (current_border == road_l)
                ended = true;
            else
                current_border = road_l;
        }
        sfRenderWindow_clear(window, sfColor_fromRGBA(44, 44, 44, 128));
        sfRenderWindow_drawVertexArray(window, road_r, NULL);
        sfRenderWindow_drawVertexArray(window, road_l, NULL);
        sfRenderWindow_display(window);
    }
    sfRenderWindow_destroy(window);
    return 0;
}