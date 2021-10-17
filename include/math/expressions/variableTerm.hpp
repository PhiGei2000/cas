#pragma once

#include "term.hpp"

namespace cas::math {
    struct VariableTerm : public Term {
      protected:
        char character;

      public:
        VariableTerm(char character);

        char getCharacter() const;

        virtual bool equals(Term* other) const override;

        virtual std::string toString() const override;
    };
} // namespace cas::math