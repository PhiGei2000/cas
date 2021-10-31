#pragma once

#include "term.hpp"

namespace cas::math {
    struct Addition : public OperationTerm {
      public:
        Addition(const std::initializer_list<Term*>& summands);
        Addition(const std::vector<Term*>& summands);

        virtual bool equals(Term* other) const override;

        std::string toString() const override;

        virtual Term* copy() const override;

        virtual Term* simplify() const override;
    };
} // namespace cas::math
