#include "math/expressions/binaryExpression.hpp"

#include "math/term.hpp"

namespace cas::math
{

bool BinaryExpression::dependsOn(const Variable& var) const {
    return left->dependsOn(var) || right->dependsOn(var);
}

} // namespace cas::math