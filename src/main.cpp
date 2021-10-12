#include <iostream>

#include "math/expressions.hpp"

using namespace cas::math;

int main(int argCnt, char** args) {
    Constant c1 = 5.0;
    Constant c2 = 5;
    Variable v1 = 'x';

    auto result = c1 * c2 + v1;

    std::cout << result.toString() << " = " << result.getValue() << std::endl;
}

