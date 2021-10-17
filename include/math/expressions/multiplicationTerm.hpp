#pragma once 

#include "term.hpp"

namespace cas::math {
    struct MultiplicationTerm : public OperationTerm {
        MultiplicationTerm(const std::initializer_list<Term*>& factors);
        MultiplicationTerm(const std::vector<Term*>& factors);

        bool equals(Term* other) const override;

        std::string toString() const override;
    };
}