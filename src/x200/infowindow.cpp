#include "infowindow.h"
#include "ui_infowindow.h"

#include <QScreen>

infoWindow::infoWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::infoWindow)
{
    ui->setupUi(this);

    //Center window on screen
    move(QGuiApplication::screens().at(0)->geometry().center() - frameGeometry().center());

    //connect OK to closing window
    connect(ui->closeButton, &QDialogButtonBox::accepted, this, &QWidget::close);
}

infoWindow::~infoWindow()
{
    delete ui;
}
