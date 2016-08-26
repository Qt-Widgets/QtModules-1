#ifndef BASEMENU_H
#define BASEMENU_H

#include <QMenu>

/**
 * @brief BaseMenu
 * 自定义Menu类，支持Action查找、按Action名称插入和Action的序号插入
 *
 * @author wzguo 2015-11-04
 */


class BaseMenu : public QMenu
{
public:
    BaseMenu(QWidget *parent = 0);
    BaseMenu(const QString &title, QWidget *parent = 0);
    BaseMenu(QMenu *menu, QWidget *parent = 0);

    ~BaseMenu();

    QAction *addAction(const QString &text) Q_DECL_OVERRIDE;
    QAction *addAction(const QIcon &icon, const QString &text) Q_DECL_OVERRIDE;
    QAction *addAction(const QString &text, const QObject *receiver, const char *member, const QKeySequence &shortcut = 0) Q_DECL_OVERRIDE;
    QAction *addAction(const QIcon &icon, const QString &text, const QObject *receiver, const char *member, const QKeySequence &shortcut = 0) Q_DECL_OVERRIDE;
    void addAction(QAction *action) Q_DECL_OVERRIDE;

    QAction *addMenu(QMenu *menu) Q_DECL_OVERRIDE;
    QAction *addSection(const QString &text) Q_DECL_OVERRIDE;
    QAction *addSection(const QIcon &icon, const QString &text) Q_DECL_OVERRIDE;


    QAction *addAction(const QString &beforeTitle, const QString &text);
    QAction *addAction(const QString &beforeTitle, QAction *action);
    QAction *addAction(int index, const QString &text);
    QAction *addAction(int index, QAction *action);

    QAction *findAction(QAction *action);
    QAction *findAction(const QString &text);

private:
    void initMenu();

private:
    QMap<int, QAction *> mapAction;

    QMenu *mmenu;

};

#endif // BASEMENU_H
