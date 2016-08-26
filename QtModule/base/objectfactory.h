/**=================================================
  * 根据类名获取对象（元对象反射）
  * 原文地址：http://www.mimec.org/node/350
  * author: wzguo 2015-09-24
  ================================================= */

#include <QByteArray>
#include <QMetaObject>
#include <QHash>
#include <QDebug>

#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

class ObjectFactory
{
public:
    template<typename T>
    static void registerObject()
    {
        constructors().insert( T::staticMetaObject.className(), &constructorHelper<T> );
        qDebug() <<"1-- ObjectFactory constructors() = "<< constructors()<<"constructors().count()"<<constructors().count();
    }

    static QObject* createObject( const QByteArray& className, QObject* parent = NULL )
    {
        qDebug() <<"2-- ObjectFactory constructors() = "<< constructors()<<"constructors().count()"<<constructors().count();
        Constructor constructor = constructors().value( className.trimmed().constData() );

        if ( constructor == NULL )
            return NULL;

        return (*constructor)( parent );
    }

private:
    typedef QObject* (*Constructor)( QObject* parent );

    template<typename T>
    static QObject* constructorHelper( QObject* parent )
    {
        return new T( parent );
    }

    static QHash<QByteArray, Constructor>& constructors()
    {
        static QHash<QByteArray, Constructor> instance;
        return instance;
    }
};


#endif // OBJECTFACTORY_H

