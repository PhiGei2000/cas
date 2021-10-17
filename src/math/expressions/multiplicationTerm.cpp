#include "math/expressions/multiplicationTerm.hpp"

namespace cas::math {
    MultiplicationTerm::MultiplicationTerm(const std::initializer_list<Term*>& factors)
        : OperationTerm(ExpressionType::Multiplication, factors) {
    }

    MultiplicationTerm::MultiplicationTerm(const std::vector<Term*>& factors)
        : OperationTerm(ExpressionType::Multiplication, factors) {
    }

    bool MultiplicationTerm::equals(Term* other) const {
        if (other->type == ExpressionType::Multiplication) {
            MultiplicationTerm* prod = reinterpret_cast<MultiplicationTerm*>(other);

            std::vector<Term*> subterms = this->subterms;
            auto it = prod->subterms.begin();

            for (; it != prod->subterms.end(); it++) {
                bool found = false;
                auto jt = subterms.begin();

                for (; jt != subterms.end(); jt++) {
                    if ((*jt)->equals(*it)) {
                        found = true;
                        break;
                    }
                }

                if (found) {
                    subterms.erase(jt);
                }
                else {
                    return false;
                }
            }

            return subterms.size() == 0;
        }

        return false;
    }

    std::string MultiplicationTerm::toString() const {
        std::string result;

        for (int i = 0; i < subterms.size(); i++) {
            if (i > 0) {
                result.append(" * ");
            }
            result.append(subterms[i]->toString());
        }

        return result;
    }
} // namespace cas::math