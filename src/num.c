#include "num.h"
#include "config.h"
#include "base_masks.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int bind(int min, int val, int max){
    if (val < min) return min;
    if (val > max) return max;
    return val; 
}

void draw_rect(int x, int y, int height, int width,fb* frame,uint32_t color){
    for (int i=x;i<x+width;i++){
        for (int j=y;j<y+height;j++){
            *(frame->arr + bind(0, j, SCR_Y) * SCR_X + bind(0,i,SCR_X)) = color;
        }
    }
}

uint32_t invert(uint32_t color){
    return color ^ 0x00ffffff;
}

void draw_rect_overlay(int x, int y, int height, int width,fb* frame,uint32_t color){
    uint32_t* curr;
    for (int i=x;i<x+width;i++){
        for (int j=y;j<y+height;j++){
            curr = (frame->arr + bind(0, j, SCR_Y) * SCR_X + bind(0,i,SCR_X)) ;
            //if (*curr) *curr ^= 0x00ffffff;
            //else
            *curr = color; 
        }
    }
}

void draw_0(int x,int y, fb* frame,font FONT){
    draw_rect_overlay(x, y,FONT.weight, FONT.width, frame,WHITE);
    draw_rect_overlay(x, y + FONT.weight, FONT.height - 2*FONT.weight, FONT.weight, frame, WHITE);
    draw_rect_overlay(x + FONT.width - FONT.weight, y + FONT.weight, FONT.height - 2*FONT.weight, FONT.weight, frame,WHITE);
    draw_rect_overlay(x, y + FONT.height - FONT.weight,FONT.weight, FONT.width, frame,WHITE);
}
void draw_1(int x,int y, fb* frame,font FONT){
    draw_rect_overlay(x + FONT.width - 1.5*FONT.weight, y, FONT.weight,FONT.weight*1.5+1,frame,WHITE);
    draw_rect_overlay(x + FONT.width - FONT.weight, y + FONT.weight,FONT.height - FONT.weight,FONT.weight,frame, WHITE);
}
void draw_2(int x,int y, fb* frame,font FONT){
    draw_rect_overlay(x, y,FONT.weight, FONT.width, frame,WHITE);
    draw_rect_overlay(x, y + FONT.height / 2 - FONT.weight/2,FONT.weight, FONT.width, frame,WHITE);
    draw_rect_overlay(x, y + FONT.height - FONT.weight ,FONT.weight, FONT.width, frame,WHITE);
    draw_rect_overlay(x, y + FONT.height/2 + FONT.weight/2, FONT.height/2 - FONT.weight - FONT.weight/2, FONT.weight, frame, WHITE);
    draw_rect_overlay(x + FONT.width - FONT.weight, y + FONT.weight, FONT.height/2 - FONT.weight - FONT.weight/2, FONT.weight, frame, WHITE);
}
void draw_3(int x,int y, fb* frame,font FONT){
    draw_rect_overlay(x, y,FONT.weight, FONT.width, frame,WHITE);
    draw_rect_overlay(x + FONT.weight/2, y + FONT.height / 2 - FONT.weight/2,FONT.weight, FONT.width - FONT.weight/2, frame,WHITE);
    draw_rect_overlay(x, y + FONT.height - FONT.weight ,FONT.weight, FONT.width, frame,WHITE);
    draw_rect_overlay(x + FONT.width - FONT.weight, y + FONT.height/2 + FONT.weight/2, FONT.height/2 - FONT.weight - FONT.weight/2, FONT.weight, frame, WHITE);
    draw_rect_overlay(x + FONT.width - FONT.weight, y + FONT.weight, FONT.height/2 - FONT.weight - FONT.weight/2, FONT.weight, frame, WHITE);
}
void draw_4(int x,int y, fb* frame,font FONT){
    draw_rect_overlay(x + FONT.width - FONT.weight, y,FONT.height, FONT.weight, frame,WHITE);
    draw_rect_overlay(x , y,FONT.height/2 - FONT.weight/2, FONT.weight, frame,WHITE);
    draw_rect_overlay(x, y + FONT.height/2 - FONT.weight/2,FONT.weight,FONT.width - FONT.weight, frame,WHITE);
}
void draw_5(int x,int y, fb* frame,font FONT){
    draw_rect_overlay(x, y,FONT.weight, FONT.width, frame,WHITE);
    draw_rect_overlay(x, y + FONT.height / 2 - FONT.weight/2,FONT.weight, FONT.width, frame,WHITE);
    draw_rect_overlay(x, y + FONT.height - FONT.weight ,FONT.weight, FONT.width, frame,WHITE);
    draw_rect_overlay(x + FONT.width -FONT.weight, y + FONT.height/2 + FONT.weight/2, FONT.height/2 - FONT.weight - FONT.weight/2, FONT.weight, frame, WHITE);
    draw_rect_overlay(x , y + FONT.weight, FONT.height/2 - FONT.weight - FONT.weight/2, FONT.weight, frame, WHITE);
}
void draw_6(int x,int y, fb* frame,font FONT){
    draw_rect_overlay(x, y,FONT.weight, FONT.width, frame,WHITE);
    draw_rect_overlay(x, y + FONT.height / 2 - FONT.weight/2,FONT.weight, FONT.width, frame,WHITE);
    draw_rect_overlay(x, y + FONT.height - FONT.weight ,FONT.weight, FONT.width, frame,WHITE);
    draw_rect_overlay(x + FONT.width - FONT.weight + FONT.weight/7, y + FONT.height/2 + FONT.weight/2, FONT.height/2 - FONT.weight - FONT.weight/2, FONT.weight - FONT.weight/7, frame, WHITE);//b_right_vert
    draw_rect_overlay(x , y + FONT.weight, FONT.height/2 - FONT.weight - FONT.weight/2, FONT.weight, frame, WHITE);
    draw_rect_overlay(x, y + FONT.height/2 + FONT.weight/2, FONT.height/2 - FONT.weight - FONT.weight/2, FONT.weight, frame, WHITE);
}
void draw_7(int x,int y, fb* frame,font FONT){
    int a = 0;
    int offset = 0;
    draw_rect_overlay(x, y,FONT.weight, FONT.width, frame,WHITE);
    draw_rect_overlay(x + FONT.width - FONT.weight, y + FONT.weight,FONT.height/2 - FONT.weight +a,FONT.weight,frame, WHITE);
    draw_rect_overlay(x + FONT.width - FONT.weight - offset, y + FONT.height/2 + a,FONT.height/2 -a,FONT.weight,frame, WHITE);
}
void draw_8(int x,int y, fb* frame,font FONT){
    draw_rect_overlay(x, y,FONT.weight, FONT.width, frame,WHITE);
    draw_rect_overlay(x, y + FONT.height / 2 - FONT.weight/2,FONT.weight, FONT.width, frame,WHITE);
    draw_rect_overlay(x, y + FONT.height - FONT.weight ,FONT.weight, FONT.width, frame,WHITE);
    draw_rect_overlay(x + FONT.width - FONT.weight + FONT.weight/7, y + FONT.height/2 + FONT.weight/2, FONT.height/2 - FONT.weight - FONT.weight/2, FONT.weight - FONT.weight/7, frame, WHITE);//b_right_vert
    draw_rect_overlay(x , y + FONT.weight, FONT.height/2 - FONT.weight - FONT.weight/2, FONT.weight, frame, WHITE);
    draw_rect_overlay(x, y + FONT.height/2 + FONT.weight/2, FONT.height/2 - FONT.weight - FONT.weight/2, FONT.weight, frame, WHITE);
    draw_rect_overlay(x + FONT.width - FONT.weight, y + FONT.weight, FONT.height/2 - FONT.weight - FONT.weight/2, FONT.weight, frame, WHITE);
}
void draw_9(int x,int y, fb* frame,font FONT){
    int adj = FONT.weight/7;
    draw_rect_overlay(x, y,FONT.weight, FONT.width, frame,WHITE);
    draw_rect_overlay(x, y + FONT.height / 2 - FONT.weight/2,FONT.weight, FONT.width, frame,WHITE);
    draw_rect_overlay(x, y + FONT.height - FONT.weight ,FONT.weight, FONT.width, frame,WHITE);
    draw_rect_overlay(x + FONT.width - FONT.weight + FONT.weight/7, y + FONT.height/2 + FONT.weight/2, FONT.height/2 - FONT.weight - FONT.weight/2, FONT.weight - FONT.weight/7, frame, WHITE);//b_right_vert
    draw_rect_overlay(x , y + FONT.weight, FONT.height/2 - FONT.weight - FONT.weight/2, FONT.weight-adj, frame, WHITE);
    //draw_rect_overlay(x, y + FONT.height/2 + FONT.weight/2, FONT.height/2 - FONT.weight - FONT.weight/2, FONT.weight, frame, WHITE);
    draw_rect_overlay(x + FONT.width - FONT.weight, y + FONT.weight, FONT.height/2 - FONT.weight - FONT.weight/2, FONT.weight, frame, WHITE);
}
void draw_number(int x,int y,int i,fb* frame,font FONT){
    switch (i){
        case 0:
            draw_0(x, y, frame,FONT); 
            break;
        case 1:
            draw_1(x, y, frame,FONT); 
            break;
        case 2:
            draw_2(x, y, frame,FONT); 
            break;
        case 3:
            draw_3(x, y, frame,FONT); 
            break;
        case 4:
            draw_4(x, y, frame,FONT); 
            break;
        case 5:
            draw_5(x, y, frame,FONT); 
            break;
        case 6:
            draw_6(x, y, frame,FONT); 
            break;
        case 7:
            draw_7(x, y, frame,FONT); 
            break;
        case 8:
            draw_8(x, y, frame,FONT); 
            break;
        case 9:
            draw_9(x, y, frame,FONT); 
            break;
    }
}
void draw_num_char(int x,int y,char i,fb* frame,font FONT){
    switch (i){
        case '0':
            draw_0(x, y, frame,FONT); 
            break;
        case '1':
            draw_1(x, y, frame,FONT); 
            break;
        case '2':
            draw_2(x, y, frame,FONT); 
            break;
        case '3':
            draw_3(x, y, frame,FONT); 
            break;
        case '4':
            draw_4(x, y, frame,FONT); 
            break;
        case '5':
            draw_5(x, y, frame,FONT); 
            break;
        case '6':
            draw_6(x, y, frame,FONT); 
            break;
        case '7':
            draw_7(x, y, frame,FONT); 
            break;
        case '8':
            draw_8(x, y, frame,FONT); 
            break;
        case '9':
            draw_9(x, y, frame,FONT); 
            break;
    }
}

