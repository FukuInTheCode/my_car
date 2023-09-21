#include "../../includes/my.h"

void my_car_draw(sfRenderWindow *window, void *car_ptr, void *map_ptr)
{
    my_car_t *car = (my_car_t *)car_ptr;
    sfRenderWindow_drawRectangleShape(window, car->rect, NULL);
    my_map_t *map = (my_map_t *)map_ptr;
    if (map->tmp == NULL)
        return;
    map->tmp = window;
}
