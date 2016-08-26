/**================================================================
  * 实现单例模式 http://wiki.qt.io/Qt_thread-safe_singleton
  *
  * @ wzguo 2019-09-20
==================================================================*/

#ifndef QSINGLETON_H
#define QSINGLETON_H

#include <QtGlobal>
#include <QScopedPointer>
#include "qcallonce.h"

template <class T>

class Singleton
{

public:
    static T& instance()
    {
        qCallOnce(init, atomicFlag);
        return *scopePointer;
    }

    static void init()
    {
        scopePointer.reset(new T);
    }

private:
    Singleton() {};
    ~Singleton() {};

    Q_DISABLE_COPY(Singleton)

    static QScopedPointer<T> scopePointer;
    static QBasicAtomicInt atomicFlag;
};

template<class T> QScopedPointer<T> Singleton<T>::scopePointer(0);
template<class T> QBasicAtomicInt Singleton<T>::atomicFlag = Q_BASIC_ATOMIC_INITIALIZER(CallOnce::ECO_REQUEST);

#endif // QSINGLETON_H