void draw_num_string_centered(int x, int y,int a,fb* frame, font FONT){
    char str[20];
    sprintf(str, "%d", a);
    int n = strlen(str);
    int width = n*(FONT.width+(padding_x-1));
    x = x - width/2;
    y = y - FONT.height/2;
    for (int i=0;i<n;i++){
        draw_num_char(x, y,str[i] , frame,FONT);
        x+=FONT.width+padding_x;
    }
}

void draw_A(int x, int y, fb *frame,font FONT){
    draw_rect_overlay(x,  y, FONT.weight, FONT.width, frame, WHITE);//top 
    draw_rect_overlay(x, y + FONT.weight, FONT.height - FONT.weight, FONT.weight, frame, WHITE);//left bar
    draw_rect_overlay(x + FONT.weight,  y + (FONT.height - FONT.weight)/2 , FONT.weight, FONT.width - FONT.weight, frame, WHITE);//middle bar
    draw_rect_overlay(x + FONT.width - FONT.weight, y + FONT.weight, FONT.height - FONT.weight, FONT.weight, frame, WHITE);//right bar
}

void draw_F(int x, int y, fb *frame,font FONT){
    draw_rect_overlay(x,  y, FONT.weight, FONT.width, frame, WHITE);//top 
    draw_rect_overlay(x, y + FONT.weight, FONT.height - FONT.weight, FONT.weight, frame, WHITE);//left bar
    draw_rect_overlay(x + FONT.weight,  y + (FONT.height - FONT.weight)/2 , FONT.weight, FONT.width - FONT.weight, frame, WHITE);//middle h bar
    //draw_rect_overlay(x + FONT.width - FONT.weight, y + FONT.weight, FONT.height / 2 - FONT.weight - FONT.width / 2, FONT.weight, frame, WHITE);//right bar
}

