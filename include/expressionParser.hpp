#pragma once
#include "math/expressions/terms.hpp"

#include <regex>

using namespace cas::math;

namespace cas {
    class ExpressionParser {
      private:
        struct OperatorToken {
            ExpressionType type;
            char operatorToken;
            char inverseOperatorToken;
        };

        static constexpr OperatorToken tokens[] = {
            OperatorToken{ExpressionType::Addition, '+', '-'},
            OperatorToken{ExpressionType::Multiplication, '*', '/'},
            OperatorToken{ExpressionType::Exponentiation, '^', '\0'}

        };

        static std::regex constantRegex;
        static std::regex variableRegex;

        static Term* parseAddition(const std::string& str);
        static Term* parseMultiplication(const std::string& str);
        static Term* parseExponentiation(const std::string& str);

        static Constant* parseConstant(const std::string& str);
        static Variable* parseVariable(const std::string& str);

        static std::size_t findToken(const std::string& str, const OperatorToken& token, char* result, std::size_t start = 0);

      public:
        static Term* parseExpression(const std::string& str);
    };
} // namespace cas
