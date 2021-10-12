#include <iostream>

#include "expressions/expression.hpp"

using namespace cas::expressions;

int main(int argCnt, char** args) {
    Constant c1 = 5.0;
    Constant c2 = 5;

    auto result = c1 * c2;

    std::cout << result->getValue() << std::endl;
}

