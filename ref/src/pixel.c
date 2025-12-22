#include "pixel.h"

pixel mkpixel(uint32_t col){
    pixel out;
    out.val = col;
    return out;
}