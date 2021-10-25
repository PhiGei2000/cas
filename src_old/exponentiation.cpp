#include "math/expressions/exponentiation.hpp"

#include <math.h>

template<typename T>
T mathPow(T a, T b) {
    return pow(a, b);
}

namespace cas::math {
    double Exponentiation::getValue() const {
        return mathPow(left->getValue(), right->getValue());
    }

    ExpressionType Exponentiation::getType() const {
        return ExpressionType::Exponentiation;
    }

    std::string Exponentiation::toString() const {
        return left->toString() + " ^ " + right->toString();
    }
} // namespace cas::math
