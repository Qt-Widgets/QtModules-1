#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDebug>
#include <QCloseEvent>
#include <QKeyEvent>
#include <QMenu>
#include <QListWidget>
#include <QDockWidget>

#include <QtWidgets>
#ifndef QT_NO_PRINTDIALOG
#include <QtPrintSupport>
#endif

#include "qshell.h"
#include "../base/qcommand.h"
#include "../base/qconsts.h"
#include "../base/qplugins.h"
#include "../common/qtintf.h"
#include "../custom/baseaction.h"
#include "../custom/iconhelper.h"
#include "../custom/basemenubar.h"
#include "../custom/basemenu.h"
#include "../base/widgetfactory.h"

#include "../tianchi/tianchi.h"

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initPage();

    this->setWindowState(Qt::WindowMaximized);
}

MainWindow::~MainWindow()
{
    shell.destroyed();
    delete ui;
}

void MainWindow::showUtilInfo()
{
    QMessageBox::information(this, QString("warning"), QString("----Qutils.dll  begin-----"));
    qDebug()<< "shell =="<< shell.metaObject()->className();
    shellHelper.execCommand(SYS_MUST_PLUGIN_UTILS, SYS_UTILS_SEND_MESSAGE, "info", "hi, i'm Qutils.dll");
    QMessageBox::information(this, QString("warning"), QString("----Qutils.dll  end-----"));
}

void MainWindow::showSysInfo()
{
    QMessageBox::information(this, QString("warning"), QString("----QSysSet.dll  begin-----"));
    tlog.debug("on_btnSysSet_clicked  begin", __FILE__, __LINE__);
    shellHelper.execCommand(SYS_MUST_PLUGIN_SYSSET, SYS_SYSSET_SEND_MESSAGE, "info", "hi, i'm QSysSet.dll");
    tlog.debug("on_btnSysSet_clicked  end", __FILE__, __LINE__);
    QMessageBox::information(this, QString("warning"), QString("----QSysSet.dll  end-----"));
}

void MainWindow::createWindow()
{
    BaseAction *action = qobject_cast<BaseAction *>(sender());

    int cmdInfo = action->getCmdInfo().toInt();
    QString moduleName = action->getModuleName();

    QVariant vParam;
    vParam.setValue(ui->mdiArea);

    shellHelper.execCommand(moduleName, cmdInfo, vParam, QVariant("0"));
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        this->close();
        return;
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(QString("确认"));
    msgBox.setInformativeText("确认要退出吗？");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    if(QMessageBox::Yes != msgBox.exec())
    {
        event->ignore();
    }
}

void MainWindow::initPage()
{
    textEdit = new QTextEdit;
    //setCentralWidget(textEdit);
    createMenuBar();

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    createDockWindows();

    setWindowTitle(tr("Modules Demo"));

    setUnifiedTitleAndToolBarOnMac(true);

    this->loadInstanceMenuItem();
}

void MainWindow::addMenuItem(const QString sPluginName, QVariant varMap)
{
    QMap<int, WidgetGUICommond *> mapMenu;

    if(varMap.canConvert<QMap<int, WidgetGUICommond *> >())
    {
        mapMenu = varMap.value<QMap<int, WidgetGUICommond *> >();
    }

    if(mapMenu.isEmpty())
    {
        return;
    }

   QMap<int, WidgetGUICommond *>::iterator mapBegin = mapMenu.begin(), mapEnd = mapMenu.end();

    for(; mapBegin != mapEnd; mapBegin++)
    {
        WidgetGUICommond *menuCmd = mapBegin.value();

        if(menuCmd == NULL)
        {
            continue;
        }

        switch (menuCmd->widgetType) {
        case GUI_WIDGET_QMENUBAR:
        {
            break;
        }
        case GUI_WIDGET_QMENU:
        {
            break;
        }

        case GUI_WIDGET_QPUSHBUTTON:
        {
            break;
        }
        case GUI_WIDGET_QTOOLBAR:
        {
            break;
        }
        case GUI_WIDGET_QACTION:
        {
            QString menuName = menuCmd->sParentName.trimmed();
            if(menuName == "")
            {
                return;
            }

            BaseMenu *menuAct = menuBar->findMenu(tr("&%1").arg(menuName));

            if(menuAct == NULL)
            {
                menuAct = menuBar->addMenu(tr("&%1").arg(menuName));
            }

            if(menuCmd->displayInfo != "")
            {
                BaseAction *action = new BaseAction(menuCmd->displayInfo);
                action->setCmdInfo(menuCmd->cmdId);
                action->setModuleName(menuCmd->moduleName);
                action->setToolTip(menuCmd->tipInfo);
                QPixmap  xmap(menuCmd->iconPath);

                iconHelper.setPixmap(action, xmap);
                connect(action, SIGNAL(triggered()), this, SLOT(createWindow()));
                utilToolBar->addAction(action);

                if(menuCmd->orderName != "")
                {
                    menuAct->addAction(menuCmd->orderName, action);
                }
                else
                {
                    menuAct->addAction(action);
                }

            }

            break;
        }

        case GUI_WIDGET_QDOCKWIDGET:
        {
            break;
        }

        case GUI_WIDGET_QSTATUSBAR:
        {
            break;
        }

        case GUI_WIDGET_QWIDGET:
        {
            break;
        }

        default:
            break;
        }
    }
}

