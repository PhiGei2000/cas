#pragma once

#include "term.hpp"

namespace cas::math {
    struct ConstantTerm : public Term {
        double value;

        ConstantTerm(double value);

        void add(Term* term) = delete;

        virtual bool equals(Term* other) const override;

        virtual std::string toString() const override;
    };
} // namespace cas::math