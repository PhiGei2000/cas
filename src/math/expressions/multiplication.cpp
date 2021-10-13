#include "math/expressions/multiplication.hpp"

namespace cas::math {
    Multiplication::Multiplication(const Expression& left, const Expression& right)
        : BinaryExpression(left, right) {
    }

    double Multiplication::getValue() const {
        return left->getValue() * right->getValue();
    }

    Expression* Multiplication::copy() const {
        return new Multiplication(*this);
    }

    ExpressionType Multiplication::getType() const {
        return ExpressionType::Multiplication;
    }

    std::string Multiplication::toString() const {
        return left->toString() + " * " + right->toString();
    }
} // namespace cas::math