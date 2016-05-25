#ifndef EXPRESSIONSYMBOL_H
#define EXPRESSIONSYMBOL_H

#include <QString>
#include <QRegExp>
#include <exception>

namespace symbols {
//    class AbstractSymbol
//    {
//    protected:
//        QString value;
//    public:
//        AbstractSymbol() : value("") {}
//        AbstractSymbol(QString value) : value(value) { }

//        QString getValue();
//    };

//    template<class T>
//    class SymbolFactoryObject
//    {
//    public:
//        SymbolFactoryObject();
//        SymbolFactoryObject(T);
//        T createSymbol(QString);
//    };


//    class FILE_PATH     : public AbstractSymbol {};
//    class BITSET        : public AbstractSymbol {};
//    class NUMBER    	: public AbstractSymbol {};
//    class NEGATE    	: public AbstractSymbol {};
//    class AND       	: public AbstractSymbol {};
//    class OR        	: public AbstractSymbol {};
//    class XOR           : public AbstractSymbol {};
//    class CONCAT    	: public AbstractSymbol {};
//    class LEFT_SHIFT    : public AbstractSymbol {};
//    class RIGHT_SHIFT   : public AbstractSymbol {};
//    class OPEN_PAR  	: public AbstractSymbol {};
//    class CLOSE_PAR 	: public AbstractSymbol {};

    enum symbol {FILE_PATH, BITSET, NEGATE, AND, OR, XOR, CONCAT, LEFT_SHIFT, RIGHT_SHIFT, OPEN_PAR, CLOSE_PAR, EPSILON};
    class Symbol {
    private:
        symbol sym;
        QString _value;
    public:
        Symbol() { }
        Symbol(symbol sym, QString value) : sym(sym), _value(value) { }

        QString value() { return _value; }
        bool is(symbol another) { return sym == another; }
        symbol type() { return sym; }
    };

    class BaseException: public std::exception {
    protected:
        QString message_;
    public:
        BaseException() : message_("") { }
        BaseException(const QString& message) : message_(message) { }
        virtual const char* what() const throw() {
            return message_.toStdString().c_str();
        }
    };

    class InvalidExpressionException : public BaseException {
    public:
        InvalidExpressionException() : BaseException("Expression syntax is wrong") { }
        InvalidExpressionException(const QString& message) : BaseException(message) { }
    };

    class NoFileException : public BaseException {
    public:
        NoFileException() : BaseException("Specified file is missing or cannot be opened") { }
        NoFileException(const QString& message) : BaseException(message) { }
    };

    class BitSetExpectedException : public BaseException {
    public:
        BitSetExpectedException() : BaseException("Value after |, & , ^ or + operations must be a BitSet") { }
        BitSetExpectedException(const QString& message) : BaseException(message) { }
    };

    class NumberExpectedException : public BaseException {
    public:
        NumberExpectedException() : BaseException("Value after << or >> operations must be a number") { }
        NumberExpectedException(const QString& message) : BaseException(message) { }
    };
}

#endif // EXPRESSIONSYMBOL_H
