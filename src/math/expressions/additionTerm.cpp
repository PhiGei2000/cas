#include "math/expressions/additionTerm.hpp"

#include "math/expressions/constantTerm.hpp"

namespace cas::math {
    AdditionTerm::AdditionTerm(const std::initializer_list<Term*>& summands)
        : OperationTerm(ExpressionType::Addition, summands) {
    }

    AdditionTerm::AdditionTerm(const std::vector<Term*>& summands)
        : OperationTerm(ExpressionType::Addition, summands) {
    }

    bool AdditionTerm::equals(Term* other) const {
        if (other->type == ExpressionType::Addition) {
            AdditionTerm* addition = reinterpret_cast<AdditionTerm*>(other);

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

    Term* AdditionTerm::copy() const {
        AdditionTerm* addition = new AdditionTerm({});

        for (const Term* term : subterms) {
            addition->addSubterm(term->copy());
        }

        return addition;
    }

    std::string AdditionTerm::toString() const {
        std::string result;

        for (int i = 0; i < subterms.size(); i++) {
            if (i > 0) {
                result.append(" + ");
            }
            result.append(subterms[i]->toString());
        }

        return result;
    }

    Term* AdditionTerm::simplify() const {
        std::vector<Term*> summands = OperationTerm::simplifySubterms(
            [&](double curr, double next) { return curr + next; }, 0);

        return new AdditionTerm(summands);
    }
} // namespace cas::math
