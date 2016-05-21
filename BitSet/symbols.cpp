#include "symbols.h"

QString symbols::AbstractSymbol::getValue()
{
    return this->value;
}

template <typename T>
symbols::SymbolFactoryObject::SymbolFactoryObject(T)
{
}

template <typename T>
T symbols::SymbolFactoryObject::createSymbol(QString value)
{
    return new T(value);
}
