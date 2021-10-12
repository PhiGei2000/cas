#pragma once

#include <string>

namespace cas::math
{

class Expression {
  public:
    virtual double getValue() const = 0;
    virtual Expression* copy() const = 0;

    virtual std::string toString() const = 0;
};

class Constant : public Expression {
  protected:
    double value;

  public:
    Constant(double value);    

    virtual double getValue() const override;
    virtual Expression* copy() const override; 

    virtual std::string toString() const override;
};

class Variable : public Expression {
  protected:
    char character;
    Expression* value = nullptr;

  public:
    Variable(char character);
    Variable(char character, const Expression& value);

    char getCharacter() const;
    void assign(const Expression& value);

    virtual double getValue() const override;
    virtual Expression* copy() const override;

    virtual std::string toString() const override;
};

class BinaryExpression : public Expression {
  protected:
    Expression* left = nullptr;
    Expression* right = nullptr;

  public:
    BinaryExpression(const Expression& left, const Expression& right);
    ~BinaryExpression();
};

class Addition : public BinaryExpression {
  public:
    Addition(const Expression& left, const Expression& right);

    virtual double getValue() const override;
    virtual Expression* copy() const override;

    virtual std::string toString() const override;
};

class Multiplication : public BinaryExpression {
  public:
    Multiplication(const Expression& left, const Expression& right);

    virtual double getValue() const override;
    virtual Expression* copy() const override;

    virtual std::string toString() const override;
};

class Exponentiation : public BinaryExpression {
  public:
    Exponentiation(const Expression& left, const Expression& right);

    virtual double getValue() const override;
    virtual Expression* copy() const override;

    virtual std::string toString() const override;
};

Addition operator+(const Expression& left, const Expression& right);
Addition operator-(const Expression& left, const Expression& right);
Multiplication operator*(const Expression& left, const Expression& right);
Multiplication operator/(const Expression& left, const Expression& right);

} // namespace cas::expressions
