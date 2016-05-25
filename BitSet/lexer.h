#ifndef LEXER_H
#define LEXER_H

#include <symbols.h>

#include <QList>
#include <QString>
#include <QMap>
#include <QRegExp>

class Lexer
{
private:
    QString expression;
    QMap<QString, symbols::symbol> tokenizationMap;
public:
    Lexer(QString);

    QList<symbols::Symbol> tokenize();

};

#endif // LEXER_H
