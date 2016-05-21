#include "expression_evaluator.h"

BitSet ExpressionEvaluator::evaluate()
{
    QList tokens = Lexer(this->expression).tokenize();
    return Parser(tokens);
}
