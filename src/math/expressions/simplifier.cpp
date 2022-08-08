#include "math/expressions/simplifier.hpp"

#include <math.h>
#include <stdexcept>

namespace cas::math {

#pragma region ProductParts
    void Simplifier::ProductParts::multiply(const Simplifier::ProductParts& parts) {
        coefficient *= parts.coefficient;

        for (const auto& [var, exp] : parts.variables) {
            variables[var] += exp;
        }
    }

    void Simplifier::ProductParts::power(double exponent) {
        coefficient = pow(coefficient, exponent);

        for (const auto& [var, _] : variables) {
            variables[var] *= exponent;
        }
    }

    bool Simplifier::ProductParts::areLike(const Simplifier::ProductParts& first, const Simplifier::ProductParts& second) {
        if (first.variables.size() != second.variables.size())
            return false;

        for (const auto& [var, exp] : first.variables) {
            try {
                if (second.variables.at(var) != exp) {
                    return false;
                }
            }
            catch (const std::out_of_range&) {
                return false;
            }
        }

        return true;
    }
#pragma endregion

    Expression* Simplifier::simplify(const Expression* expr) {
        ExpressionType type = expr->getType();

        switch (type) {
            case ExpressionType::Addition:
                return simplifyAddition(reinterpret_cast<const Addition*>(expr));
            case ExpressionType::Multiplication:
                return simplifyMultiplication(reinterpret_cast<const Multiplication*>(expr));
            default:
                return expr->copy();
        }
    }

    Simplifier::ProductParts Simplifier::getProductParts(const Multiplication* prod) noexcept(false) {
        ProductParts parts;

        ExpressionType leftType = prod->left->getType();
        ExpressionType rightType = prod->right->getType();

        switch (leftType) {
            case ExpressionType::Addition:
                throw std::runtime_error("Can not get product parts if the product contains a addition as factor");

            case ExpressionType::Multiplication: {
                ProductParts leftParts = getProductParts(reinterpret_cast<Multiplication*>(prod->left));

                parts.multiply(leftParts);
            } break;

            case ExpressionType::Exponentiation: {
                Exponentiation* exp = reinterpret_cast<Exponentiation*>(prod->left);
                ProductParts leftParts = getExpProductParts(exp);
                parts.multiply(leftParts);

            } break;

            case ExpressionType::Constant: {
                Constant* c = reinterpret_cast<Constant*>(prod->left);
                parts.coefficient *= c->getValue();
            } break;

            case ExpressionType::Variable: {
                Variable* v = reinterpret_cast<Variable*>(prod->left);
                parts.variables[v->getCharacter()] += 1;
            } break;

            default: break;
        }

        switch (rightType) {
            case ExpressionType::Addition:
                throw std::runtime_error("Can not get product parts if the product contains a addition as factor");

            case ExpressionType::Multiplication: {
                ProductParts rightParts = getProductParts(reinterpret_cast<Multiplication*>(prod->right));

                parts.multiply(rightParts);
            } break;

            case ExpressionType::Exponentiation: {
                Exponentiation* exp = reinterpret_cast<Exponentiation*>(prod->right);
                ProductParts rightParts = getExpProductParts(exp);

                parts.multiply(rightParts);
            } break;

            case ExpressionType::Constant: {
                Constant* c = reinterpret_cast<Constant*>(prod->right);
                parts.coefficient *= c->getValue();
            } break;

            case ExpressionType::Variable: {
                Variable* v = reinterpret_cast<Variable*>(prod->right);
                parts.variables[v->getCharacter()] += 1;
            } break;

            default: break;
        }

        return parts;
    }

    Simplifier::ProductParts Simplifier::getExpProductParts(const Exponentiation* exp) noexcept(false) {
        ProductParts parts;
        double exponent = NAN;
        try {
            exponent = exp->right->getValue();
        }
        catch (std::exception e) {
            throw std::runtime_error("Only constants are allowed as exponents");
        }

        ExpressionType baseType = exp->left->getType();
        switch (baseType) {
            case ExpressionType::Addition:
                throw std::runtime_error("Can not get product parts if the product contains a addition as factor");

            case ExpressionType::Multiplication: {
                ProductParts baseParts = getProductParts(reinterpret_cast<Multiplication*>(exp->left));
                baseParts.power(exponent);

                parts.multiply(baseParts);
            } break;

            case ExpressionType::Exponentiation: {
                Exponentiation* innerExp = reinterpret_cast<Exponentiation*>(exp->left);
                ProductParts baseParts = getExpProductParts(innerExp);

                baseParts.power(exponent);
                parts.multiply(baseParts);
            } break;

            case ExpressionType::Constant: {
                Constant* c = reinterpret_cast<Constant*>(exp->left);

                parts.coefficient *= pow(c->getValue(), exponent);
            } break;

            case ExpressionType::Variable: {
                Variable* v = reinterpret_cast<Variable*>(exp->left);

                parts.variables[v->getCharacter()] += exponent;
            } break;

            default:
                break;
        }

        return parts;
    }

