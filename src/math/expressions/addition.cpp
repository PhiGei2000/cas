#include "math/expressions/addition.hpp"

namespace cas::math {

    double Addition::getValue() const {
        return left->getValue() + right->getValue();
    }

    ExpressionType Addition::getType() const {
        return ExpressionType::Addition;
    }

    std::string Addition::toString() const {
        return left->toString() + " + " + right->toString();
    }

} // namespace cas::math