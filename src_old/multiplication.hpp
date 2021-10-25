#pragma once

#include "math/expressions/binaryExpression.hpp"

namespace cas::math {

    struct Multiplication : public BinaryExpression {
      public:
        virtual double getValue() const override;

        virtual ExpressionType getType() const override;

        virtual std::string toString() const override;
    };

} // namespace cas::math