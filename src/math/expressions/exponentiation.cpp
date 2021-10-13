#include "math/expressions/exponentiation.hpp"

#include <math.h>

namespace cas::math {
    Exponentiation::Exponentiation(const Expression& left, const Expression& right)
        : BinaryExpression(left, right) {
    }

    double Exponentiation::getValue() const {
        return pow(left->getValue(), right->getValue());
    }

    Expression* Exponentiation::copy() const {
        return new Exponentiation(*this);
    }

    ExpressionType Exponentiation::getType() const {
        return ExpressionType::Exponentiation;
    }

    std::string Exponentiation::toString() const {
        return left->toString() + " ^ " + right->toString();
    }
} // namespace cas::math
