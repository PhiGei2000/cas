#include "math/expressions.hpp"

namespace cas::math
{
Addition* operator+(Expression& left, Expression& right) {
    return left.add(&right);
}

Addition* operator-(Expression& left, Expression& right) {
    return left.add(right.multiply(new Constant(-1)));
}

Multiplication* operator*(Expression& left, Expression& right) {
    return left.multiply(&right);
}

Multiplication* operator/(Expression& left, Expression& right) {
    return left.multiply(right.pow(new Constant(-1)));
}

} // namespace cas::math
