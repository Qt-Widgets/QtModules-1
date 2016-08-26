#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QAction;
class QListWidget;
class BaseMenu;
class QTextEdit;
QT_END_NAMESPACE

namespace Ui
{
    class MainWindow;
}

class BaseMenuBar;
class BaseMenu;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void save();
    void print();
    void undo();
    void about();

    void showUtilInfo();
    void showSysInfo();

    void createWindow();

protected:
    void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *event);

private:
    void initPage();
    void addMenuItem(const QString sPluginName, QVariant varMap);
    void loadInstanceMenuItem();

    void createDockWindows();
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createMenuBar();

private:
    Ui::MainWindow *ui;

    BaseMenuBar *menuBar;

    QTextEdit *textEdit;
    QListWidget *customerList;
    QListWidget *paragraphsList;

    BaseMenu *fileMenu;
    BaseMenu *editMenu;
    BaseMenu *viewMenu;
    BaseMenu *helpMenu;
    BaseMenu *sysMenu;

    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    QToolBar *utilToolBar;
    QToolBar *sysToolBar;

    QAction *newLetterAct;
    QAction *saveAct;
    QAction *printAct;
    QAction *undoAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QAction *quitAct;
    QAction *utilAct;
    QAction *sysAct;

};

#endif // MAINWINDOW_H
