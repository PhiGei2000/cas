#include "math/expressions/variableTerm.hpp"

namespace cas::math {

    VariableTerm::VariableTerm(char character)
        : character(character), Term(ExpressionType::Variable) {
    }

    char VariableTerm::getCharacter() const {
        return character;
    }

    bool VariableTerm::equals(Term* other) const {
        if (other->type == this->type) {
            VariableTerm* var = reinterpret_cast<VariableTerm*>(other);

            return var->character == this->character;
        }

        return false;
    }

    Term* VariableTerm::copy() const {
        return new VariableTerm(character);
    }

    std::string VariableTerm::toString() const {
        std::string result;

        result.push_back(character);
        return result;
    }

} // namespace cas::math
