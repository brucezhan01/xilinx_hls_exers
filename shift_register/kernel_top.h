#pragma once

#include "shift_reg.h"

#define rows    4
#define cols    4
#define len     4
struct vec_type {
    short data[len];
};

void kernel_top(vec_type const &vec_in, vec_type &vec_out);
