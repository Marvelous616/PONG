#include "entity.h"

entity init_entity_static(point starting_pos){
    entity out;
    out.pos = starting_pos;
    out.velocity = out.acceleration = out.acceleration = mkpoint(0,0);
    out.mass = 0;
    out.draw_size = 50;
    out.s = SQUARE;
    out.sp = NULL;
    return out;
}