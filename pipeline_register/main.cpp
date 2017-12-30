#include <iostream>

#include "make_register.h"

extern void kernel_top(int val_i, int *val_o);
int main() {
    int val = 10;
    int res = 0;
    kernel_top(val, &res);
    std::cout << res << std::endl;
    return 0;
}
