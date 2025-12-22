#include <fcntl.h>
#include <stdint.h>
#include "config.h"
#include "inp_event.h"
#include <linux/fb.h>
#include <stdio.h>
#include <sys/mman.h>
#include "base_masks.h"
#include <unistd.h>
#include "num.h"
#include <math.h>
#include "sprite.h"

static struct fb_var_screeninfo vinfo;
static struct fb_fix_screeninfo finfo;
extern int screen_fd;

typedef struct rect{
    int width;
    int height;
    int x;
    int y;
}rect;

typedef struct state{
    int ball_x;
    int ball_y;
    int ball_vel_x;
    int ball_vel_y;
    int paddle_a_x;
    int paddle_a_y;
    int paddle_b_x;
    int paddle_b_y;
}state;

typedef struct score{
    int a;
    int b;
}score;
static score sc;
static state st;
static fb* frame;

// int square(int i){
//     return i*i;
// }

void draw_ball(fb* frame){
    for (int i = -BALL_RADIUS;i<BALL_RADIUS;i++){
        for (int j = -BALL_RADIUS;j<BALL_RADIUS;j++){
            if (square(i)+square(j)<square(BALL_RADIUS)) *(frame->arr + (st.ball_y + j)*SCR_X + st.ball_x + i) ^= 0x00ffffff;
        }
    }
}

void reset_ball(){
    st.ball_x = SCR_X/2;
    st.ball_y = SCR_Y/2;
    st.ball_vel_x = BALL_VEL*(sc.a>sc.b?1:-1);
    st.ball_vel_y = BALL_VEL;
    //clsd(frame);
    //draw_ball(frame);
    //usleep(500000);
}

void init_state(){
    reset_ball();
    st.paddle_a_x = PADDLE_WIDTH;
    st.paddle_a_y = SCR_Y/2;
    st.paddle_b_x = SCR_X - PADDLE_WIDTH;
    st.paddle_b_y = SCR_Y/2;
    sc.a = 0;
    sc.b = 0;
}

void bound_collision(){
    if (st.ball_y > SCR_Y - BALL_RADIUS - BORDER_WIDTH) {
        st.ball_y = SCR_Y - BALL_RADIUS - BORDER_WIDTH;
        st.ball_vel_y *= -1;
    } else if (st.ball_y < BALL_RADIUS + BORDER_WIDTH) {
        st.ball_y = BALL_RADIUS + BORDER_WIDTH;
        st.ball_vel_y *= -1;
    }
    if (st.ball_x > SCR_X - PADDLE_WIDTH*2){
        sc.a++;
        reset_ball();
    }else if (st.ball_x < PADDLE_WIDTH*2) {
        sc.b++;
        reset_ball();
    }
}

void paddle_collision(){
    if (st.ball_x > SCR_X - PADDLE_WIDTH*2){
        if (st.ball_y < st.paddle_b_y + PADDLE_HEIGHT + BALL_RADIUS && st.ball_y > st.paddle_b_y - PADDLE_HEIGHT - BALL_RADIUS){
            st.ball_vel_x *=-1;
            st.ball_x = SCR_X - PADDLE_WIDTH*2;
        }
    }
    else if (st.ball_x < PADDLE_WIDTH*2){
        if (st.ball_y < st.paddle_a_y + PADDLE_HEIGHT + BALL_RADIUS && st.ball_y > st.paddle_a_y - PADDLE_HEIGHT - BALL_RADIUS){
            st.ball_vel_x *=-1;
            st.ball_x = PADDLE_WIDTH*2;
        }
    } 
}

void draw_paddle_a(fb* f){
    for (int i = -PADDLE_WIDTH; i < PADDLE_WIDTH; i++){
        for (int j = -PADDLE_HEIGHT; j < PADDLE_HEIGHT; j++){
            *(f->arr + (st.paddle_a_y + j)*SCR_X + st.paddle_a_x + i) = WHITE;
            //if (i < 5 && i > -5 && j > -5 && j < 5) *(f->arr + (st.paddle_a_y+j)*SCR_X + st.paddle_a_x + i) = RED;
        }
    }
}

void draw_paddle_b(fb* f){
    for (int i = -PADDLE_WIDTH; i < PADDLE_WIDTH; i++){
        for (int j = -PADDLE_HEIGHT; j < PADDLE_HEIGHT; j++){
            *(f->arr + (st.paddle_b_y+j)*SCR_X + st.paddle_b_x + i) = WHITE;
            //if (i < 5 && i > -5 && j > -5 && j < 5) *(f->arr + (st.paddle_b_y+j)*SCR_X + st.paddle_b_x + i) = GREEN;
        }
    }
}

