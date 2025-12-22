#pragma once
#include <unistd.h>
#include <stdint.h>

typedef struct sz_point{
    size_t x;
    size_t y;
}spoint;

typedef struct sprite{
    uint32_t* arr;
    spoint dim;
}sprite;

sprite load_sprite();//fill this