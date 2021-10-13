#include "math/expressions/expression.hpp"

#include "math/expressions/variable.hpp"

namespace cas::math
{

Expression* Expression::simplify() {
    return this;
}

} // namespace cas::math