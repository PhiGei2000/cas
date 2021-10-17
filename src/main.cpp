#include <iostream>

#include "math/expressions.hpp"
#include "math/expressions/simplifier.hpp"

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

    auto s1 = (c1 * v1)->add(&v2);
    auto s2 = (v2 * c1)->add(&v1);

    Term* t1 = Simplifier::convertToTerm(s1);
    std::cout << t1->toString() << std::endl;

    Term* t2 = Simplifier::convertToTerm(s2);
    std::cout << t2->toString() << std::endl;

    std::cout << "t1 == t2 ? " << t1->equals(t2) << std::endl;

    delete s1;

    return 0;
}
