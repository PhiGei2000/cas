#include "math/expressions/expression.hpp"

#include "math/expressions/addition.hpp"
#include "math/expressions/constant.hpp"
#include "math/expressions/exponentiation.hpp"
#include "math/expressions/multiplication.hpp"
#include "math/expressions/variable.hpp"

#include <iostream>

namespace cas::math {
    std::map<std::type_index, ExpressionType> Expression::expressionTypeMappings = std::map<std::type_index, ExpressionType>({{typeid(Constant), ExpressionType::Constant},
                                                                                                                              {typeid(Variable), ExpressionType::Variable},
                                                                                                                              {typeid(Addition), ExpressionType::Addition},
                                                                                                                              {typeid(Multiplication), ExpressionType::Multiplication},
                                                                                                                              {typeid(Exponentiation), ExpressionType::Exponentiation}});

    Addition* Expression::add(Expression* other) {
        Addition* result = create<Addition>();
        result->heap = true;

        result->left = this;
        result->right = other;

        return result;
    }

    Multiplication* Expression::multiply(Expression* other) {
        Multiplication* result = create<Multiplication>();

        result->left = this;
        result->right = other;

        return result;
    }

    Exponentiation* Expression::pow(Expression* exponent) {
        Exponentiation* result = create<Exponentiation>();

        result->left = this;
        result->right = exponent;

        return result;
    }

    template<typename T>
    T* Expression::create() {
        T* expr = new T();        

        expr->heap = true;
        return expr;
    }

    // template<typename T>
    // bool Expression::convert(Expression* in, T* out) {
    //     std::type_index type = typeid(T);

    //     // TODO: Fix this (segmentation fault)
    //     bool canConvert = expressionTypeMappings.find(type) != expressionTypeMappings.end() ? in->getType() == expressionTypeMappings[type] : false;
    //     if (canConvert) {
    //         out = reinterpret_cast<T*>(in);
    //     }

    //     return canConvert;
    // }

    void Expression::operator delete(void* ptr) {
        Expression* expr = reinterpret_cast<Expression*>(ptr);

        if (expr->heap) {
            ::operator delete(ptr);
        }
    }

    // template bool Expression::convert<Variable>(Expression*, Variable*);
    // template bool Expression::convert<Addition>(Expression*, Addition*);
} // namespace cas::math