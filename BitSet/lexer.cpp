#include "lexer.h"

#include <symbols.cpp>
#include <QList>

#include <algorithm>

using namespace symbols;

Lexer::Lexer(QString expression) : expression(expression)
{
    this->tokenizationMap.insert("^file@([^@\\s]+)@",       FILE_PATH);
    this->tokenizationMap.insert("^([10]+)",                BITSET);
    this->tokenizationMap.insert("^\\!",                    NEGATE);
    this->tokenizationMap.insert("^\\&",                    AND);
    this->tokenizationMap.insert("^\\|",                    OR);
    this->tokenizationMap.insert("^\\^",                    XOR);
    this->tokenizationMap.insert("^\\+",                    CONCAT);
    this->tokenizationMap.insert("^\\<\\<\\s*(\\d+)",       LEFT_SHIFT);
    this->tokenizationMap.insert("^\\>\\>\\s*(\\d+)",       RIGHT_SHIFT);
    this->tokenizationMap.insert("^\\(",                    OPEN_PAR);
    this->tokenizationMap.insert("^\\)",                    CLOSE_PAR);
}

QList<Symbol> Lexer::tokenize()
{
    QString exp = this->expression.trimmed();

    QList<QString> regexpStr = this->tokenizationMap.keys();
    QList<QRegExp> regexp;
    std::transform(regexpStr.begin(), regexpStr.end(), std::back_inserter(regexp), [](QString& str) { return QRegExp(str); });

    QList<Symbol> symbols;

    while (exp.length() > 0) {
        int index;
        int matchedLength = -1;
        for (int i = 0; i < regexp.length(); ++i) {
            QRegExp rx = regexp[i];
            if ((index = rx.indexIn(exp)) != -1) {
                matchedLength = rx.matchedLength();
                symbols.push_back(Symbol(this->tokenizationMap[regexpStr[i]], rx.cap(1)));
                break;
            }
        }

        if (matchedLength == -1) {
            throw InvalidExpressionException();
        }

        exp = exp.remove(0, matchedLength).trimmed();
    }
    return symbols;
}
