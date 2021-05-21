#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QWidget>

namespace Ui {
class aboutWindow;
}

class aboutWindow : public QWidget
{
    Q_OBJECT

public:
    explicit aboutWindow(QWidget *parent = nullptr);
    ~aboutWindow();

private:
    Ui::aboutWindow *ui;
};

#endif // ABOUTWINDOW_H
