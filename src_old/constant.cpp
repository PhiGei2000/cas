#include "math/expressions/constant.hpp"

namespace cas::math {
    Constant::Constant(double value)
        : value(value) {
    }

    double Constant::getValue() const {
        return value;
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

    bool Constant::equals(Expression* expr) const {
        return expr->hasValue()
                   ? expr->getValue() == value
                   : false;        
    }

    bool Constant::hasValue() const {
        return true;
    }

} // namespace cas::math