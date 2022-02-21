#include <iostream>

#include "expressionParser.hpp"

using namespace cas;
using namespace cas::math;

int main(int argCnt, char** args) {

    Term* expr = ExpressionParser::parseExpression("5+2+5*10");

    std::cout << expr->toString() << std::endl;

    Term* simple = expr->simplify();

    std::cout << simple->toString() << std::endl;

    return 0;
}
