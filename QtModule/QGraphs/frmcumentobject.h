#ifndef FRMCUMENTOBJECT_H
#define FRMCUMENTOBJECT_H

#include <QWidget>
#include <QTextDocument>
#include <QFileDialog>
#include "qcpdocumentobject.h"

namespace Ui {
class FrmCumentObject;
}

class FrmCumentObject : public QWidget
{
    Q_OBJECT

public:
    explicit FrmCumentObject(QWidget *parent = 0);
    ~FrmCumentObject();

  private slots:
    void on_btnInsertPlot_clicked();
    void on_btnSaveDoc_clicked();

private:
    void setupPlot();
    void initFrm();

private:
    Ui::FrmCumentObject *ui;
};

#endif // FRMCUMENTOBJECT_H
