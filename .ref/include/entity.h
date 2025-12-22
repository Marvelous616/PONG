#pragma once
#include "point.h"
#include "sprite.h"

typedef enum default_shapes{
    SQUARE,RECT,CIRCLE
}default_shape;

typedef struct obj{
    point pos;
    point velocity;
    point acceleration;
    int mass;
    default_shape s;
    int draw_size;
    sprite* sp;
}entity;

entity init_entity_static(point starting_pos);

typedef struct entity_node{
    struct entity_node* prev;
    entity* val;
    struct entity_node* next;
}entity_node;

typedef struct entity_index{
    entity_node* list;
    int size;
}entity_index;