#pragma once
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "point.h"
#include "pixel.h"
#include <fcntl.h>
//#include "sprite.h"

typedef struct framebuffer{
    uint32_t* arr;
    size_t size;
    point dim;
}fb;

typedef struct triangle{
    point a;
    point b;
    point c;
}triangle;

fb* init_framebuffer(point dim);
void fb_set_pix(fb* f,point a,pixel color);
void fb_set_pix_helper(fb* f,int x, int y, pixel color);

void cls(fb* f);

extern size_t BUFF_SIZE;
extern int screen_fd;

void init_screen();
void clsd(fb* f);
void draw(fb* f,uint32_t* screen);
float slope(point a, point b);
float inv_slope(point a, point b);
void draw_line(point a, point b, fb* f, pixel color);

void draw_bounds(uint32_t* frame,point dim);

void draw_net(uint32_t* frame, point dim);

void draw_bg(uint32_t* frame, point dim);