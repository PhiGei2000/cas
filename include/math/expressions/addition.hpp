#pragma once

#include "binaryExpression.hpp"

namespace cas::math {

    struct Addition : public BinaryExpression {
      public:      
        virtual double getValue() const override;
                
        virtual ExpressionType getType() const override;        

        virtual std::string toString() const override;

        virtual bool equals(Expression* other) const override;
    };

} // namespace cas::math