#include "inp_event.h"
#include <linux/input-event-codes.h>
#include <stddef.h>

Mouse mouse;
Keyboard keyboard;
size_t BUFF_SIZE = SCR_X*SCR_Y*sizeof(uint32_t);

void init_mouse(){
    mouse.fd = open("/dev/input/event4",O_RDONLY | O_NONBLOCK);
    mouse.pos.x = SCR_X/1;
    mouse.pos.y = SCR_Y/1;
}

void update_mouse(fb* frame, uint32_t* screen_buff){
    struct input_event event;
    while (read(mouse.fd, &event, sizeof(event))>0){
        if (event.type == EV_REL){
            if(event.code == REL_X) mouse.pos.x+=event.value;
            else if(event.code == REL_Y) mouse.pos.y+=event.value;
        }
        //skipping buttons cuz we don't really need them
    }
    //clamping
    if (mouse.pos.x < 0) mouse.pos.x = 0;
    if (mouse.pos.x > SCR_X - 1) mouse.pos.x = SCR_X - 1;
    if (mouse.pos.y < 0) mouse.pos.y = 0;
    if (mouse.pos.y > SCR_Y - 1) mouse.pos.y =  SCR_Y - 1;
}

void init_kbd(){
    keyboard.fd = open("/dev/input/event4", O_RDONLY | O_NONBLOCK);
    keyboard.state = calloc(KEY_CNT,sizeof(int));
    keyboard.state_size = KEY_CNT;
}

// void update_entity_pos_kbd(entity *obj){
//     int step = 50;
//     if (read(keyboard.fd, &keyboard.ev, sizeof(keyboard.ev)) > 0){
//         if (keyboard.ev.type == EV_KEY){
//                 if (keyboard.ev.code == KEY_W) obj->pos.y-=step*keyboard.ev.value; 
//                 if (keyboard.ev.code == KEY_A) obj->pos.x-=step*keyboard.ev.value;
//                 if (keyboard.ev.code == KEY_S) obj->pos.y+=step*keyboard.ev.value; 
//                 if (keyboard.ev.code == KEY_D) obj->pos.x+=step*keyboard.ev.value;       
//         }
//     }
// }
void update_kbd(){
    while (read(keyboard.fd, &keyboard.ev, sizeof(keyboard.ev)) > 0){
        if (keyboard.ev.type == EV_KEY){
            keyboard.state[keyboard.ev.code] = keyboard.ev.value;
        }
    }
}

// void draw_entity(fb* frame, entity obj, pixel color){
//     if (obj.s == SQUARE){
//         for (int i = -obj.draw_size;i < obj.draw_size;i++){
//             for (int j = -obj.draw_size;j < obj.draw_size;j++){
//                 *(frame->arr + (obj.pos.y+j)*SCR_X + obj.pos.x + i) = color.val;
//             }
//         }
//     }
// }