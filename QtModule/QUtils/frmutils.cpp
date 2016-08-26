#include "frmutils.h"
#include "ui_frmutils.h"
#include <QDebug>
#include <QMessageBox>
#include <QApplication>
#include "../tianchi/tianchi.h"

FrmUtils::FrmUtils(QWidget *parent)
    :QWidget(parent),
    ui(new Ui::FrmUtils)
{
    ui->setupUi(this);

    tlog.error("FrmUtils::FrmUtils init begin");
    initPage();
    tlog.error("FrmUtils::FrmUtils init end");
}

FrmUtils::~FrmUtils()
{
    delete ui;
}

void FrmUtils::on_btnOk_clicked()
{
    QMessageBox::information(this, QString("提示"), QString("this myself info，哈哈哈"));
}

void FrmUtils::on_btnCancel_clicked()
{
    ((QWidget *)this->parent())->close();
}

void FrmUtils::initPage()
{
    this->setWindowTitle("个人信息");

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setAlternatingRowColors(false);
    ui->tableWidget->setCornerButtonEnabled(false);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableWidget->verticalHeader()->setDefaultSectionSize(20);
    ui->tableWidget->verticalHeader()->setVisible(false);

    ui->tableWidget->horizontalHeader()->setHighlightSections(false);
    ui->tableWidget->horizontalHeader()->setFixedHeight(20);
    ui->tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft| Qt::AlignCenter);

    ui->tableWidget->setObjectName("tableWidget");
}
