#include "../../includes/my.h"

void my_car_draw(sfRenderWindow *window, void *car_ptr, void *map_ptr)
{
    sfRectangleShape *car_rect = sfRectangleShape_create();
    sfRectangleShape_setPosition(car_rect, car->pos);
    sfRectangleShape_setSize(car_rect, car->size);
    sfRectangleShape_setFillColor(car_rect, sfRed);
    sfVector2f car_origin = {car->size.x / 2., car->size.y / 2.};
    sfRectangleShape_setOrigin(car_rect, car_origin);
    sfRenderWindow_drawRectangleShape(window, car_rect, NULL);
    sfRectangleShape_destroy(car_rect);
}
