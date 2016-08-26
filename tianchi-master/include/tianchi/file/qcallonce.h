/**================================================================
  * 实现单例模式 http://wiki.qt.io/Qt_thread-safe_singleton
  *
  * @ wzguo 2019-09-20
==================================================================*/

#ifndef QCALLONCE_H
#define QCALLONCE_H

#include <QtGlobal>
#include <QAtomicInt>
#include <QMutex>
#include <QWaitCondition>
#include <QThreadStorage>
#include <QThread>

namespace CallOnce
{

    enum ECallOnce
    {
        ECO_REQUEST         = 0,
        ECO_IN_PROGRESS     = 1,
        ECO_FINISHED        = 2
    };

    Q_GLOBAL_STATIC(QThreadStorage<QAtomicInt*>, once_flag)
}

template <class Function>

inline static void qCallOnce(Function func, QBasicAtomicInt& atomFlag)
{
    using namespace CallOnce;
    int protectFlag = 0;

#if QT_VERSION < 0x050000
    protectFlag = atomFlag.fetchAndStoreAcquire(atomFlag);
#elif QT_VERSION >= 0x050000
    protectFlag = atomFlag.fetchAndStoreAcquire(atomFlag.load());
#endif

    if (protectFlag == ECO_FINISHED)
        return;

    if (protectFlag == ECO_REQUEST && atomFlag.testAndSetRelaxed(protectFlag,ECO_IN_PROGRESS))
    {
        func();
        atomFlag.fetchAndStoreRelease(ECO_FINISHED);
    }
    else
    {
        do
        {
            QThread::yieldCurrentThread();
        }
        while(!atomFlag.testAndSetAcquire(ECO_FINISHED, ECO_FINISHED));
    }
}

template <class Function>
inline static void qCallOncePerThread(Function func)
{
    using namespace CallOnce;
    if (!once_flag()->hasLocalData())
    {
        once_flag()->setLocalData(new QAtomicInt(ECO_REQUEST));
        qCallOnce(func, *once_flag()->localData());
    }
}


#endif // QCALLONCE_H

