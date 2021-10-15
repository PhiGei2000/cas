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

    bool Addition::equals(Expression* other) const {
        if (other->getType() == ExpressionType::Addition) {
            Addition* addition = reinterpret_cast<Addition*>(other);

            return left->equals(addition->left) && right->equals(addition->right)
                       ? true
                       : right->equals(addition->left) && left->equals(addition->right);
        }

        return false;
    }

} // namespace cas::math