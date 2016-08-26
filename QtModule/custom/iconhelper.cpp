#include "iconhelper.h"
#include <QDebug>

IconHelper::IconHelper(QObject *parent)
    : QObject(parent)
{
    initHelper();
}

IconHelper::~IconHelper()
{

}

void IconHelper::setIcon(QLabel *label, const QChar &chr, int size)
{
    iconFont.setPointSize(size);
    label->setFont(iconFont);
    label->setText(chr);
}

void IconHelper::setIcon(QPushButton *btn, const QChar &chr, int size)
{
    iconFont.setPointSize(size);
    btn->setFont(iconFont);
    btn->setText(chr);
}

void IconHelper::setIcon(QAction *action, const QChar &chr, int size)
{
    iconFont.setPointSize(size);
    action->setFont(iconFont);
    action->setText(chr);
}

void IconHelper::setIcon(QMenu *menu, const QChar &chr, int size)
{
    iconFont.setPointSize(size);
    menu->setFont(iconFont);
    menu->setTitle(chr);
}

void IconHelper::setPixmap(QLabel *label, const QPixmap &xmap, int size)
{
    label->setMaximumSize(size, size);
    label->setScaledContents(true);

    if(!xmap.isNull()){
        label->setPixmap(xmap);
    }
}

void IconHelper::setPixmap(QPushButton *btn, const QPixmap &xmap, int size)
{
    btn->setIconSize(QSize(size, size));

    if(!xmap.isNull()){
        btn->setIcon(QIcon(xmap));
    }
}

void IconHelper::setPixmap(QAction *action, const QPixmap &xmap)
{
    if(!xmap.isNull()){
        action->setIcon(QIcon(xmap));
    }

}

void IconHelper::setPixmap(QMenu *menu, const QPixmap &xmap)
{
    if(!xmap.isNull()){
        menu->setIcon(QIcon(xmap));
    }

}

void IconHelper::initHelper()
{
    QString spath = QString(":/other/fontawesome-webfont.ttf");
    int fontId = QFontDatabase::addApplicationFont(spath);

    if(fontId >= 0) {
        QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
        iconFont = QFont(fontName);
    }
}

