#include "math/expressions/constant.hpp"

#include <sstream>

namespace cas::math {
    Constant::Constant(double value)
        : value(value), Term(ExpressionType::Constant) {
    }

    bool Constant::equals(Term* other) const {
        if (other->type == ExpressionType::Constant) {
            Constant* c = reinterpret_cast<Constant*>(other);

            return c->value == this->value;
        }

        return false;
    }

    Term* Constant::copy() const {
        return new Constant(value);
    }

    std::string Constant::toString() const {
        std::stringstream ss;
        ss << value;

        return ss.str();
    }
} // namespace cas::math
