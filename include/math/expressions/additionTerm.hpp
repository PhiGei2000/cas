#pragma once

#include "term.hpp"

namespace cas::math {
    struct AdditionTerm : public OperationTerm {
      public:
        AdditionTerm(const std::initializer_list<Term*>& summands);
        AdditionTerm(const std::vector<Term*>& summands);

        virtual bool equals(Term* other) const override;

        std::string toString() const override;
    };
} // namespace cas::math
