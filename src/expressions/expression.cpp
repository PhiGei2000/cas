#include "expressions/expression.hpp"

#include <math.h>

namespace cas::expressions
{
Constant::Constant(double value)
    : value(value) {
}

double Constant::getValue() const {
    return value;
}

Expression* Constant::copy() const {
    return new Constant(value);
}

Variable::Variable(char character)
    : character(character) {
}

Variable::Variable(char character, const Expression& value)
    : character(character) {
    this->value = value.copy();
}

char Variable::getCharacter() const {
    return character;
}

void Variable::assign(const Expression& value) {
    this->value = value.copy();
}

double Variable::getValue() const {
    return value->getValue();
}

Expression* Variable::copy() const {
    if (value == nullptr) {
        return new Variable(character);
    }

    return new Variable(character, *value);
}

BinaryExpression::BinaryExpression(const Expression& left, const Expression& right) {
    this->left = left.copy();
    this->right = right.copy();
}

BinaryExpression::~BinaryExpression() {
    if (left != nullptr) {
        delete left;
    }

    if (right != nullptr) {
        delete right;
    }
}

#pragma region Addition
Addition::Addition(const Expression& left, const Expression& right)
    : BinaryExpression(left, right) {
}

double Addition::getValue() const {
    return left->getValue() + right->getValue();
}

Expression* Addition::copy() const {
    return new Addition(*left, *right);
}

#pragma endregion

#pragma region Multiplication
Multiplication::Multiplication(const Expression& left, const Expression& right)
    : BinaryExpression(left, right) {
}

double Multiplication::getValue() const {
    return left->getValue() * right->getValue();
}

Expression* Multiplication::copy() const {
    return new Multiplication(*left, *right);
}

#pragma endregion

#pragma region Exponentiation
Exponentiation::Exponentiation(const Expression& left, const Expression& right)
    : BinaryExpression(left, right) {
}

double Exponentiation::getValue() const {
    return pow(left->getValue(), right->getValue());
}

Expression* Exponentiation::copy() const {
    return new Exponentiation(*left, *right);
}
#pragma endregion

#pragma region operators
Expression* operator+(const Expression& left, const Expression& right) {
    return new Addition(left, right);
}

Expression* operator-(const Expression& left, const Expression& right) {
    return new Addition(left, Multiplication(Constant(-1), right));
}

Expression* operator*(const Expression& left, const Expression& right) {
    return new Multiplication(left, right);
}

Expression* operator/(const Expression& left, const Expression& right) {
    return new Multiplication(left, Exponentiation(right, Constant(-1)));
}

} // namespace cas::expressions
