#pragma once

#include "term.hpp"

namespace cas::math {
    struct Constant : public Term {
        double value;

        Constant(double value);

        void add(Term* term) = delete;

        virtual bool equals(Term* other) const override;

        virtual Term* copy() const override;

        virtual std::string toString() const override;
    };
} // namespace cas::math