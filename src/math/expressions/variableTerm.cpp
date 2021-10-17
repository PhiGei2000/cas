#include "math/expressions/variableTerm.hpp"

#include "math/expressions/expression.hpp"

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

    std::string VariableTerm::toString() const {
        std::string result;

        result.push_back(character);
        return result;
    }

} // namespace cas::math
