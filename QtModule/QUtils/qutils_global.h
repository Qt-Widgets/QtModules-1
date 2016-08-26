#ifndef QUTILS_GLOBAL_H
#define QUTILS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QUTILS_LIBRARY)
#  define QUTILSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QUTILSSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QUTILS_GLOBAL_H
