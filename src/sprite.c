#include "sprite.h"
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include "base_masks.h"
#include "point.h"
#include "render.h"
#include "config.h"

int square(int i) {return i*i;}

void draw_circle(fb* f,int r, point centre){
    for (int i=0;i<(f->dim).x;i++){
        for (int j=0;j<(f->dim).y;j++){
            if (square(i-centre.x)+square(j-centre.y)<=r*r) *(f->arr + j*f->dim.x + i) = WHITE;//decided to write directly to minimize function calling overhead
        }
    }
}

sprite* load_sprite(FILE* file){
    if (!file) return NULL;
    sprite* out = malloc(sizeof(sprite));
    fread(&out->dim.x,sizeof(uint32_t),1,file);
    fread(&out->dim.y,sizeof(uint32_t),1,file);
    out->arr = malloc(sizeof(uint32_t)*out->dim.x*out->dim.y);
    fread(out->arr,sizeof(uint32_t),out->dim.x*out->dim.y,file);
    return out;
}

sprite* load_sprite_headless(int x, int y, FILE* file){
    if (!file) return NULL;
    sprite* out = malloc(sizeof(sprite));
    out->dim.x = x;
    out->dim.y = y;
    out->arr = malloc(sizeof(uint32_t)*out->dim.x*out->dim.y);
    fread(out->arr,sizeof(uint32_t),out->dim.x*out->dim.y,file);
    return out;
}

// void draw_sprite(int x, int y, sprite* arr, fb *f){
//     if (!arr || !f) return; // Safety first

//     for (int i = 0; i < arr->dim.x; i++){
//         for (int j = 0; j < arr->dim.y; j++){
            
//             // SCREEN Coordinates
//             int screen_x = x + i;
//             int screen_y = y + j;

//             // Bounds Check (Prevents Segfaults at edges)
//             if (screen_x < 0 || screen_x >= f->dim.x) continue;
//             if (screen_y < 0 || screen_y >= f->dim.y) continue;

//             // THE FIX: Use arr->dim.x for the sprite, SCR_X for the screen
//             uint32_t color = arr->arr[j * arr->dim.x + i];
            
//             // Optional: Cheap transparency (Skip pure black pixels)
//             // if (color == 0xFF000000) continue; 

//             f->arr[screen_y * SCR_X + screen_x] = color;
//         }
//     }
// }