#include "../../includes/my.h"

void my_map_place_start(my_map_t *map, sfRenderWindow *window)
{
    if (sfKeyboard_isKeyPressed(sfKeySpace)) {
        sfVector2i window_pos = sfRenderWindow_getPosition(window);
        sfVector2i mouse_pos = sfMouse_getPosition(NULL);
        map->start.x = mouse_pos.x - window_pos.y;
        map->start.y = mouse_pos.y - window_pos.y;
        map->status = no_mode;
    }
}
