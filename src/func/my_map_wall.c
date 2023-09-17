#define MATRIX_CHECK_ALLOC
#include "../../includes/my.h"

void my_map_alloc_wall(my_map_t *map)
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

void my_map_add_wall(my_map_t *map, sfRenderWindow *window)
{
    if (sfKeyboard_isKeyPressed(sfKeyE) && sfVertexArray_getVertexCount(map->walls[map->walls_n - 1]) > 1) {
        map->status = no_mode;
        sfVertex ith_vertex = *sfVertexArray_getVertex(map->walls[map->walls_n - 1], 0);
        sfVertex pt = {{ith_vertex.position.x, ith_vertex.position.y}, sfWhite, {0, 0}};
        sfVertexArray_append(map->walls[map->walls_n - 1], pt);
        my_map_alloc_wall(map);
    } else if (sfKeyboard_isKeyPressed(sfKeySpace)) {
        sfVector2i window_pos = sfRenderWindow_getPosition(window);
        sfVector2i pos = sfMouse_getPosition(NULL);
        pos.x -= window_pos.x;
        pos.y -= window_pos.y;
        sfVertex pt = {{pos.x, pos.y}, sfWhite, {0, 0}};
        sfVertexArray_append(map->walls[map->walls_n - 1], pt);
        if (sfVertexArray_getVertexCount(map->walls[map->walls_n - 1]) > 1)
            sfVertexArray_append(map->walls[map->walls_n - 1], pt);
    }
}

void my_map_del_wall(my_map_t *map)
{
    if (map->walls_n <= 1)
        return;
    sfVertexArray **tmp = map->walls;
    map->walls = calloc(map->walls_n - 1, sizeof(sfVertexArray *));
    for (uint32_t i = 0; i < map->walls_n - 2; ++i)
        map->walls[i] = tmp[i];
    free(tmp);
    map->walls_n -= 1;
    my_map_alloc_wall(map);
}
