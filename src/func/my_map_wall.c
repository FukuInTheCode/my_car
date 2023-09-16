#define MATRIX_CHECK_ALLOC
#include "../../includes/my.h"

void my_map_add_wall(my_map_t *map)
{
    sfVertexArray **tmp_walls = map->walls;
    map->walls = calloc(map->walls_n + 1, sizeof(sfVertexArray *));
    check_alloc(map->walls);
    for (uint32_t i = 0; i < map->walls_n; ++i)
        map->walls[i] = tmp_walls[i];
    map->walls_n += 1;
    map->walls[map->walls_n - 1] = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(map->walls[map->walls_n - 1], sfLines);

}

void my_map_draw_wall(my_map_t *map, sfRenderWindow *window)
{
    if (sfKeyboard_isKeyPressed(sfKeyW)) {
        map->status = no_mode;
        sfVertex pt = *sfVertexArray_getVertex(map->walls[map->walls_n - 1], 0);
        sfVertexArray_append(map->walls[map->walls_n], pt);
        my_map_add_wall(map);
    }

    if (sfKeyboard_isKeyPressed(sfKeySpace)) {
        sfVector2i window_pos = sfRenderWindow_getPosition(window);
        sfVector2i pos = sfMouse_getPosition(NULL);
        pos.x -= window_pos.x;
        pos.y -= window_pos.y;
        sfVertex pt = {{pos.x, pos.y}, sfWhite, {0, 0}};
        sfVertexArray_append(map->walls[map->walls_n - 1], pt);
    }
}
