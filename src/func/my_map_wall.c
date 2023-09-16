#include "../../includes/my.h"

void my_map_draw_wall(my_map_t *map, sfRenderWindow *window)
{
    if (sfKeyboard_isKeyPressed(sfKeyW)) {
        map->status = no_mode;
        sfVertex pt = sfVertexArray_getVertex(map->walls[map->walls_n - 1], 0);
        sfVertexArray_append(map->walls[map->walls_n], pt);
    }

    if (sfKeyboard_isKeyPressed(sfKeySpace)) {
        sfVector2i window_pos = sfRenderWindow_getPosition(window);
        sfVector2i pos = sfMouse_getPosition(NULL);
        pos.x -= window_pos.x;
        pos.y -= window_pos.y;
        sfVertex pt = {pos, sfWhite, {0, 0}};
        sfVertexArray_append(map->walls[map->walls_n - 1], pt);
    }
}
