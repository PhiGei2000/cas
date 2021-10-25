#pragma once

#include "math/expressions/expression.hpp"

namespace cas::math {

struct Variable : public Expression {
  protected:
    char character;

  public:
    Variable(char character);

    char getCharacter() const;

    virtual bool dependsOn(const Variable& var) const override;

    virtual double getValue() const override;
    
    virtual ExpressionType getType() const override;

    virtual std::string toString() const override;

    virtual bool equals(Expression* expr) const override;
    
    virtual bool hasValue() const override;
};

}
