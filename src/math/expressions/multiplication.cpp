#include "math/expressions/multiplication.hpp"

namespace cas::math {
    double Multiplication::getValue() const {
        return left->getValue() * right->getValue();
    }

    ExpressionType Multiplication::getType() const {
        return ExpressionType::Multiplication;
    }

    std::string Multiplication::toString() const {
        return left->toString() + " * " + right->toString();
    }
} // namespace cas::math