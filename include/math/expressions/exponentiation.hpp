#pragma once

#include "binaryExpression.hpp"

namespace cas::math {

    struct Exponentiation : public BinaryExpression {
      public:
        Exponentiation(const Expression& left, const Expression& right);

        virtual double getValue() const override;
        virtual Expression* copy() const override;
        virtual ExpressionType getType() const override;        

        virtual std::string toString() const override;
    };

} // namespace cas::math
