#include <iostream>

#include "tmatrix.h"
#include "tvector.h"
int main() {
    using real = long double;
    using Vector = TVector<real>;
    using Matrix = TMatrix<real>;
    Vector vec(10), vec2(10);

    vec(3) = 4;
    vec(5) = 1;
    vec2(3) = 8;
    vec2(5) = 2;
    vec = vec * (vec2 * vec);
    std::cout << vec << vec.norm2() << std::endl;

    Matrix mat(5, 5);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            mat(i, j) = i + j;
        }
    }
    Matrix mat2 = mat;
    mat2 += mat;
    mat2 -= mat;
    mat2 *= 2;

    std::cout << mat2 << std::endl;

    std::cout << mat << std::endl;

    mat2 *= mat;

    std::cout << mat2 << std::endl;

    mat2 = mat + mat2;
    std::cout << mat2 << std::endl;

    Matrix mat3(5, 5);
    Vector vec3(5);
    for (size_t i = 0; i < 5; i++) {
        mat3(i, i) = 1;
        vec3(i) = 1;
    }
    mat2 *= mat3;
    std::cout << mat2 << std::endl;
    std::cout << vec3 * mat2 << std::endl;
    std::cout << vec3 * mat2 * vec3 << std::endl;

    return 0;
}