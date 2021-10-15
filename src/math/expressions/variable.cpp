#include "math/expressions/variable.hpp"

#include <stdexcept>

namespace cas::math {

    Variable::Variable(char character)
        : character(character) {
    }

    char Variable::getCharacter() const {
        return character;
    }

    bool Variable::dependsOn(const Variable& var) const {
        return character == var.character;
    }

    double Variable::getValue() const {
        throw std::runtime_error("Cannot get value of a variable");
    }

    ExpressionType Variable::getType() const {
        return ExpressionType::Variable;
    }

    std::string Variable::toString() const {
        return std::string(1, character);
    }

    bool Variable::equals(Expression* expr) const {
        if (expr->getType() == ExpressionType::Variable) {
        Variable* var = reinterpret_cast<Variable*>(expr);
            
            return var->character == character;
        }

        return false;
    }

    bool Variable::hasValue() const {
        return false;
    }

} // namespace cas::math