/**
  * 图标助理类
  *
  * @author wzguo 2015-09-30
  */


#ifndef ICONHELPER_H
#define ICONHELPER_H

#include <QObject>
#include <QLabel>
#include <QPushButton>
#include <QAction>
#include <QMenu>
#include <QFont>
#include <QFontDatabase>
#include <QPixmap>

#include "../Base/qsingleton.h"

#define iconHelper Singleton<IconHelper>::instance()

class IconHelper : public QObject
{
    Q_OBJECT

public:
    explicit IconHelper(QObject *parent = 0);
    ~IconHelper();

    void setIcon(QLabel *label,  const QChar &chr, int size = 10);
    void setIcon(QPushButton *btn, const QChar &chr, int size = 10);
    void setIcon(QAction *action, const QChar &chr, int size = 10);
    void setIcon(QMenu *menu, const QChar &chr, int size = 10);

    void setPixmap(QLabel *label, const QPixmap &xmap, int size = 10);
    void setPixmap(QPushButton *btn, const QPixmap &xmap, int size = 10);
    void setPixmap(QAction *action, const QPixmap &xmap);
    void setPixmap(QMenu *menu, const QPixmap &xmap);

private:
    void initHelper();

private:
    QFont iconFont;
};

#endif // ICONHELPER_H
