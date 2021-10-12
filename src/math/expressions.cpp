#include "math/expressions.hpp"

#include <math.h>
#include <stdexcept>

namespace cas::math
{

Constant::Constant(double value)
    : value(value) {
}

double Constant::getValue() const {
    return value;
}

Expression* Constant::copy() const {
    return new Constant(*this);
}

constexpr ExpressionType Constant::getType() const {
    return ExpressionType::Constant;
}

bool Constant::dependsOn(const Variable& var) const {
    return false;
}

std::string Constant::toString() const {
    return std::to_string(value);
}

Variable::Variable(char character)
    : character(character) {
}

char Variable::getCharacter() const {
    return character;
}

bool Variable::dependsOn(const Variable& var) const {
    return character == var.character;
}

double Variable::getValue() const {
    throw std::runtime_error("Cannot get value of a variable");
}

Expression* Variable::copy() const {
    return new Variable(*this);
}

constexpr ExpressionType Variable::getType() const {
    return ExpressionType::Variable;
}

std::string Variable::toString() const {
    return std::string(1, character);
}

BinaryExpression::BinaryExpression(const Expression& left, const Expression& right) {
    this->left = left.copy();
    this->right = right.copy();
}

BinaryExpression::~BinaryExpression() {
    delete left;
    delete right;
}

bool BinaryExpression::dependsOn(const Variable& var) const {
    return left->dependsOn(var) || right->dependsOn(var);
}

#pragma region Addition
Addition::Addition(const Expression& left, const Expression& right)
    : BinaryExpression(left, right) {
}

double Addition::getValue() const {
    return left->getValue() + right->getValue();
}

Expression* Addition::copy() const {
    return new Addition(*this);
}

constexpr ExpressionType Addition::getType() const {
    return ExpressionType::Addition;
}

std::string Addition::toString() const {
    return left->toString() + " + " + right->toString();
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
    return new Multiplication(*this);
}

constexpr ExpressionType Multiplication::getType() const {
    return ExpressionType::Multiplication;
}

std::string Multiplication::toString() const {
    return left->toString() + " * " + right->toString();
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
    return new Exponentiation(*this);
}

constexpr ExpressionType Exponentiation::getType() const {
    return ExpressionType::Exponentiation;
}

std::string Exponentiation::toString() const {
    return left->toString() + " ^ " + right->toString();
}

#pragma endregion

#pragma region operators
Addition operator+(const Expression& left, const Expression& right) {
    return Addition(left, right);
}

Addition operator-(const Expression& left, const Expression& right) {
    return Addition(left, Multiplication(Constant(-1), right));
}

Multiplication operator*(const Expression& left, const Expression& right) {
    return Multiplication(left, right);
}

Multiplication operator/(const Expression& left, const Expression& right) {
    return Multiplication(left, Exponentiation(right, Constant(-1)));
}

#pragma endregion

} // namespace cas::math
