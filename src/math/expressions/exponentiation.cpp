#include "math/expressions/exponentiation.hpp"

#include "math/expressions/addition.hpp"
#include "math/expressions/multiplication.hpp"

#include <sstream>

namespace cas::math {
    Exponentiation::Exponentiation(Term* base, Term* exponent)
        : base(base), exponent(exponent), Term(ExpressionType::Exponentiation) {
    }

    bool Exponentiation::equals(Term* other) const {
        return false;
    }

    std::string Exponentiation::toString() const {
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

    Term* Exponentiation::copy() const {
        return new Exponentiation(base->copy(), exponent->copy());
    }

    Term* Exponentiation::simplify() const {
        Term* simplifiedBase = base->simplify();
        Term* simplifiedExponent = exponent->simplify();

        Term* result;
        switch (simplifiedBase->type) {
        case ExpressionType::Multiplication:
            Multiplication* baseMul = reinterpret_cast<Multiplication*>(simplifiedBase);

            std::vector<Term*> factors;
            // e^(x+y) = e^x * e^y
            if (simplifiedExponent->type == ExpressionType::Addition) {
                Addition* expAdd = reinterpret_cast<Addition*>(simplifiedExponent);

                for (auto it = baseMul->begin(); it != baseMul->end(); it++) {
                    for (auto jt = expAdd->begin(); jt != expAdd->end(); jt++) {
                        factors.push_back(new Exponentiation(*it, *jt));
                    }
                }
            }
            else {
                for (auto it = baseMul->begin(); it != baseMul->end(); it++) {
                    factors.push_back(new Exponentiation(*it, simplifiedExponent));
                }
            }

            result = new Multiplication(factors);
            break;
        }
    }
} // namespace cas::math