    void Simplifier::getSummands(const Expression* expr, std::vector<Expression*>* summands) {
        if (expr->getType() == ExpressionType::Addition) {
            const Addition* sum = reinterpret_cast<const Addition*>(expr);

            if (sum->left->getType() == ExpressionType::Addition) {
                const Addition* leftSum = reinterpret_cast<const Addition*>(sum->left);
                getSummands(leftSum, summands);
            }
            else {
                summands->push_back(sum->left->copy());
            }

            if (sum->right->getType() == ExpressionType::Addition) {
                const Addition* rightSum = reinterpret_cast<const Addition*>(sum->right);
                getSummands(rightSum, summands);
            }
            else {
                summands->push_back(sum->right->copy());
            }
        }
        else {
            summands->push_back(expr->copy());
        }
    }

    Expression* Simplifier::multiplyOut(const Expression* left, const Expression* right) {
        std::vector<Expression*> leftSummands, rightSummands;

        getSummands(left, &leftSummands);
        getSummands(right, &rightSummands);

        std::vector<Expression*> resultSummands;
        for (const auto& leftSummand : leftSummands) {
            for (const auto& rightSummand : rightSummands) {
                Multiplication* summand = new Multiplication(*leftSummand, *rightSummand);

                resultSummands.push_back(summand->simplify());
                delete summand;
            }
        }

        auto it = resultSummands.rbegin();
        Expression* result = *it;
        it++;

        while (it != resultSummands.rend()) {
            Addition* sum = new Addition(*it, result);
            result = sum;

            it++;
        }

        return result;
    }

    Expression* Simplifier::simplifyAddition(const Addition* sum) {
        // simplify both summands
        Expression* left = sum->left->simplify();
        Expression* right = sum->right->simplify();

        // evaluate numerical values if the summands are constants
        if (left->getType() == ExpressionType::Constant) {
            double leftValue = left->getValue();
            if (right->getType() == ExpressionType::Constant) {
                double value = leftValue + right->getValue();

                return new Constant(value);
            }
            // ignore first summand if it is zero
            else if (leftValue == 0) {
                return right;
            }
        }

        // ignore second summand if it is zero
        if (right->getType() == ExpressionType::Constant) {
            double rightValue = right->getValue();
            if (rightValue == 0)
                return left;
        }

        Addition* simplifiedSum = new Addition(left, right);
        if (left->getType() == ExpressionType::Addition || right->getType() == ExpressionType::Addition) {
            std::vector<Expression*> summands;
            getSummands(simplifiedSum, &summands);

            std::vector<ProductParts> combinedTerms = {};
            std::vector<Expression*> restTerms = {};
            for (const auto& summand : summands) {
                ExpressionType type = summand->getType();

                switch (type) {
                    case ExpressionType::Exponentiation: {
                        try {
                            ProductParts parts = getExpProductParts(reinterpret_cast<const Exponentiation*>(summand));

                            auto it = combinedTerms.begin();
                            while (it != combinedTerms.end()) {
                                if (ProductParts::areLike(*it, parts)) {
                                    break;
                                }

                                it++;
                            }

                            if (it == combinedTerms.end()) {
                                combinedTerms.push_back(parts);
                            }
                            else {
                                (*it).coefficient += parts.coefficient;
                            }
                        }
                        catch (const std::runtime_error&) {
                            restTerms.push_back(summand);
                        }
                    } break;
                    case ExpressionType::Multiplication: {
                        ProductParts parts = getProductParts(reinterpret_cast<const Multiplication*>(summand));

                        auto it = combinedTerms.begin();
                        while (it != combinedTerms.end()) {
                            if (ProductParts::areLike(*it, parts)) {
                                break;
                            }

                            it++;
                        }

                        if (it == combinedTerms.end()) {
                            combinedTerms.push_back(parts);
                        }
                        else {
                            (*it).coefficient += parts.coefficient;
                        }
                    } break;

                    case ExpressionType::Constant: {
                        double value = summand->getValue();

                        auto it = combinedTerms.begin();
                        while (it != combinedTerms.end() || (*it).variables.size() == 0) {
                            it++;
                        }

                        if (it == combinedTerms.end()) {
                            combinedTerms.push_back(ProductParts{value, {}});
                        }
                        else {
                            (*it).coefficient += value;
                        }
                    } break;

                    case ExpressionType::Variable: {
                        const Variable* var = reinterpret_cast<const Variable*>(summand);
                        ProductParts parts = ProductParts{1, std::unordered_map<char, double>{{var->getCharacter(), 1}}};

                        auto it = combinedTerms.begin();
                        while (it != combinedTerms.end() || ProductParts::areLike(*it, parts)) {
                            it++;
                        }

                        if (it == combinedTerms.end()) {
                            combinedTerms.push_back(parts);
                        }
                        else {
                            (*it).coefficient += parts.coefficient;
                        }
                    } break;
                    default: {
                        restTerms.push_back(summand);
                    } break;
                }
            }

            auto getFactor = [&](const std::unordered_map<char, double>::const_iterator& it) -> Expression* {
                double exp = (*it).second;
                if (exp == 1) {
                    return new Variable((*it).first);
                }
                else if (exp == 0) {
                    return new Constant(0);
                }

                Constant* exponent = new Constant(exp);
                Variable* variable = new Variable((*it).first);

                return new Exponentiation(variable, exponent);
            };
            auto getTerm = [&](const ProductParts& parts) -> Expression* {
                if (parts.variables.size() == 0) {
                    return new Constant(parts.coefficient);
                }

                auto it = parts.variables.begin();
                Expression* result = getFactor(it);
                it++;
                while (it != parts.variables.end()) {
                    Multiplication* prod = new Multiplication(getFactor(it), result);
                    result = prod;

                    it++;
                }

                if (parts.coefficient == 1) {
                    return result;
                }

                Constant* coefficient = new Constant(parts.coefficient);
                return new Multiplication(coefficient, result);
            };

            auto it = combinedTerms.rbegin();
            Expression* result = getTerm(*it);
            it++;

            while (it != combinedTerms.rend()) {
                Addition* sum = new Addition(getTerm(*it), result);
                result = sum;

                it++;
            }

            for (auto it = restTerms.begin(); it != restTerms.end(); it++) {
                Addition* sum = new Addition(*it, result);
                result = sum;
            }

            return result;
        }

        return simplifiedSum;
    }

