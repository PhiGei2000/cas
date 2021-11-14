#pragma once

#include "math/expressions/terms.hpp"

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

        static Addition* parseAddition(const std::string& str);
        static Multiplication* parseMultiplication(const std::string& str);
        static Exponentiation* parseExponentiation(const std::string& str);

        static Constant* parseConstant(const std::string& str);
        static Variable* parseVariable(const std::string& str);

        static Term* parseBrackets(const std::string& str);

      public:
        static Term* parseExpression(const std::string& str);
    };
} // namespace cas
