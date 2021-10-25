#pragma once

#include "expression.hpp"
#include "term.hpp"

namespace cas::math {
    class Simplifier {
      private:
        static std::vector<Expression*> getSubterms(Expression* term, ExpressionType type);

      public:
        static Term* convertToTerm(Expression* expr);
    };
} // namespace cas::math