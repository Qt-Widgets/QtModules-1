#ifndef QGRAPHS_GLOBAL_H
#define QGRAPHS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QGRAPHS_LIBRARY)
#  define QGRAPHSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QGRAPHSSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QGRAPHS_GLOBAL_H
