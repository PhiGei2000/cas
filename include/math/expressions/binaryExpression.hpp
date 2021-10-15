#pragma once

#include "expression.hpp"

namespace cas::math {

    struct Term;

    struct BinaryExpression : public Expression {
      public:
        Expression* left;
        Expression* right;

        ~BinaryExpression();

        virtual bool dependsOn(const Variable& var) const override;
    };

} // namespace cas::math