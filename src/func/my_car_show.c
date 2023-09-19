#include "../../includes/my.h"

void my_car_draw(sfRenderWindow *window, void *car_ptr, void *map_ptr)
{
    my_car_t *car = (my_car_t *)car_ptr;
    sfRectangleShape *car_rect = sfRectangleShape_create();
    sfRectangleShape_setPosition(car->rect, car->pos);
    sfRectangleShape_setSize(car->rect, car->size);
    sfRectangleShape_setFillColor(car->rect, sfRed);
    sfVector2f car_origin = {car->size.x / 2., car->size.y / 2.};
    sfRectangleShape_setOrigin(car->rect, car_origin);
    sfRenderWindow_drawRectangleShape(window, car->rect, NULL);
}
