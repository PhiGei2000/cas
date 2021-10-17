#include "math/expressions/constantTerm.hpp"

#include "math/expressions/expression.hpp"

#include <sstream>

namespace cas::math {
    ConstantTerm::ConstantTerm(double value)
        : value(value), Term(ExpressionType::Constant) {
    }

    bool ConstantTerm::equals(Term* other) const {
        if (other->type == ExpressionType::Constant) {
            ConstantTerm* c = reinterpret_cast<ConstantTerm*>(other);

            return c->value == this->value;
        }

        return false;
    }

    std::string ConstantTerm::toString() const {
        std::stringstream ss;
        ss << value;

        return ss.str();
    }
} // namespace cas::math
