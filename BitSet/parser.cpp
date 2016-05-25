#include "parser.h"

#include "bitset.h"

using namespace symbols;

void Parser::goNext()
{
    if (this->tokens.size() > 0) {
        this->tokens.pop_front();
        this->cur = this->next;
        if (this->tokens.size() > 1) {
            this->next = this->tokens[1];
        } else {
            this->next = Symbol(EPSILON, "");
        }
    } else {
        this->cur = Symbol(EPSILON, "");
        this->next = Symbol(EPSILON, "");
    }
}

BitSet Parser::parseConcat()
{
    BitSet result = parseShift();
    while (cur.is(CONCAT)) {
        goNext();
        result += parseShift();
    }
    return result;
}

BitSet Parser::parseShift()
{
    BitSet result = parseXor();
    while (cur.is(LEFT_SHIFT) || cur.is(RIGHT_SHIFT)) {
        bool ok;
        int shift = cur.value().toInt(&ok);
        if (!ok) {
            throw NumberExpectedException("Expercted number after shift operator");
        }
        if (shift < 0) {
            throw NumberExpectedException("Cannot shift on negative offset");
        }
        if (cur.is(LEFT_SHIFT)) {
            result <<= shift;
        } else if (cur.is(RIGHT_SHIFT)) {
            result >>= shift;
        }
        goNext();
    }
    return result;
}

BitSet Parser::parseXor()
{
    BitSet result = parseOr();
    while (cur.is(XOR)) {
        goNext();
        result ^= parseOr();
        goNext();
    }
    return result;
}

BitSet Parser::parseOr()
{
    BitSet result = parseAnd();
    while (cur.is(OR)) {
        goNext();
        result |= parseAnd();
        goNext();
    }
    return result;
}

BitSet Parser::parseAnd()
{
    BitSet result = parseNegate();
    while (cur.is(AND)) {
        goNext();
        result &= parseNegate();
        goNext();
    }
    return result;
}

BitSet Parser::parseNegate()
{
    bool negate = false;
    if (cur.is(NEGATE)) {
        goNext();
        negate = true;
    }
    BitSet result = parseTerm();
    return negate ? !result : result;
}

BitSet Parser::parseTerm()
{
    BitSet result;
    if (cur.is(FILE_PATH)) {
        // TODO vlad: open and read file
        result = BitSet("");
    } else if (cur.is(BITSET)) {
        result = BitSet(cur.value());
        goNext();
    } else if (cur.is(OPEN_PAR)) {
        goNext();
        result = parseConcat();
        goNext();
    } else {
        throw BaseException("Expected file or bitset or `(`");
    }
    return result;
}

Parser::Parser()
{

}

Parser::Parser(QList<symbols::Symbol>& tokens) : tokens(tokens)
{
    if (tokens.size() == 0) {
        this->cur = Symbol(EPSILON, "");
        this->next = Symbol(EPSILON, "");
    } else if (tokens.size() == 1) {
        this->cur = tokens[0];
        this->next = Symbol(EPSILON, "");
    } else {
        this->cur = tokens[0];
        this->next = tokens[1];
    }
}

BitSet Parser::parse()
{
    BitSet result = parseConcat();
    if (!this->cur.is(EPSILON)) {
        throw InvalidExpressionException("Unexpected symbol after the end of the expression: " + this->cur.type());
    }
    return result;
}
