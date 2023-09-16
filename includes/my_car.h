#ifndef MY_CAR_H
#define MY_CAR_H

#include "my_neuralnetwork.h"
#include "my_matrix.h"

typedef struct {
    sfVertexArray *walls;
    sfVector2f start;
    sfVertex *gates;
    uint32_t walls_n;
    uint32_t gates_n;
} my_map_t;


#endif
