#include "math/expressions/addition.hpp"

namespace cas::math {
    
    Addition::Addition(const Expression& left, const Expression& right)
        : BinaryExpression(left, right) {
    }

    double Addition::getValue() const {
        return left->getValue() + right->getValue();
    }

    Expression* Addition::copy() const {
        return new Addition(*this);
    }

    ExpressionType Addition::getType() const {
        return ExpressionType::Addition;
    }

    std::string Addition::toString() const {
        return left->toString() + " + " + right->toString();
    }

} // namespace cas::math