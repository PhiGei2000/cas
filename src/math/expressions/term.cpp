#include "math/expressions/term.hpp"

namespace cas::math {
    Term::Term(ExpressionType type)
        : type(type) {
    }

    OperationTerm::OperationTerm(ExpressionType type, const std::initializer_list<Term*>& subterms)
        : subterms(subterms), Term(type) {
    }

    OperationTerm::OperationTerm(ExpressionType type, const std::vector<Term*>& subterms)
        : subterms(subterms), Term(type) {
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

    int OperationTerm::size() const {
        return subterms.size();
    }

    std::vector<Term*> OperationTerm::getSubterms() const {
        return subterms;
    }

    bool Term::operator==(Term* other) const {
        return equals(other);
    }
} // namespace cas::math
