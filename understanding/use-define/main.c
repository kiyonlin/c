#include <stdio.h>
#define XNAME(n) x##n
#define PRINT_XN(n) printf("x" #n "=%d\n", x##n)

void glue() {
    int XNAME(1) = 14;
    int XNAME(2) = 20;
    int x3 = 30;

    PRINT_XN(1);
    PRINT_XN(2);
    PRINT_XN(3);
}

#include <math.h>
#define PR(X,...) printf("Message " #X ":" __VA_ARGS__)
void variadic() {
    double x = 48;
    double y;
    y = sqrt(x);
    PR(1, "x=%g\n", x);
    PR(2, "x=%.2f, y=%.4f\n", x, y);
}

int main() {
    glue();
    
    variadic();

    return 0;
}