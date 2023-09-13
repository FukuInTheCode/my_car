#pragma once
#define MYH

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "my_evo.h"
#include "my_car.h"
#include "SFML/Graphics.h"

#define VERTEX_DECLA(n, x, y, c) sfVertex n = {{x, y}, c, {0, 0}}
