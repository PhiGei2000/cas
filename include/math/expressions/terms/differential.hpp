#pragma once

#include "variable.hpp"

namespace cas::math {
    struct Differential : public Variable {
        Differential(VariableSymbol symbol);

        virtual Expression* copy() const override;

        virtual ExpressionType getType() const override;
        virtual std::string toString() const override;
    };
} // namespace cas::math