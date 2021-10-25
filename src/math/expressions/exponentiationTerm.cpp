#include "math/expressions/exponentiationTerm.hpp"

#include "math/expressions/multiplicationTerm.hpp"

#include <sstream>

namespace cas::math {
    ExponentiationTerm::ExponentiationTerm(Term* base, Term* exponent)
        : base(base), exponent(exponent), Term(ExpressionType::Exponentiation) {
    }

    bool ExponentiationTerm::equals(Term* other) const {
        return false;
    }

    std::string ExponentiationTerm::toString() const {
        std::stringstream ss;

        if (base->type == ExpressionType::Exponentiation) {
            ss << "(" << base->toString() << ")";
        }
        else {
            ss << base->toString();
        }

        ss << "^";

        if (exponent->type == ExpressionType::Exponentiation) {
            ss << "(" << exponent->toString() << ")";
        }
        else {
            ss << exponent->toString();
        }

        return ss.str();
    }

    Term* ExponentiationTerm::copy() const {
        return new ExponentiationTerm(base->copy(), exponent->copy());
    }

    Term* ExponentiationTerm::simplify() const {
        Term* simpleBase = base->simplify();
        Term* simpleExponent = exponent->simplify();

        Term* result;
        if (simpleExponent->type == ExpressionType::Addition) {
            
        }

        switch (simpleBase->type) {
        case ExpressionType::Multiplication:
            MultiplicationTerm* baseMul = reinterpret_cast<MultiplicationTerm*>(simpleBase);

            std::vector<Term*> factors;
            for (auto it = baseMul->begin(); it != baseMul->end(); it++) {
                factors.push_back(new ExponentiationTerm(*it, simpleExponent));
            }

            result = new MultiplicationTerm(factors);
            break;
        }
    }
} // namespace cas::math
