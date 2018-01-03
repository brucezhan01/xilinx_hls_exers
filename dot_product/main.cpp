#include <cmath>
#include "kernel_top.hpp"

#define N      8

#define EPSILON    1e-3

bool check(float a, float b) {
    float diff = a - b;
    return fabs(a-b) < EPSILON;
}

int main() {
    lane_t vec_a[N];
    lane_t vec_b[N];
    data_t sum = (data_t)0;

    data_t sum_ref = (data_t)0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < PARALLEL_NUM; ++j) {
            vec_a[i].val[j] = (i*N+j);
            vec_b[i].val[j] = (i*N+j);
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < PARALLEL_NUM; ++j) {
            sum_ref += (i*N+j) * (i*N+j);
        }
    }

    kernel_top(vec_a, vec_b, N, &sum);

    std::cout << "sum: " << sum << " | sum_ref: " << sum_ref << std::endl;

    if (check(sum, sum_ref)) {
        std::cout << "Success!" << std::endl;
        return 0;
    } else {
        std::cout << "Error!" << std::endl;
        return !0;
    }
}
