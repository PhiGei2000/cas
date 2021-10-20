#include "math/expressions/term.hpp"

#include "math/expressions/constantTerm.hpp"

#include <stdexcept>

namespace cas::math {
    Term::Term(ExpressionType type)
        : type(type) {
    }

    // Term* Term::getParent() const {
    //     return parent;
    // }

    OperationTerm::OperationTerm(ExpressionType type, const std::initializer_list<Term*>& subterms)
        : subterms(subterms), Term(type) {
    }

    OperationTerm::OperationTerm(ExpressionType type, const std::vector<Term*>& subterms)
        : subterms(subterms), Term(type) {
    }

    bool Term::hasSubterms() const {
        return false;
    }

    void OperationTerm::checkSubterms() {
        auto it = subterms.begin();

        std::vector<Term*> newSubterms;

        while (it != subterms.end()) {
            const Term* term = *it;
            if (term->type == this->type) {
                const OperationTerm* subterm = reinterpret_cast<const OperationTerm*>(term);
                newSubterms.insert(subterms.end(), subterm->subterms.begin(), subterm->subterms.end());

                it = subterms.erase(it);
            }
        }

        subterms.insert(subterms.end(), newSubterms.begin(), newSubterms.end());
    }

    bool OperationTerm::hasSubterms() const {
        return true;
    }

    void OperationTerm::addSubterm(Term* term) {
        // term->parent = this;

        if (term->type == type) {
            OperationTerm* opTerm = reinterpret_cast<OperationTerm*>(term);
            subterms.insert(subterms.end(), opTerm->begin(), opTerm->end());
        }
        else {
            subterms.push_back(term);
        }
    }

    int OperationTerm::size() const {
        return subterms.size();
    }

    std::vector<Term*> OperationTerm::getSubterms() const {
        return subterms;
    }

    void OperationTerm::simplifySubterms(std::function<double(double, double)> aggreate, double startValue) {
        std::vector<ConstantTerm*> constants;

        for (auto it = subterms.begin(); it != subterms.end();) {
            Term* subterm = *it;
            if (subterm->hasSubterms()) {
                OperationTerm* opTerm = reinterpret_cast<OperationTerm*>(subterm);
                opTerm->simplify();

                // TODO: Change term type if there is only one subterm left
            }

            if (subterm->type == ExpressionType::Constant) {
                constants.push_back(reinterpret_cast<ConstantTerm*>(subterm));
                it = subterms.erase(it);
            }
            else {
                it++;
            }
        }

        if (constants.size() > 0) {
            ConstantTerm* result = new ConstantTerm(startValue);
            for (auto constant : constants) {
                result->value = aggreate(result->value, constant->value);

                delete constant;
            }

            subterms.push_back(result);
        }
    }

    Term* OperationTerm::operator[](int index) const {
        return subterms[index];
    }

    std::vector<Term*>::iterator OperationTerm::begin() {
        return subterms.begin();
    }

    std::vector<Term*>::iterator OperationTerm::end() {
        return subterms.end();
    }

    bool Term::operator==(Term* other) const {
        return equals(other);
    }
} // namespace cas::math
