#include <stdint.h>
#include <unistd.h>
#include "base_masks.h"
#include "point.h"
#include "render.h"

int square(int i) {return i*i;}

void draw_circle(fb* f,int r, point centre){
    for (int i=0;i<(f->dim).x;i++){
        for (int j=0;j<(f->dim).y;j++){
            if (square(i-centre.x)+square(j-centre.y)<=r*r) *(f->arr + j*f->dim.x + i) = WHITE;//decided to write directly to minimize function calling overhead
        }
    }
}