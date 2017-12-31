#include <iostream>
#include "kernel_top.h"

int main() {
    vec_type vec_in, vec_out;
    for (int i = 0; i < len; ++i) {
        vec_in.data[i] = i;
        vec_out.data[i] = 0;
    }
    for (int i = 0; i < cols+1; ++i)  {
        kernel_top(vec_in, vec_out);
        for (int j = 0; j < len; ++j) {
            std::cout << vec_out.data[j] << "  ";
        }
        std::cout << std::endl;
    }
    return 0;
}
