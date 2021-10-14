#include "math/expressions/exponentiation.hpp"

#include <math.h>

namespace cas::math {
    double Exponentiation::getValue() const {
        return pow(left->getValue(), right->getValue());
    }

    ExpressionType Exponentiation::getType() const {
        return ExpressionType::Exponentiation;
    }

    std::string Exponentiation::toString() const {
        return left->toString() + " ^ " + right->toString();
    }
} // namespace cas::math
