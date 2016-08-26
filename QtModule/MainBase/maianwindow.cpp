#include "maianwindow.h"
#include "ui_maianwindow.h"

MaianWindow::MaianWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MaianWindow)
{
    ui->setupUi(this);

    this->set
}

MaianWindow::~MaianWindow()
{
    delete ui;
}
