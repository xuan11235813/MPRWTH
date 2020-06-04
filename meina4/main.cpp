#include <iostream>

#include "tvector.h"
int main() {
    using real = long double;
    using Vector = TVector<real>;

    Vector vec(10), vec2(10);

    vec(3) = 4;
    vec(5) = 1;
    vec2(3) = 8;
    vec2(5) = 2;
    vec = vec * (vec2 * vec);
    std::cout << vec << vec.norm2() << std::endl;

    return 0;
}