    Expression* Simplifier::simplifyMultiplication(const Multiplication* prod) {
        // simplyfy both factors
        Expression* left = prod->left->simplify();
        Expression* right = prod->right->simplify();

        // evaluate numerical values if the factors are constants
        if (left->getType() == ExpressionType::Constant) {
            double leftValue = left->getValue();
            if (right->getType() == ExpressionType::Constant) {
                double value = leftValue * right->getValue();
                return new Constant(value);
            }
            // ignore fist factor if it is one
            else if (leftValue == 1) {
                return right;
            }
            // if one factor is zero then the product is zero
            else if (leftValue == 0) {
                return new Constant(0);
            }
        }

        if (right->getType() == ExpressionType::Constant) {
            double rightValue = right->getValue();

            // ignore second factor if it is one
            if (rightValue == 1) {
                return left;
            }
            // if one factor is zero then the product is zero
            else if (rightValue == 0) {
                return new Constant(0);
            }
        }

        // multiply out
        if (left->getType() == ExpressionType::Addition || right->getType() == ExpressionType::Addition) {
            Expression* sum = multiplyOut(left, right);

            return sum->simplify();
        }

        // create new product whit the simplified terms
        Multiplication* simplifiedProduct = new Multiplication(left, right);
        try {
            // reorder terms
            ProductParts parts = getProductParts(simplifiedProduct);
            delete simplifiedProduct;

            if (parts.variables.size() > 0) {
                Expression* result;

                auto getTerm = [&](std::unordered_map<char, double>::iterator it) -> Expression* {
                    double exp = (*it).second;
                    if (exp == 1) {
                        return new Variable((*it).first);
                    }
                    else if (exp == 0) {
                        return new Constant(0);
                    }

                    Constant* exponent = new Constant(exp);
                    Variable* variable = new Variable((*it).first);

                    return new Exponentiation(variable, exponent);
                };

                auto it = parts.variables.begin();
                result = getTerm(it);
                it++;

                while (it != parts.variables.end()) {
                    Multiplication* p = new Multiplication(getTerm(it), result);
                    result = p;

                    it++;
                }

                if (parts.coefficient != 1) {
                    Constant* coefficient = new Constant(parts.coefficient);
                    Multiplication* p = new Multiplication(coefficient, result);
                    result = p;
                }
                return result;
            }
            else {
                return new Constant(parts.coefficient);
            }
        }
        catch (const std::runtime_error&) {
            return simplifiedProduct;
        }
    }

    Expression* Simplifier::simplifyExponentiation(const Exponentiation* exp) {
        Expression* left = exp->left->simplify();
        Expression* right = exp->right->simplify();

        if (right->getType() == ExpressionType::Constant) {
            double value = right->getValue();

            if (left->getType() == ExpressionType::Constant) {
                return new Constant(pow(left->getValue(), value));
            }

            if (value == 0)
                return new Constant(1);
            else if (value == 1)
                return left;
        }

        return new Exponentiation(left, right);
    }
} // namespace cas::math