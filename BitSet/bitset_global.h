#ifndef BITSET_GLOBAL_H
#define BITSET_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(BITSET_LIBRARY)
#  define BITSETSHARED_EXPORT Q_DECL_EXPORT
#else
#  define BITSETSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // BITSET_GLOBAL_H
