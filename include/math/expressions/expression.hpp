#pragma once

#include <string>

namespace cas {
  class Engine;
}

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

    struct Expression {
      public:
        const ExpressionId getId() const;

        virtual double getValue() const = 0;

        virtual ExpressionType getType() const = 0;

        virtual bool dependsOn(const Variable& var) const = 0;

        virtual std::string toString() const = 0;
    };
} // namespace cas::math