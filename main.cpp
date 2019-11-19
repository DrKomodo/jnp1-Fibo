#include <iostream>
#include "fibo.h"

int main() {

    Fibo f("0010101011");
    Fibo f0(0);
    Fibo f1(1);
    Fibo f2(100);
    f0 += f1;
    f0.print();
    f.print();
    Fibo asd;
    asd.print();

    return 0;
}
