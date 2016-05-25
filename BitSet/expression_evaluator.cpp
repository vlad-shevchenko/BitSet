#include "expression_evaluator.h"

#include <symbols.h>
#include <parser.cpp>
#include <lexer.cpp>

BitSet ExpressionEvaluator::evaluate()
{
    QList<symbols::Symbol> tokens = Lexer(this->expression).tokenize();
    return Parser(tokens).parse();
}
