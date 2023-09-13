#include "../includes/my.h"


int main(int argc, char* argv[])
{
    sfVideoMode mode = {2000, 1500, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode, "my_car", sfDefaultStyle, NULL);
    sfEvent event;
    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }
        if (sfKeyboard_isKeyPressed(sfKeyA))
            printf("%d, %d\n", sfMouse_getPosition(NULL).x, sfMouse_getPosition(NULL).y);
        sfRenderWindow_clear(window, sfColor_fromRGBA(44, 44, 44, 128));
        sfRenderWindow_display(window);
    }
    sfRenderWindow_destroy(window);
    return 0;
}