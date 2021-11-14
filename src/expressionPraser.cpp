#include "expressionParser.hpp"

namespace cas {
    Addition* ExpressionParser::parseAddition(const std::string& str) {
    }

    Exponentiation* ExpressionParser::parseExponentiation(const std::string& str){
        str.
    }

    Constant* ExpressionParser::parseConstant(const std::string& str) {
        double value = std::stod(str);

        return new Constant(value);
    }

    Variable* ExpressionParser::parseVariable(const std::string& str) {
        char character = str[0];

        return new Variable(character);
    }
} // namespace cas