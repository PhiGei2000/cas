#include "expressionParser.hpp"

namespace cas {
    std::regex ExpressionParser::constantRegex = std::regex("\\d+(\\.\\d+)?");
    std::regex ExpressionParser::variableRegex = std::regex("[a-zA-Z]{1}");

    Term* ExpressionParser::parseAddition(const std::string& str) {
        const OperatorToken& token = tokens[static_cast<int>(ExpressionType::Addition)];

        char tokenCharacter;
        std::size_t position = findToken(str, token, &tokenCharacter);

        if (position != std::string::npos) {
            const std::string& first = str.substr(0, position);
            const std::string& last = str.substr(position + 1);

            Term* firstSummand = parseMultiplication(first);
            Term* rest = parseAddition(last);

            if (tokenCharacter == token.operatorToken) {
                return new Addition({firstSummand, rest});
            }
            else {
                return new Addition({firstSummand, new Multiplication({new Constant(-1), rest})});
            }
        }
        else {
            return parseMultiplication(str);
        }
    }

    Term* ExpressionParser::parseMultiplication(const std::string& str) {
        const OperatorToken& token = tokens[static_cast<int>(ExpressionType::Multiplication)];

        char tokenCharacter;
        std::size_t position = findToken(str, token, &tokenCharacter);

        if (position != std::string::npos) {
            const std::string& first = str.substr(0, position);
            const std::string& last = str.substr(position + 1);

            Term* firstFactor = parseExponentiation(first);
            Term* rest = parseMultiplication(last);

            if (tokenCharacter == token.operatorToken) {
                return new Multiplication({firstFactor, rest});
            }
            else {
                return new Multiplication({firstFactor, new Exponentiation({new Constant(-1), rest})});
            }
        }
        else {
            return parseExponentiation(str);
        }
    }

    Term* ExpressionParser::parseExponentiation(const std::string& str) {
        const OperatorToken& token = tokens[static_cast<int>(ExpressionType::Exponentiation)];

        char tokenCharacter;
        std::size_t position = findToken(str, token, &tokenCharacter);

        if (position != std::string::npos) {
            const std::string& first = str.substr(0, position);
            const std::string& last = str.substr(position + 1);

            Term* base = parseExpression(first);
            Term* exponent = parseExponentiation(last);

            // no inverse operator
            // if (tokenCharacter == token.operatorToken) {
            return new Exponentiation({base, exponent});
            // }
        }
        else {
            return parseExpression(str);
        }
    }

    Constant* ExpressionParser::parseConstant(const std::string& str) {
        double value = std::stod(str);

        return new Constant(value);
    }

    Variable* ExpressionParser::parseVariable(const std::string& str) {
        char character = str[0];

        return new Variable(character);
    }

    Term* ExpressionParser::parseExpression(const std::string& str) {
        if (str.front() == '(' && str.back() == ')') {
            return parseExpression(str.substr(1, str.size() - 2));
        }
        else if (std::regex_match(str, constantRegex)) {
            return parseConstant(str);
        }
        else if (std::regex_match(str, variableRegex)) {
            return parseVariable(str);
        }
        else {
            return parseAddition(str);
        }
    }

    std::size_t ExpressionParser::findToken(const std::string& str, const OperatorToken& token, char* result, std::size_t start) {
        std::size_t position = std::string::npos;

        size_t i = start;
        int bracketCounter = 0;

        while (position == std::string::npos && i < str.size()) {
            const char ch = str[i];

            if (ch == '(')
                ++bracketCounter;
            else if (ch == ')')
                --bracketCounter;
            else if (ch == token.operatorToken || ch == token.inverseOperatorToken) {
                if (bracketCounter == 0) {
                    position = i;
                    *result = ch;
                }
            }

            ++i;
        }

        return position;
    }
} // namespace cas