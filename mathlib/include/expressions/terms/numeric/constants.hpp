#pragma once
#include "expressions/terms/constant.hpp"

#if WIN32
#include <numbers>
#endif

namespace cas::math{
    struct NamedConstant : public Number {
      protected:
        std::string symbol;

      public:
        inline NamedConstant(const std::string& symbol, double value)
            :Number(value), symbol(symbol) {

        }

        inline virtual Expression* copy() const override {
          return new NamedConstant(symbol, value);
        }

        inline virtual ExpressionTypes getType() const override {
          return ExpressionTypes::NamedConstant;
        }

        inline virtual std::string toString() const override {
          return symbol;
        }
    };

    struct E : public NamedConstant {
      public:
        inline E()
            :NamedConstant("e", std::numbers::e){

        }
    };
}