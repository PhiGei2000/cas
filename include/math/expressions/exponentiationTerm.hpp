#pragma once

#include "term.hpp"

namespace cas::math {
    struct ExponentiationTerm : public Term {
      public:
        Term* base;
        Term* exponent;

        ExponentiationTerm(Term* base, Term* exponent);

        bool equals(Term* other) const override;

        std::string toString() const override;

        Term* copy() const override;

        Term* simplify() const override;
    };
} // namespace cas::math
