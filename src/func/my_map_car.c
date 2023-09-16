#include "../../includes/my.h"

void my_map_place_start(my_map_t *map, sfRenderWindow *window)
{
    if (sfKeyboard_isKeyPressed(sfKeySpace)) {
        sfVector2u window_pos = sfRenderWindow_getPosition(window);
        sfVector2u mouse_pos = sfMouse_getPosition(NULL);
        map->start.x = mouse_pos.x - window_pos.y;
        map->start.y = mouse_pos.y - window_pos.y;
        map->status = race_mode;
    }
}
