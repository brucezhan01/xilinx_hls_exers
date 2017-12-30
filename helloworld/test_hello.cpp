#include <iostream>

extern void hello_core(int a, int b, int *c);
int main() {
    int a = 3;
    int b = 3;
    int c;
    hello_core(a,b,&c);
    std::cout << c << std::endl;
}
