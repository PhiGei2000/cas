#pragma once

#include "expression.hpp"

namespace cas::math {

    struct BinaryExpression : public Expression {
      public:
        Expression* left;
        Expression* right;

        ~BinaryExpression();

        virtual bool dependsOn(const Variable& var) const override;

        virtual bool hasValue() const override;

        virtual bool equals(Expression* other) const override;
    };

} // namespace cas::math