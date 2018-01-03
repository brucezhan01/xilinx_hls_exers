#include "kernel_top.hpp"

void kernel_top(lane_t const vec_a[], lane_t const vec_b[], int length, data_t *sum) {
//#pragma HLS dataflow
#pragma HLS expression_balance
#pragma HLS data_pack variable=vec_a instance=vec_a
#pragma HLS data_pack variable=vec_b instance=vec_b
#pragma HLS INTERFACE ap_bus depth=64 port=vec_b
#pragma HLS INTERFACE ap_bus depth=64 port=vec_a

    data_t acc = 0;
    outer_loop: for (int i = 0; i < length; ++i) {
#pragma HLS pipeline
    	inner_loop: for (int j = 0; j < PARALLEL_NUM; ++j) {
            acc += vec_a[i].val[j] * vec_b[i].val[j];
        }
    }
    *sum = acc;
}
