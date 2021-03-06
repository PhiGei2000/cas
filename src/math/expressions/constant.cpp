#include "math/expressions/constant.hpp"

namespace cas::math {
    Constant::Constant(double value)
        : value(value) {
    }

    double Constant::getValue() const {
        return value;
    }

    Expression* Constant::copy() const {
        return new Constant(*this);
    }

    ExpressionType Constant::getType() const {
        return ExpressionType::Constant;
    }

    bool Constant::dependsOn(const Variable& var) const {
        return false;
    }

    std::string Constant::toString() const {
        return std::to_string(value);
    }

} // namespace cas::math