#ifndef MAIANWINDOW_H
#define MAIANWINDOW_H

#include <QWidget>

namespace Ui {
class MaianWindow;
}

class MaianWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MaianWindow(QWidget *parent = 0);
    ~MaianWindow();

private:
    Ui::MaianWindow *ui;
};

#endif // MAIANWINDOW_H
