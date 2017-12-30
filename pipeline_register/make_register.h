#pragma once

#include <stdint.h>

template<typename T, uint8_t num_cycles>
T make_reg(T val) {
#pragma HLS pipeline
//#pragma HLS inline self off
#pragma HLS interface ap_ctrl_none register port=return
    if (num_cycles == 1)
        return val;
    else
        return make_reg<T, num_cycles-1>(val);
}

template<typename T>
T make_reg(T val) {
    return make_reg<T,1>(val);
}
