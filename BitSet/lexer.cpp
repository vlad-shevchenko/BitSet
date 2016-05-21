#include "lexer.h"

Lexer::Lexer(QString expression) : expression(expression)
{

}

QList<symbols::AbstractSymbol> Lexer::tokenize()
{
    return QList();
}
