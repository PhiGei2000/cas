#pragma once

#include "expression.hpp"

#include <vector>
#include <string>

namespace cas::math {
    struct Term {
        const cas::math::ExpressionType type;

        Term(ExpressionType type);

        virtual bool equals(Term* other) const = 0;

        virtual std::string toString() const = 0;

        bool operator==(Term* other) const;
    };

    struct OperationTerm : public Term {
      protected:
        std::vector<Term*> subterms;

        void checkSubterms();

      public:
        OperationTerm(ExpressionType type, const std::initializer_list<Term*>& subterms);
        OperationTerm(ExpressionType type, const std::vector<Term*>& subterms);

        int size() const;
        std::vector<Term*> getSubterms() const;
    };
} // namespace cas::math