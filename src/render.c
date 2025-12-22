//#include "config.h"
#include "base_masks.h"
#include "config.h"
#include "render.h"

int screen_fd;

fb* init_framebuffer(point dim){
    //add malloc checks
    fb* out = malloc(sizeof(fb));
    out->size = dim.x*dim.y;
    out->arr = calloc(out->size,sizeof(uint32_t));//add malloc checks
    out->dim = dim;
    return out;
}

void fb_set_pix(fb* f,point a,pixel color){
    *(f->arr + a.y * f->dim.x + a.x) = color.val;
}

void fb_set_pix_helper(fb* f,int x, int y, pixel color){
    *(f->arr + y * f->dim.x + x) = color.val;
}

void cls(fb* f){
    for (int i=0;i<f->dim.x*f->dim.y;i++){
            *(f->arr + i) = ALPHA;//decided to write directly to minimize function calling overhead
    }
}

void init_screen(){
    screen_fd = open("/dev/fb0", O_RDWR);
}

void clsd(fb* f){
    memset(f->arr, 0, BUFF_SIZE);
}

void draw(fb* f,uint32_t* screen) {
    memcpy(screen, f->arr, BUFF_SIZE);
}

float slope(point a, point b){
    return (((float)(b.y-a.y))/((float)(b.x-a.x)));
}

float inv_slope(point a, point b){
    return (((float)(b.x-a.x))/((float)(b.y-a.y)));
}

// void draw_line(point a, point b, fb* f, pixel color){//always order inputs by abscissae     
//     float m = slope(a,b);
//     float k = inv_slope(a,b);
//     if (m > 1 || m < -1){
//         int start = a.y>b.y?b.y:a.y;
//         int end = a.y>b.y?a.y:b.y;
//         for (int i = start;i<end;i++){
//             *(f->arr + f->dim.x*i +(int)((float)k*(i-a.y)) + a.x) = color.val;
//         }    
//     } else {
//         for (int i = a.x;i<b.x;i++){
//             *(f->arr + f->dim.x*((int)((float)m*(i-a.x)+a.y)) + i) = color.val;
//         }    
//     }
// }

// void fb_write(fb* f,point x,pixel a){
// //fill later
//     return;    
// }