#pragma once
#include <fcntl.h>
#include <linux/input-event-codes.h>
#include <linux/input.h>            
#include <unistd.h>
#include <sys/ioctl.h>
#include "render.h"
#include "entity.h"

#define SCR_X 2560
#define SCR_Y 1600

typedef struct mouse{
    int fd;
    point pos;
    int left_click;
    int right_click;
}Mouse;

extern Mouse mouse;

void init_mouse();

void update_mouse(fb* frame, uint32_t* screen_buff);

#define W_ 0
#define A_ 1
#define S_ 2
#define D_ 3
#define SPACE_ 4

typedef struct keyboard{
    int fd;    
    int* state;
    int state_size;
    struct input_event ev;
}Keyboard;

extern Keyboard keyboard;

void init_kbd();

void update_entity_pos_kbd(entity* obj);

void update_kbd();

void draw_entity(fb* frame, entity obj, pixel color);