void bind_paddles(){
    if (st.paddle_a_y > SCR_Y - PADDLE_HEIGHT - BORDER_WIDTH) st.paddle_a_y = SCR_Y - PADDLE_HEIGHT - BORDER_WIDTH;
    if (st.paddle_a_y < PADDLE_HEIGHT + BORDER_WIDTH) st.paddle_a_y = PADDLE_HEIGHT + BORDER_WIDTH;
    if (st.paddle_b_y > SCR_Y - PADDLE_HEIGHT - BORDER_WIDTH) st.paddle_b_y = SCR_Y - PADDLE_HEIGHT - BORDER_WIDTH;
    if (st.paddle_b_y < PADDLE_HEIGHT + BORDER_WIDTH) st.paddle_b_y = PADDLE_HEIGHT + BORDER_WIDTH;
}
#define PADDLE_SPEED 10

void move_paddles(){
    st.paddle_a_y-=PADDLE_SPEED*keyboard.state[KEY_W];
    st.paddle_a_y+=PADDLE_SPEED*keyboard.state[KEY_S];
    st.paddle_b_y-=PADDLE_SPEED*keyboard.state[KEY_I];
    st.paddle_b_y+=PADDLE_SPEED*keyboard.state[KEY_K];
}

void force_update(){
    vinfo.activate = FB_ACTIVATE_NOW;
    ioctl(screen_fd, FBIOPAN_DISPLAY, &vinfo); 
}

void draw_px(int x,int y,fb* frame){
    *(frame->arr + SCR_X*y + x) = WHITE;
}


void draw_bounds(fb* frame){
    for (int i=0;i<SCR_X;i++){
        for (int j=0;j<BORDER_WIDTH;j++){
            *(frame->arr + j*SCR_X + i) = WHITE;
        }
    }
    for (int i=0;i<SCR_X;i++){
        for (int j=SCR_Y - BORDER_WIDTH;j<SCR_Y;j++){
            *(frame->arr + j*SCR_X + i) = WHITE;
        }
    }
}
// static int paddle_a_mem[5]={0};
// enum ball_mapping{
//     ball_prev_x,
//     ball_prev_y,
//     ball_curr_x,
//     ball_curr_y,
//     ball_hit_estimate
// };

float sigmoid(float low,float high,float x){
    return low + (high-low)/(1+exp(-x*1000));
}
// #define PADDLE_MAX_VEL 3
// void paddle_a_ai(){
//     paddle_a_mem[ball_prev_x] = paddle_a_mem[ball_curr_x];
//     paddle_a_mem[ball_prev_y] = paddle_a_mem[ball_curr_y];
//     paddle_a_mem[ball_curr_x] = st.ball_x;
//     paddle_a_mem[ball_curr_y] = st.ball_y;
//     int dy = paddle_a_mem[ball_curr_y] - paddle_a_mem[ball_prev_y];
//     int dx = paddle_a_mem[ball_curr_x]-paddle_a_mem[ball_prev_x];
//     paddle_a_mem[ball_hit_estimate] = paddle_a_mem[ball_curr_y] + (dy*/dx;
//     st.paddle_a_y -= PADDLE_MAX_VEL*sigmoid(PADDLE_WIDTH*2,SCR_X - PADDLE_WIDTH*2,paddle_a_mem[ball_hit_estimate] - st.paddle_a_y);
// }

void paddle_a_ai(){
    //st.paddle_a_y += (st.ball_y-st.paddle_a_y)*sigmoid(SCR_X-2*PADDLE_WIDTH,2*PADDLE_WIDTH,(float)st.ball_x/SCR_X)/SCR_Y;
    st.paddle_a_y = st.ball_y;
}

void paddle_b_ai(){
    st.paddle_b_y = st.ball_y;
}

void draw_net(fb* frame){
    for (int i=0;i<SCR_Y;i++){
        *(frame->arr + i*SCR_X + SCR_X/2) = WHITE;
    }
}

extern Mouse mouse;
extern Keyboard keyboard;

void draw_img(char* img,fb* frame,int x,int y,point dim){
    for (int i=0;i<dim.x;i++){
        for (int j=0;j<dim.y;j++){
            if ((x+i<2560)&&(x+i>=0)&&(y+j>=0)&&(y+j<1600)) *(frame->arr + x + i + (y + j) * SCR_X) = *(img + i + j*dim.x) == 0x01 ? WHITE:BLACK;
        }
    }
}

