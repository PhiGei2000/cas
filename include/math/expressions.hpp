#pragma once

#include <memory>
#include <string>

namespace cas::math
{
enum class ExpressionType
{
    Constant,
    Variable,
    Addition,
    Multiplication,
    Exponentiation
};

class Variable;

class Expression {
  public:
    virtual double getValue() const = 0;
    virtual Expression* copy() const = 0;
    virtual constexpr ExpressionType getType() const = 0;

    virtual bool dependsOn(const Variable& var) const = 0;    

    virtual std::string toString() const = 0;
};

class Constant : public Expression {
  protected:
    double value;

  public:
    Constant(double value);

    virtual double getValue() const override;
    virtual Expression* copy() const override;
    virtual constexpr ExpressionType getType() const override;

    virtual bool dependsOn(const Variable& var) const override;

    virtual std::string toString() const override;
};

class Variable : public Expression {
  protected:
    char character;

  public:
    Variable(char character);    

    char getCharacter() const;

    virtual bool dependsOn(const Variable& var) const override;

    virtual double getValue() const override;
    virtual Expression* copy() const override;
    virtual constexpr ExpressionType getType() const override;

    virtual std::string toString() const override;
};

class BinaryExpression : public Expression {
  public:
    Expression* left = nullptr;
    Expression* right = nullptr;

    BinaryExpression(const Expression& left, const Expression& right);
    ~BinaryExpression();

    virtual bool dependsOn(const Variable& var) const override;
};

class Addition : public BinaryExpression {
  public:
    Addition(const Expression& left, const Expression& right);

    virtual double getValue() const override;
    virtual Expression* copy() const override;
    virtual constexpr ExpressionType getType() const override;

    virtual std::string toString() const override;
};

class Multiplication : public BinaryExpression {
  public:
    Multiplication(const Expression& left, const Expression& right);

    virtual double getValue() const override;
    virtual Expression* copy() const override;
    virtual constexpr ExpressionType getType() const override;

    virtual std::string toString() const override;
};

class Exponentiation : public BinaryExpression {
  public:
    Exponentiation(const Expression& left, const Expression& right);

    virtual double getValue() const override;
    virtual Expression* copy() const override;
    virtual constexpr ExpressionType getType() const override;

    virtual std::string toString() const override;
};

Addition operator+(const Expression& left, const Expression& right);
Addition operator-(const Expression& left, const Expression& right);
Multiplication operator*(const Expression& left, const Expression& right);
Multiplication operator/(const Expression& left, const Expression& right);

} // namespace cas::math
