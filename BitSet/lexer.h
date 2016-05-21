#ifndef LEXER_H
#define LEXER_H

#include <symbols.h>

#include <QList>
#include <QString>
#include <QMap>

class Lexer
{
private:
    QString expression;
    QMap<symbols::AbstractSymbol, symbols::SymbolFactoryObject> symbolsMap;
public:
    Lexer(QString);

    QList<symbols::AbstractSymbol> tokenize();

};

#endif // LEXER_H
