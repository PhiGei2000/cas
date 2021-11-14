#include "math/expressions/variable.hpp"

namespace cas::math {

    Variable::Variable(char character)
        : character(character), Term(ExpressionType::Variable) {
    }

    char Variable::getCharacter() const {
        return character;
    }

    bool Variable::equals(Term* other) const {
        if (other->type == this->type) {
            Variable* var = reinterpret_cast<Variable*>(other);

            return var->character == this->character;
        }

        return false;
    }

    Term* Variable::copy() const {
        return new Variable(character);
    }

    std::string Variable::toString() const {
        std::string result;

        result.push_back(character);
        return result;
    }

} // namespace cas::math
