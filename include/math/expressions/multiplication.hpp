#pragma once

#include "math/expressions/binaryExpression.hpp"

namespace cas::math {

    struct Multiplication : public BinaryExpression {
      public:
        Multiplication(const Expression& left, const Expression& right);

        virtual double getValue() const override;
        virtual Expression* copy() const override;
        virtual ExpressionType getType() const override;        

        virtual std::string toString() const override;
    };

} // namespace cas::math