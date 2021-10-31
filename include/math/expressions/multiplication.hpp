#pragma once 

#include "term.hpp"

namespace cas::math {
    struct Multiplication : public OperationTerm {
        Multiplication(const std::initializer_list<Term*>& factors);
        Multiplication(const std::vector<Term*>& factors);

        bool equals(Term* other) const override;

        virtual Term* copy() const override;

        std::string toString() const override;

        virtual Term* simplify() const override;
    };
}