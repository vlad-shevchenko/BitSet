#ifndef EXPRESSIONSYMBOL_H
#define EXPRESSIONSYMBOL_H

#include <QString>
#include <exception>

namespace symbols {
    class AbstractSymbol
    {
    private:
        QString value;
    public:
        AbstractSymbol(QString value) : value(value) { }

        QString getValue();

        static const QString REG_EXP;
    };

    template <typename T>
    class SymbolFactoryObject
    {
    public:
        SymbolFactoryObject(T);
        T createSymbol(QString);
    };


    class FILE_PATH         : AbstractSymbol {};
    class BITSET            : AbstractSymbol {};
    class NUMBER     		: AbstractSymbol {};
    class NEGATE     		: AbstractSymbol {};
    class AND        		: AbstractSymbol {};
    class OR         		: AbstractSymbol {};
    class XOR        		: AbstractSymbol {};
    class CONCAT     		: AbstractSymbol {};
    class LEFT_SHIFT 		: AbstractSymbol {};
    class RIGHT_SHIFT 		: AbstractSymbol {};
    class OPEN_PAR   		: AbstractSymbol {};
    class CLOSE_PAR 		: AbstractSymbol {};


    class NoFileException : public std::exception {
        const char * what () const throw ()
        {
          return "Specified file is missing or cannot be opened";
        }
    };

    class BitSetExpectedException : public std::exception {
        const char * what () const throw ()
        {
          return "Value after |, & , ^ or + operations must be a BitSet";
        }
    };

    class NumberExpectedException : public std::exception {
        const char * what () const throw ()
        {
          return "Value after << or >> operations must be a number";
        }
    };
}

#endif // EXPRESSIONSYMBOL_H
