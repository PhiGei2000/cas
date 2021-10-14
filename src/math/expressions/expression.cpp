#include "math/expressions/expression.hpp"

#include "math/expressions/variable.hpp"

namespace cas::math {

    const ExpressionId Expression::getId() const {
        return id;
    }

} // namespace cas::math