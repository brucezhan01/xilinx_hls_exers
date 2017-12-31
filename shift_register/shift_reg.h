#pragma once
#include <iostream>
#include <assert.h>

/* Refer to Xilinx ap_shift_reg.h */
template<typename T, unsigned int depth=1>
class shift_reg_1d {
    T regs[depth];
public:
    shift_reg_1d() {}
    
    ~shift_reg_1d() {}

    void shift(T data_in, T *data_out, bool enable=true) {
        *data_out = regs[depth-1];
        if (enable) {
            for (int i = depth-1; i > 0; --i) {
#pragma HLS unroll
                regs[i] = regs[i-1];
            }
            regs[0] = data_in;
        }
    }

    void read(T *data_out, unsigned int addr=depth-1) {
        assert(addr<depth);
        *data_out = regs[addr];
    }
};

template<typename T, unsigned int rows=1, unsigned int cols=1, unsigned int len=1, bool shift_hori=true>
class shift_reg_2d {
    T regs[rows][cols];
public:
    shift_reg_2d() {}
    
    ~shift_reg_2d() {}

    void shift(T const vec_in[len], T vec_out[len], bool enable=true) {
//#pragma HLS inline self
        if (shift_hori) {
            assert(len == rows);
            for (int r = 0; r < rows;  ++r) {
#pragma HLS unroll
                vec_out[r] = regs[r][cols-1];
#ifndef synthesis
                //std::cout << vec_out[r] << " ";
#endif
            }
#ifndef synthesis
            //std::cout << std::endl;
#endif

            if (enable) {
                for (int r = 0; r < rows;  ++r) {
#pragma HLS unroll
                    for (int c = cols-1; c > 0; --c) {
#pragma HLS unroll
                        regs[r][c] = regs[r][c-1];
                    }
                    regs[r][0] = vec_in[r];
#ifndef synthesis
                    //std::cout << vec_in[r] << " ";
#endif
                }
#ifndef synthesis
                //std::cout << std::endl;
#endif
            }
        } else {
            assert(len == cols);
            for (int c = 0; c < cols; ++c) {
#pragma HLS unroll
                vec_out[c] = regs[rows-1][c];
            }
            if (enable) {
                for (int c = 0; c < cols; ++c) {
#pragma HLS unroll
                    for (int r = rows-1; r > 0; --r) {
#pragma HLS unroll
                        regs[r][c] = regs[r-1][c];
                    }
                    regs[0][c] = vec_in[c];
                }
            }
        }
    }

    void read(T vec_out[len], unsigned int addr) {
        if (shift_hori) {
            assert(addr < cols);
            for (int r = 0; r < rows; ++r) {
#pragma HLS unroll
                vec_out[r] = regs[r][addr];
            }
        } else {
            assert(addr < rows);
            for (int c = 0; c < cols; ++c) {
#pragma HLS unroll
                vec_out[c] = regs[addr][c];
            }
        }
    }
};
