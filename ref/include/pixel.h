#pragma once
#include <stdint.h>

typedef struct pixel{
    uint32_t val;
}pixel;

pixel mkpixel(uint32_t col);

pixel pix(uint32_t r,uint32_t g,uint32_t b,uint32_t a);//fill later