#include <iostream>

#include "math/expressions.hpp"

using namespace cas::math;

void match(Expression* left, Expression* right) {
    std::cout << left->toString()
              << " = "
              << right->toString()
              << " ? "
              << (left->equals(right)
                      ? "true"
                      : "false")
              << std::endl;
}

int main(int argCnt, char** args) {

    Constant c1 = 10;
    Constant c2 = 50;
    Variable v1 = 'x';
    Variable v2 = 'y';

    std::cout << "c1: " << &c1 << std::endl;
    std::cout << "c2: " << &c2 << std::endl;
    std::cout << "v1: " << &v1 << std::endl;

    auto s1 = (c1 + v1)->add(&v2);
    auto s2 = (v2 + v1)->add(&c1);

    match(s1, s2);

    delete s1;
    delete s2;

    return 0;
}
