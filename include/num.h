#include "render.h"
#include <stdio.h>
#include <stdlib.h>

#define padding_y 100
#define padding_x 20

//#define weight 25
#define fh 100
#define fw 70

#define title_weight 50
#define title_fh 200
#define title_fw 140

typedef struct font{
    int height;
    int width;
    int weight;
}font;

int bind(int a,int b,int c);
void draw_rect(int x, int y, int height, int width,fb* frame, uint32_t color);
void draw_rect_overlay(int x, int y, int height, int width,fb* frame, uint32_t color);
void draw_0(int x,int y, fb* frame,font FONT);
void draw_1(int x,int y, fb* frame,font FONT);
void draw_2(int x,int y, fb* frame,font FONT);
void draw_3(int x,int y, fb* frame,font FONT);
void draw_4(int x,int y, fb* frame,font FONT);
void draw_5(int x,int y, fb* frame,font FONT);
void draw_6(int x,int y, fb* frame,font FONT);
void draw_7(int x,int y, fb* frame,font FONT);
void draw_8(int x,int y, fb* frame,font FONT);
void draw_9(int x,int y, fb* frame,font FONT);
void draw_number(int x, int y, int i, fb* frame,font FONT);
void draw_num_char(int x,int y,char i,fb* frame,font FONT);
void draw_num_string_centered(int x, int y,int a,fb* frame,font FONT);

void draw_A(int x, int y, fb *frame,font FONT);
void draw_F(int x, int y, fb *frame,font FONT);
void draw_G(int x,int y, fb* frame,font FONT);
void draw_N(int x,int y, fb* frame,font FONT);
void draw_O(int x,int y, fb* frame,font FONT);
void draw_P(int x, int y, fb *frame,font FONT);
void draw_R(int x, int y, fb* frame, font FONT);
void draw_S(int x, int y, fb* frame, font FONT);
void draw_T(int x, int y, fb* frame, font FONT);
void draw_S(int x, int y, fb* frame, font FONT);

void draw_string(int x,int y, char* str, fb* frame, font FONT);