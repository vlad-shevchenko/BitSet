#ifndef PARSER_H
#define PARSER_H

#include <symbols.h>
#include <bitset.h>

#include <QString>

class Parser
{
private:
    QList<symbols::Symbol> tokens;

    symbols::Symbol cur;
    symbols::Symbol next;

    void goNext();

    BitSet parseConcat();
    BitSet parseShift();
    BitSet parseXor();
    BitSet parseAnd();
    BitSet parseOr();
    BitSet parseNegate();
    BitSet parseTerm();

public:
    Parser();
    Parser(QList<symbols::Symbol>& tokens);
    BitSet parse();
};

#endif // PARSER_H
