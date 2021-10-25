#pragma once

#include <string>
#include <vector>
#include <functional>

namespace cas::math {
    enum class ExpressionType {
      Addition, Multiplication, Exponentiation, Constant, Variable
    };

    struct Term {
      protected:
        // Term* parent = nullptr;

        friend struct OperationTerm;

      public:
        const cas::math::ExpressionType type;

        Term(ExpressionType type);

        // Term* getParent() const;

        virtual bool hasSubterms() const;

        virtual bool equals(Term* other) const = 0;

        virtual std::string toString() const = 0;

        virtual Term* copy() const = 0;

        virtual Term* simplify() const;

        bool operator==(Term* other) const;
    };

    struct OperationTerm : public Term {
      protected:
        std::vector<Term*> subterms;

        void checkSubterms();
        std::vector<Term*> simplifySubterms(std::function<double(double, double)> aggreate, double startValue) const;

      public:
        OperationTerm(ExpressionType type, const std::initializer_list<Term*>& subterms);
        OperationTerm(ExpressionType type, const std::vector<Term*>& subterms);

        virtual bool hasSubterms() const override;
        void addSubterm(Term* subterm);

        int size() const;
        std::vector<Term*> getSubterms() const;

        virtual Term* simplify() const = 0;

        Term* operator[](int index) const;

        std::vector<Term*>::iterator begin();
        std::vector<Term*>::iterator end();
    };
} // namespace cas::math