void MainWindow::loadInstanceMenuItem()
{
    for(int i=0; i<shell.getHost()->getInstanceCount(); i++)
    {
        LInstanceInfo *instanceInfo = shell.getHost()->getInstanceInfos(i);
        qDebug()<<"--- loading plugin "<< instanceInfo->getInstanceName();

        LPluginType pluginType = instanceInfo->getPluginType();

        qDebug() << "pluginType " << pluginType;

        //获取DLL中需要显示菜单的项
        if(pluginType == ptVisual || pluginType == ptTwinVisual)
        {
            QVariant varMap =  instanceInfo->getInstane()->execCmd(SYS_MAIN_GET_MENU, 0, 0);
            this->addMenuItem(instanceInfo->getInstanceName(), varMap);
        }
    }
}

void MainWindow::createDockWindows()
{
    QDockWidget *dock = new QDockWidget(tr("Customers"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    customerList = new QListWidget(dock);
    customerList->addItems(QStringList()<< "This is Customers QDockWidget");
    dock->setWidget(customerList);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());

    dock = new QDockWidget(tr("Paragraphs"), this);
    paragraphsList = new QListWidget(dock);
    paragraphsList->addItems(QStringList()<< "This is Paragraphs QDockWidget");
    dock->setWidget(paragraphsList);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());
}


void MainWindow::print()
{
#ifndef QT_NO_PRINTDIALOG
    QTextDocument *document = textEdit->document();
    QPrinter printer;

    QPrintDialog dlg(&printer, this);
    if (dlg.exec() != QDialog::Accepted) {
        return;
    }

    document->print(&printer);
    statusBar()->showMessage(tr("Ready"), 2000);
#endif
}

void MainWindow::save()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                        tr("Choose a file name"), ".",
                        tr("HTML (*.html *.htm)"));
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Modules Demo"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << textEdit->toHtml();
    QApplication::restoreOverrideCursor();

    statusBar()->showMessage(tr("Saved '%1'").arg(fileName), 2000);
}

void MainWindow::undo()
{
    QTextDocument *document = textEdit->document();
    document->undo();
}

void MainWindow::about()
{
   QMessageBox::about(this, tr("About Modules Demos"),
            tr("The <b>Dock Widgets</b> example demonstrates how to "
               "use Qt's dock widgets. You can enter your own text, "
               "click a customer to add a customer name and "
               "address, and click standard paragraphs to add them."));
}

void MainWindow::createMenuBar()
{
    menuBar = new BaseMenuBar(this);
    this->setMenuBar(menuBar);
}

void MainWindow::createActions()
{
    //QString spath = QString("%1/../../Custom/images/%2").arg(QApplication::applicationDirPath());

    newLetterAct = new QAction(QIcon(":/images/new.png"), tr("&New Letter"), this);
    newLetterAct->setShortcuts(QKeySequence::New);
    newLetterAct->setStatusTip(tr("Create a new form letter"));
    //connect(newLetterAct, SIGNAL(triggered()), this, SLOT(newLetter()));

    saveAct = new QAction(QIcon(":/images/save.png"), tr("&Save..."), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the current form letter"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    printAct = new QAction(QIcon(":/images/print.png"), tr("&Print..."), this);
    printAct->setShortcuts(QKeySequence::Print);
    printAct->setStatusTip(tr("Print the current form letter"));
    connect(printAct, SIGNAL(triggered()), this, SLOT(print()));

    undoAct = new QAction(QIcon(":/images/undo.png"), tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo the last editing action"));
    connect(undoAct, SIGNAL(triggered()), this, SLOT(undo()));

    quitAct = new QAction(tr("&Quit"), this);
    quitAct->setShortcuts(QKeySequence::Quit);
    quitAct->setStatusTip(tr("Quit the application"));
    connect(quitAct, SIGNAL(triggered()), this, SLOT(close()));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    utilAct = new QAction(QIcon(":/images/info.png"), tr("&Info"), this);
    utilAct->setStatusTip(tr("Show the Util.dll's function"));
    connect(utilAct, SIGNAL(triggered()), this, SLOT(showUtilInfo()));

    sysAct = new QAction(QIcon(":/images/cut.png"), tr("&Info"), this);
    sysAct->setStatusTip(tr("Show the Systt.dll's function"));
    connect(sysAct, SIGNAL(triggered()), this, SLOT(showSysInfo()));

}

void MainWindow::createMenus()
{
    sysMenu = menuBar->addMenu(tr("&System"));
    sysMenu->addAction(quitAct);

    fileMenu = menuBar->addMenu(tr("&File"));
    fileMenu->addAction(newLetterAct);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAct);
    fileMenu->addAction(printAct);

    editMenu = menuBar->addMenu(tr("&Edit"));
    editMenu->addAction(undoAct);

    viewMenu = menuBar->addMenu(tr("&View"));

    menuBar->addSeparator();

    helpMenu = menuBar->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(newLetterAct);
    fileToolBar->addAction(saveAct);
    fileToolBar->addAction(printAct);

    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(undoAct);

    utilToolBar = this->addToolBar(tr("Utils.dll"));
    utilToolBar->addAction(utilAct);

    sysToolBar= this->addToolBar(tr("Systt.dll"));
    sysToolBar->addAction(sysAct);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

