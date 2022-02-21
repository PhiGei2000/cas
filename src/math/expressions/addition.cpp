#include "math/expressions/addition.hpp"

#include "math/expressions/constant.hpp"

namespace cas::math {
    Addition::Addition(const std::initializer_list<Term*>& summands)
        : OperationTerm(ExpressionType::Addition, summands) {
    }

    Addition::Addition(const std::vector<Term*>& summands)
        : OperationTerm(ExpressionType::Addition, summands) {
    }

    bool Addition::equals(Term* other) const {
        if (other->type == ExpressionType::Addition) {
            Addition* addition = reinterpret_cast<Addition*>(other);

            std::vector<Term*> subterms = this->subterms;
            auto it = addition->subterms.begin();

            for (; it != addition->subterms.end(); it++) {
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

    Term* Addition::copy() const {
        Addition* addition = new Addition({});

        for (const Term* term : subterms) {
            addition->addSubterm(term->copy());
        }

        return addition;
    }

    std::string Addition::toString() const {
        std::string result;

        for (int i = 0; i < subterms.size(); i++) {
            if (i > 0) {
                result.append(" + ");
            }
            result.append(subterms[i]->toString());
        }

        return result;
    }

    Term* Addition::simplify() const {
        std::vector<Term*> summands = OperationTerm::simplifySubterms(
            [&](double curr, double next) { return curr + next; }, 0);

        if (summands.size() == 1) {
            if (summands.front()->type == ExpressionType::Constant || summands.front()->type == ExpressionType::Variable) {
                return summands.front();
            }
        }

        return new Addition(summands);
    }
} // namespace cas::math
