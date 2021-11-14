#pragma once

#include "term.hpp"

namespace cas::math {
    struct Variable : public Term {
      protected:
        char character;

      public:
        Variable(char character);

        char getCharacter() const;

        virtual bool equals(Term* other) const override;

        virtual Term* copy() const override;

        virtual std::string toString() const override;
    };
} // namespace cas::math