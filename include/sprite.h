#pragma once
#include <unistd.h>
#include <stdint.h>
#include "point.h"
#include <stdio.h>
#include "render.h"

int square(int i);
typedef struct sz_point{
    size_t x;
    size_t y;
}spoint;

typedef struct sprite{
    uint32_t* arr;
    point dim;
}sprite;

sprite* load_sprite(FILE* file);//fill this
sprite* load_sprite_headless(int x,int y,FILE* file);
void draw_sprite(int x,int y,sprite* arr, fb* f);