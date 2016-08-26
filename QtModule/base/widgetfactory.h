#ifndef WIDGETFACTORY_H
#define WIDGETFACTORY_H

#include <QByteArray>
#include <QMetaObject>
#include <QHash>
#include <QWidget>
#include <QDebug>

class WidgetFactory
{
public:
    template<typename T>
    static void registerWidget()
    {
        qDebug()<<"staticMetaObject == "<< T::staticMetaObject.className();
        constructors().insert( T::staticMetaObject.className(), &constructorHelper<T> );
        qDebug()<<"1-- WidgetFactory constructors() == "<<constructors()<<"constructors().count() == " << constructors().count();
    }

    static QWidget* createWidget( const QByteArray& className, QWidget *parent = NULL )
    {
        qDebug()<<"2-- WidgetFactory constructors() == "<<constructors()<<"constructors().count() == " << constructors().count();
        Constructor constructor  = constructors().value( className.trimmed().constData() );

        if ( constructor == NULL )
            return NULL;

        return (*constructor)( parent );
    }

private:
    typedef QWidget* (*Constructor)( QWidget* parent );

    template<typename T>
    static QWidget* constructorHelper( QWidget* parent )
    {
        return new T( parent );
    }

    static QHash<QByteArray, Constructor>& constructors()
    {
        static QHash<QByteArray, Constructor> instance;
        return instance;
    }
};


#endif // WIDGETFACTORY_H

