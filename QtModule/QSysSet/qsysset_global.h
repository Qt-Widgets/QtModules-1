#ifndef QSYSSET_GLOBAL_H
#define QSYSSET_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QSYSSET_LIBRARY)
#  define QSYSSETSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QSYSSETSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QSYSSET_GLOBAL_H
