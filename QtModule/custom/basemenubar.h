#ifndef BASEMENUBAR_H
#define BASEMENUBAR_H

/**
  * 自定义 MenuBar 类，便于QMenu的搜索
  *
  * @author wzguo 2015-11-03
  */

#include <QMenuBar>

class BaseMenu;

class BaseMenuBar : public QMenuBar
{

public:
    BaseMenuBar(QWidget * parent = 0);

    ~BaseMenuBar();


    QAction *addMenu(BaseMenu *menu) Q_DECL_OVERRIDE;
    BaseMenu *addMenu(const QString &title) Q_DECL_OVERRIDE;
    BaseMenu *addMenu(const QIcon &icon, const QString &title) Q_DECL_OVERRIDE;

    BaseMenu *findMenu(BaseMenu *menu);
    BaseMenu *findMenu(const QString &title);

private:
    void initMenuBar();

private:
    QList<BaseMenu *> menuList;
};

#endif // BASEMENUBAR_H
