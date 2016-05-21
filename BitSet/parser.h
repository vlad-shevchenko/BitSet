#ifndef PARSER_H
#define PARSER_H

#include <bitset.h>
#include <symbols.h>

#include <QString>

class Parser
{
private:
    QList<symbols::AbstractSymbol> tokens;
public:
    Parser() {}
    Parser(QList<symbols::AbstractSymbol>& tokens) : tokens(tokens) {}

    BitSet parse();
};

#endif // PARSER_H
