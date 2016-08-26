#ifndef FRMUTILS_H
#define FRMUTILS_H

#include <QWidget>

namespace Ui {
class FrmUtils;
}

class FrmUtils : public QWidget
{
    Q_OBJECT

public:
    explicit FrmUtils(QWidget *parent = 0);

    ~FrmUtils();

private slots:
    void on_btnOk_clicked();
    void on_btnCancel_clicked();

private:
    void initPage();

private:
    Ui::FrmUtils *ui;
};

#endif // FRMUTILS_H
