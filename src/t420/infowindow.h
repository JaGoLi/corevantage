#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include <QWidget>

namespace Ui {
class infoWindow;
}

class infoWindow : public QWidget
{
    Q_OBJECT

public:
    explicit infoWindow(QWidget *parent = nullptr);
    ~infoWindow();

private:
    Ui::infoWindow *ui;
};

#endif // INFOWINDOW_H
