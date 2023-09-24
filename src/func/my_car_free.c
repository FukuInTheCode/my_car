#include "../../includes/my.h"

void my_car_free(void *car_ptr, void *map)
{
    my_car_t *car = (my_car_t *)car_ptr;
    my_nn_free(&(car->brain));
    sfRectangleShape_destroy(car->rect);
}
