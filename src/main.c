#include "../includes/my.h"


int main(int argc, char* argv[])
{
    sfVideoMode mode = {2000, 1500, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode, "my_car", sfDefaultStyle, NULL);
    sfEvent event;
    sfVertexArray *road_right = sfVertexArray_create();
    sfVertex v1 = {
    sfVertexArray_append(road_left, v1);
    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }

        sfRenderWindow_clear(window, sfColor_fromRGBA(44, 44, 44, 128));
        sfRenderWindow_display(window);
    }
    sfRenderWindow_destroy(window);
    return 0;
}