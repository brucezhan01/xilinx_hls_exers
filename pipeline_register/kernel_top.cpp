#include "make_register.h"

void kernel_top(int val_i, int *val_o) {
    *val_o = make_reg<int,3>(val_i);
}
