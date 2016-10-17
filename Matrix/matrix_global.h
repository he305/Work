#ifndef MATRIX_GLOBAL_H
#define MATRIX_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MATRIX_LIBRARY)
#  define MATRIXSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MATRIXSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MATRIX_GLOBAL_H
