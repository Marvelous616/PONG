#include <linux/input-event-codes.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <math.h>
#include "base_masks.h"
#include "point.h"
#include "pixel.h"
#include "render.h"
#include "inp_event.h"
#include "entity.h"
#include "gameloop.h"
//masks
static struct fb_var_screeninfo vinfo;
static struct fb_fix_screeninfo finfo;
extern int screen_fd;

typedef struct base_context{
    int frame_counter;
    point screen_size;
}context;

static context CONTEXT;
extern Mouse mouse;
extern Keyboard keyboard;

void init_context(){
    return;
}

static int centre_x = SCR_X/2;
static int centre_y = SCR_Y/2;

//typedef struct global_force{}global_force;

int point_dist(point a, point b){
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

void bound_check(entity* obj){
    if (obj->pos.x > SCR_X - obj->draw_size) obj->pos.x = SCR_X - obj->draw_size;
    if (obj->pos.x < obj->draw_size) obj->pos.x = 0 + obj->draw_size;
    if (obj->pos.y > SCR_Y - obj->draw_size) obj->pos.y = SCR_Y - obj->draw_size;
    if (obj->pos.y < obj->draw_size) obj->pos.y = 0 + obj->draw_size;
}

void force_update(){
    vinfo.activate = FB_ACTIVATE_NOW;
    ioctl(screen_fd, FBIOPAN_DISPLAY, &vinfo); 
}
static entity player;
int main(){
    point dim;
    dim.x = SCR_X;
    dim.y = SCR_Y;
    fb* frame = init_framebuffer(dim);
    init_screen();
    
    ioctl(screen_fd, FBIOGET_VSCREENINFO, &vinfo);
    ioctl(screen_fd, FBIOGET_FSCREENINFO, &finfo);
    uint32_t* screen_buff = (uint32_t*)mmap( 0, finfo.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, screen_fd, 0);
    
    init_mouse();
    init_kbd();

    point centre = mkpoint(SCR_X/2,SCR_Y/2);
    pixel alpha = mkpixel(ALPHA);
    pixel red = mkpixel(RED);
    pixel white = mkpixel(WHITE);
    player = init_entity_static(centre);
    player.pos = mkpoint(SCR_X/2,SCR_Y/2);
    
    float fr = 50;
    int player_speed = 20;
    player.draw_size = 10;
    while(1){
        clsd(frame);
        update_mouse(frame,screen_buff);
        //update_entity_pos_kbd(&player); 
        update_kbd();
        player.pos.y -= player_speed*keyboard.state[KEY_W];
        player.pos.y += player_speed*keyboard.state[KEY_S];
        player.pos.x -= player_speed*keyboard.state[KEY_A];
        player.pos.x += player_speed*keyboard.state[KEY_D];
        if (keyboard.state[KEY_SPACE]) clsd(frame);
        bound_check(&player);
        draw_entity(frame, player, white); 
        draw(frame,screen_buff);
        force_update(); 
    }
} 