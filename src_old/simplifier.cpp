#include "math/expressions/simplifier.hpp"

#include "math/expressions.hpp"
#include "math/expressions/additionTerm.hpp"
#include "math/expressions/constantTerm.hpp"
#include "math/expressions/multiplicationTerm.hpp"
#include "math/expressions/term.hpp"
#include "math/expressions/variableTerm.hpp"

namespace cas::math {
    std::vector<Expression*> Simplifier::getSubterms(Expression* term, ExpressionType type) {
        std::vector<Expression*> subterms;
        if (term->getType() == type) {

            switch (type) {
            case ExpressionType::Addition: {
                Addition* addition = reinterpret_cast<Addition*>(term);

                std::vector<Expression*> leftSubterms = getSubterms(addition->left, type);
                std::vector<Expression*> rightSubterms = getSubterms(addition->right, type);

                subterms.insert(subterms.end(), leftSubterms.begin(), leftSubterms.end());
                subterms.insert(subterms.end(), rightSubterms.begin(), rightSubterms.end());
                break;
            }
            case ExpressionType::Multiplication: {
                Multiplication* multiplication = reinterpret_cast<Multiplication*>(term);

                std::vector<Expression*> leftFactors = getSubterms(multiplication->left, type);
                std::vector<Expression*> rightFactors = getSubterms(multiplication->right, type);

                subterms.insert(subterms.end(), leftFactors.begin(), leftFactors.end());
                subterms.insert(subterms.end(), rightFactors.begin(), rightFactors.end());
                break;
            }
            default:
                subterms.push_back(term);
                break;
            }
        }
        else {
            subterms.push_back(term);
        }

        return subterms;
    }

    Term* Simplifier::convertToTerm(Expression* expr) {
        if (expr->hasValue()) {
            double value = expr->getValue();

            return new ConstantTerm(value);
        }

        switch (expr->getType()) {
        case ExpressionType::Variable: {
            Variable* var = reinterpret_cast<Variable*>(expr);

            return new VariableTerm(var->getCharacter());
        }
        case ExpressionType::Addition: {
            Addition* addition = reinterpret_cast<Addition*>(expr);

            std::vector<Expression*> summands = getSubterms(addition, ExpressionType::Addition);
            std::vector<Term*> subterms;

            for (auto summand : summands) {
                subterms.push_back(convertToTerm(summand));
            }

            return new AdditionTerm(subterms);
        }
        case ExpressionType::Multiplication: {
            Multiplication* prod = reinterpret_cast<Multiplication*>(expr);

            std::vector<Expression*> factors = getSubterms(prod, ExpressionType::Multiplication);
            std::vector<Term*> subterms;

            for (auto factor : factors) {
                subterms.push_back(convertToTerm(factor));
            }

            return new MultiplicationTerm(subterms);
        }
        default:
            return nullptr;
        }
    }
} // namespace cas::math