int main(){
    point dim;
    dim.x = SCR_X;
    dim.y = SCR_Y;
    frame = init_framebuffer(dim);
    init_screen();
    init_state();
    ioctl(screen_fd, FBIOGET_VSCREENINFO, &vinfo);
    ioctl(screen_fd, FBIOGET_FSCREENINFO, &finfo);
    uint32_t* screen_buff = (uint32_t*)mmap( 0, finfo.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, screen_fd, 0);
    
    init_mouse();
    init_kbd();

    point centre = mkpoint(SCR_X/2,SCR_Y/2);
    pixel alpha = mkpixel(ALPHA);
    pixel red = mkpixel(RED);
    pixel white = mkpixel(WHITE);
    init_kbd();
    int x,y;
    FILE *logfile = fopen("./game_log.csv", "w");
    clsd(frame);
    //sc.a = sc.b = 123456;
    fprintf(logfile, "ball_x, ball_y, ball_vel_x, ball_vel_y, paddle_a_x, paddle_a_y, paddle_b_x, paddle_b_y,sigmoid\n");
    // FILE* f = fopen("/home/levi/test/PONG/624x1196_hand_dithered.data","rb");
    // sprite* hand = load_sprite_headless(624, 1196, f);
    // while(1){
    //     clsd(frame);
    //     draw_sprite(0, 0, hand, frame);
    //     draw(frame,screen_buff);
    //     force_update();
    // }
    //opening image
    int img_x = 468;
    int img_y = 897;
    int img_fd = open("/home/levi/test/PONG_no_menu/468x897_hand_dithered_1_bit.data",O_RDONLY); 
    char* img = mmap(NULL,img_x*img_y,PROT_READ,MAP_PRIVATE,img_fd,0);
    // ----------- menu ---------------
    point title = mkpoint(200,200);
    point title_dim = mkpoint(100,100);
    
    font title_font = { 200, 140,50};

    font score_font = {100,70,25};
    
    font menu_item_font = {50, 35, 5};

    point menu_pos = {200,800};
//     while (1){
//         clsd(frame);
//         draw_P(title.x,title.y,frame,title_font);
//         draw_O(title.x + (title_fw + title_weight),title.y, frame,title_font);
//         draw_N( title.x + 2*(title_fw + title_weight), title.y, frame,title_font);
//         draw_G( title.x + 3*(title_fw + title_weight), title.y, frame,title_font);
//
//         draw_img(img, frame,SCR_X/2 + 500,SCR_Y - img_y + 150,mkpoint(img_x,img_y));
//
//         draw_S(menu_pos.x, menu_pos.y, frame,menu_item_font);
//         draw_T(menu_pos.x + 1*(menu_item_font.width + menu_item_font.weight),menu_pos.y,frame,menu_item_font);
//         draw_A(menu_pos.x + 2*(menu_item_font.width + menu_item_font.weight),menu_pos.y,frame,menu_item_font);
//         draw_R(menu_pos.x + 3*(menu_item_font.width + menu_item_font.weight),menu_pos.y,frame,menu_item_font);
//         draw_T(menu_pos.x + 4*(menu_item_font.width + menu_item_font.weight),menu_pos.y,frame,menu_item_font);
//
//         draw(frame,screen_buff);
//         force_update();
//     }
    // ----------- game - loop ----------
    while(1){
        clsd(frame);
        draw_bounds(frame);
        draw_net(frame);
        update_kbd();
        move_paddles();
        //paddle_a_ai();
        //paddle_b_ai();
        fprintf(logfile, "%d,%d,%d,%d,%d,%d,%d,%d,%f\n",st.ball_x,st.ball_y,st.ball_vel_x,st.ball_vel_y,st.paddle_a_x,st.paddle_a_y,st.paddle_b_x,st.paddle_b_y,1/*sigmoid(SCR_X-2*PADDLE_WIDTH,2*PADDLE_WIDTH,st.ball_x)*/);
        bind_paddles();
        paddle_collision();
        bound_collision();
        st.ball_x += st.ball_vel_x;
        st.ball_y += st.ball_vel_y;
        fprintf(logfile, "%d,%d,%d,%d,%d,%d,%d,%d,%f\n",st.ball_x,st.ball_y,st.ball_vel_x,st.ball_vel_y,st.paddle_a_x,st.paddle_a_y,st.paddle_b_x,st.paddle_b_y,1/*sigmoid(SCR_X-2*PADDLE_WIDTH,2*PADDLE_WIDTH,st.ball_x)*/);
        draw_px(PADDLE_WIDTH, 200, frame);
        draw_paddle_a(frame);
        draw_paddle_b(frame);
        draw_num_string_centered(SCR_X/4,BORDER_WIDTH + padding_y,sc.a,frame,score_font);
        draw_num_string_centered(SCR_X-SCR_X/4,BORDER_WIDTH + padding_y,sc.b,frame,score_font);
        draw_ball(frame);
        draw(frame,screen_buff);
        force_update();
        //usleep(16000);
        fflush(logfile);

        //clsd(frame);
    }
}
