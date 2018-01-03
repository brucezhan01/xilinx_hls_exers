#pragma once

#include <hls_half.h>

#define PARALLEL_NUM       8

typedef short data_t;
struct lane_t {
    data_t val[PARALLEL_NUM];
};
void kernel_top(lane_t const *vec_a, lane_t const *vec_b, int length, data_t *sum);
