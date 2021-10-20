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

    auto s1 = (c1 + v1)->multiply(v2 + c2);

    Term* t1 = Simplifier::convertToTerm(s1);
    std::cout << t1->toString() << std::endl;

    if (t1->hasSubterms()) {
        reinterpret_cast<OperationTerm*>(t1)->simplify();
    }

    std::cout << t1->toString() << std::endl;

    delete s1;

    return 0;
}
