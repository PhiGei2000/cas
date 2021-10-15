#pragma once

#include "expressions/addition.hpp"
#include "expressions/constant.hpp"
#include "expressions/exponentiation.hpp"
#include "expressions/multiplication.hpp"
#include "expressions/variable.hpp"

namespace cas::math {
    Addition* operator+(Expression& left, Expression& right);
    Addition* operator-(Expression& left, Expression& right);
    Multiplication* operator*(Expression& left, Expression& right);
    Multiplication* operator/(Expression& left, Expression& right);    
} // namespace cas::math
