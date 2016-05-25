#ifndef EXPRESSIONEVALUATOR_H
#define EXPRESSIONEVALUATOR_H

#include <bitset.h>

#include <QString>

class ExpressionEvaluator
{
private:
    QString expression;
public:
    ExpressionEvaluator(QString expression) : expression(expression) {}

    BitSet evaluate();
};

#endif // EXPRESSIONEVALUATOR_H