void draw_G(int x,int y, fb* frame,font FONT){
    draw_rect_overlay(x, y,FONT.weight, FONT.width, frame,WHITE);
    draw_rect_overlay(x, y + FONT.weight, FONT.height - 2*FONT.weight, FONT.weight, frame, WHITE);
    draw_rect_overlay(x + FONT.width - FONT.weight, y + FONT.height / 2 , FONT.height / 2 - FONT.weight, FONT.weight, frame,WHITE);
    draw_rect_overlay(x, y + FONT.height - FONT.weight,FONT.weight, FONT.width, frame,WHITE);
}

void draw_N(int x,int y, fb* frame,font FONT){
    draw_rect_overlay(x, y, FONT.height, (FONT.weight*4)/5, frame, WHITE);
    draw_rect_overlay(x + FONT.width - (FONT.weight*4)/5, y, FONT.height, (FONT.weight*4)/5, frame, WHITE);
    draw_rect_overlay(x + (FONT.weight*4) / 5, y, FONT.height / 2, FONT.weight / 2 + FONT.weight/10, frame, WHITE);
    draw_rect_overlay(x + FONT.width - (FONT.weight*4)/5 - FONT.weight / 2 - FONT.weight/10, y + FONT.height/2, FONT.height/2, FONT.weight / 2 + FONT.weight/10,frame, WHITE);
}

