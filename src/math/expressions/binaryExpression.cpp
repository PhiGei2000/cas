#include "math/expressions/binaryExpression.hpp"

namespace cas::math
{

BinaryExpression::~BinaryExpression() {
    delete left;
    delete right;
}

bool BinaryExpression::dependsOn(const Variable& var) const {
    return left->dependsOn(var) || right->dependsOn(var);
}

} // namespace cas::math