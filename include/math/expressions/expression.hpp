#pragma once

#include <map>
#include <string>
#include <typeindex>

namespace cas::math {
    enum class ExpressionType
    {
        Constant,
        Variable,
        Addition,
        Multiplication,
        Exponentiation
    };

    struct Variable;
    struct Addition;
    struct Multiplication;
    struct Exponentiation;

    struct Expression {
      private:
        bool heap = false;

        static std::map<std::type_index, ExpressionType> expressionTypeMappings;

      public:
        Addition* add(Expression* other);
        Multiplication* multiply(Expression* other);
        Exponentiation* pow(Expression* exponent);

        virtual double getValue() const = 0;

        virtual ExpressionType getType() const = 0;

        virtual bool dependsOn(const Variable& var) const = 0;

        virtual std::string toString() const = 0;

        template<typename T>
        static T* create();

        // template<typename T>
        // static bool convert(Expression* in, T* out);

        void operator delete(void* ptr);

        virtual bool equals(Expression* other) const = 0;

        virtual bool hasValue() const = 0;
    };
} // namespace cas::math