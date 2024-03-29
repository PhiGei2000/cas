#pragma once

#include "binaryExpression.hpp"

namespace cas::math {

    struct Addition : public BinaryExpression {
      public:
        Addition(const Expression& left, const Expression& right);
        Addition(Expression* left, Expression* right);

        virtual Number getValue() const override;
        virtual Expression* copy() const override;
        virtual ExpressionTypes getType() const override;

        virtual Expression* simplify() const override;

        virtual Expression* differentiate(const Variable* var) const override;

        virtual std::string toString() const override;
    };

} // namespace cas::math