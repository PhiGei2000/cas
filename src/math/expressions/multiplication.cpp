#include "math/expressions/multiplication.hpp"

#include "math/expressions/addition.hpp"

namespace cas::math {
    Multiplication::Multiplication(const std::initializer_list<Term*>& factors)
        : OperationTerm(ExpressionType::Multiplication, factors) {
    }

    Multiplication::Multiplication(const std::vector<Term*>& factors)
        : OperationTerm(ExpressionType::Multiplication, factors) {
    }

    bool Multiplication::equals(Term* other) const {
        if (other->type == ExpressionType::Multiplication) {
            Multiplication* prod = reinterpret_cast<Multiplication*>(other);

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

    Term* Multiplication::copy() const {
        Multiplication* multiplication = new Multiplication({});

        for (const Term* term : subterms) {
            multiplication->addSubterm(term->copy());
        }

        return multiplication;
    }

    std::string Multiplication::toString() const {
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

    Term* Multiplication::simplify() const {
        // simplify subterms
        std::vector<Term*> subterms = OperationTerm::simplifySubterms(
            [&](double curr, double next) { return curr * next; },
            1);

        // apply distributive property
        std::vector<Addition*> sums;

        for (auto it = subterms.begin(); it != subterms.end();) {
            Term* subterm = *it;

            if (subterm->type == ExpressionType::Addition) {
                sums.push_back(reinterpret_cast<Addition*>(*it));

                it = subterms.erase(it);
            }
            else {
                it++;
            }
        }

        if (sums.size() > 0) {
            Addition* result = new Addition(*sums.front());
            {
                auto it = sums.begin() + 1;
                while (it != sums.end()) {
                    Addition* sum = *it;
                    Addition* tmp = new Addition({});

                    for (auto jt = result->begin(); jt != result->end(); jt++) {
                        Term* summand = *jt;
                        for (auto kt = sum->begin(); kt != sum->end(); kt++) {
                            Term* summand2 = *kt;
                            Multiplication* prod = summand->type == ExpressionType::Multiplication
                                                       ? reinterpret_cast<Multiplication*>(summand)
                                                       : new Multiplication({summand->copy()});
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

        if (subterms.size() == 1) {
            Term* term = subterms[0];

            return term->copy();
        }

        return new Multiplication(subterms);
    }
} // namespace cas::math