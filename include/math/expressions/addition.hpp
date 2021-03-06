#pragma once

#include "binaryExpression.hpp"

namespace cas::math {

    struct Addition : public BinaryExpression {
      public:
        Addition(const Expression& left, const Expression& right);

        virtual double getValue() const override;
        virtual Expression* copy() const override;
        virtual ExpressionType getType() const override;        

        virtual std::string toString() const override;
    };

} // namespace cas::math