void draw_O(int x,int y, fb* frame, font FONT){
    draw_rect_overlay(x, y,FONT.weight, FONT.width, frame,WHITE);
    draw_rect_overlay(x, y + FONT.weight, FONT.height - 2*FONT.weight, FONT.weight, frame, WHITE);
    draw_rect_overlay(x + FONT.width - FONT.weight, y + FONT.weight, FONT.height - 2*FONT.weight, FONT.weight, frame,WHITE);
    draw_rect_overlay(x, y + FONT.height - FONT.weight,FONT.weight, FONT.width, frame,WHITE);
}

void draw_P(int x, int y, fb *frame, font FONT){
    draw_rect_overlay(x,  y, FONT.weight, FONT.width, frame, WHITE);//top 
    draw_rect_overlay(x, y + FONT.weight, FONT.height - FONT.weight, FONT.weight, frame, WHITE);//left bar
    draw_rect_overlay(x + FONT.weight,  y + (FONT.height - FONT.weight)/2 , FONT.weight, FONT.width - FONT.weight, frame, WHITE);//middle h bar
    draw_rect_overlay(x + FONT.width - FONT.weight, y + FONT.weight, FONT.height / 2 - FONT.weight - FONT.weight / 2, FONT.weight, frame, WHITE);//right bar
}

void draw_S(int x, int y, fb* frame, font FONT){
    draw_rect_overlay(x, y,FONT.weight, FONT.width, frame,WHITE);
    draw_rect_overlay(x, y + FONT.height / 2 - FONT.weight/2,FONT.weight, FONT.width, frame,WHITE);
    draw_rect_overlay(x, y + FONT.height - FONT.weight ,FONT.weight, FONT.width, frame,WHITE);
    draw_rect_overlay(x + FONT.width -FONT.weight , y + FONT.height/2 + FONT.weight/2, FONT.height/2 - FONT.weight - FONT.weight/2, FONT.weight, frame, WHITE);
    draw_rect_overlay(x , y + FONT.weight , FONT.height/2 - FONT.weight - FONT.weight/2, FONT.weight, frame, WHITE);
}

void draw_R(int x, int y, fb *frame,font FONT){
    draw_rect_overlay(x,  y, FONT.weight, FONT.width, frame, WHITE);//top 
    draw_rect_overlay(x, y + FONT.weight, FONT.height - FONT.weight, FONT.weight, frame, WHITE);//left bar
    draw_rect_overlay(x + FONT.weight,  y + (FONT.height - FONT.weight)/2 , FONT.weight, FONT.width - FONT.weight, frame, WHITE);//middle h bar
    draw_rect_overlay(x + FONT.width - FONT.weight, y + FONT.weight, FONT.height / 2 - FONT.weight - FONT.weight / 2, FONT.weight, frame, WHITE);//right bar
    draw_rect_overlay(x + FONT.width - 2*(FONT.weight),y + FONT.weight/2 + FONT.height / 2 ,(FONT.height - FONT.weight)/4 ,FONT.weight,frame,WHITE);
    draw_rect_overlay(x + FONT.width - (FONT.weight),y + FONT.weight/2 + FONT.height / 2 + (FONT.height - FONT.weight)/4, (FONT.height - FONT.weight)/4,FONT.weight,frame,WHITE);
}

void draw_T(int x, int y, fb* frame, font FONT){
    draw_rect_overlay(x, y, FONT.weight, FONT.width, frame, WHITE);
    draw_rect_overlay(x + (FONT.width - FONT.weight)/2, y + FONT.weight, FONT.height - FONT.weight, FONT.weight, frame, WHITE);
}