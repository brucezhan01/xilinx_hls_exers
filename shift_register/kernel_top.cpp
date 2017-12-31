#include "kernel_top.h"

void kernel_top(vec_type const &vec_in, vec_type &vec_out) {
#pragma HLS data_pack variable=vec_in
#pragma HLS data_pack variable=vec_out
#pragma HLS interface ap_fifo port=vec_in
#pragma HLS interface ap_fifo port=vec_out
    static shift_reg_2d<short, rows, cols, rows, false> array_2d;
    array_2d.shift(vec_in.data,vec_out.data);
}
