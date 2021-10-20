#include "math/expressions/multiplicationTerm.hpp"

#include "math/expressions/additionTerm.hpp"

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

    Term* MultiplicationTerm::copy() const {
        MultiplicationTerm* multiplication = new MultiplicationTerm({});

        for (const Term* term : subterms) {
            multiplication->addSubterm(term->copy());
        }

        return multiplication;
    }

    std::string MultiplicationTerm::toString() const {
        std::string result;

        for (int i = 0; i < subterms.size(); i++) {
            if (i > 0) {
                result.append(" * ");
            }

            bool addition = subterms[i]->type == ExpressionType::Addition;

            if (addition) {
                result.append("(" + subterms[i]->toString() + ")");
            }
            else {
                result.append(subterms[i]->toString());
            }
        }

        return result;
    }

    void MultiplicationTerm::simplify() {
        // simplify subterms
        OperationTerm::simplifySubterms(
            [&](double curr, double next) { return curr * next; },
            1);

        // apply distributive property
        std::vector<AdditionTerm*> sums;

        for (auto it = subterms.begin(); it != subterms.end();) {
            Term* subterm = *it;

            if (subterm->type == ExpressionType::Addition) {
                sums.push_back(reinterpret_cast<AdditionTerm*>(*it));

                it = subterms.erase(it);
            }
            else {
                it++;
            }
        }

        if (sums.size() > 0) {
            AdditionTerm* result = new AdditionTerm(*sums.front());
            {
                auto it = sums.begin() + 1;
                while (it != sums.end()) {
                    AdditionTerm* sum = *it;
                    AdditionTerm* tmp = new AdditionTerm({});

                    for (auto jt = result->begin(); jt != result->end(); jt++) {
                        Term* summand = *jt;
                        for (auto kt = sum->begin(); kt != sum->end(); kt++) {
                            Term* summand2 = *kt;
                            MultiplicationTerm* prod = summand->type == ExpressionType::Multiplication
                                                           ? reinterpret_cast<MultiplicationTerm*>(summand)
                                                           : new MultiplicationTerm({summand->copy()});
                            prod->addSubterm(summand2->copy());

                            tmp->addSubterm(prod);
                        }
                    }

                    delete result;
                    result = tmp;

                    it++;
                }
            }

            result->simplify();
            subterms.push_back(result);
        }
    }
} // namespace cas::math