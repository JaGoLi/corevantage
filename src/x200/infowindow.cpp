#include "infowindow.h"
#include "ui_infowindow.h"

#include <QScreen>
#include <QIcon>

infoWindow::infoWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::infoWindow)
{
    ui->setupUi(this);

    //set window title and icon
    this->setWindowTitle("Information");
    this->setWindowIcon(QIcon::fromTheme("corevantage"));

    //Center window on screen
    move(QGuiApplication::screens().at(0)->geometry().center() - frameGeometry().center());

    //connect OK to closing window
    connect(ui->closeButton, &QDialogButtonBox::accepted, this, &QWidget::close);
}

infoWindow::~infoWindow()
{
    delete ui;
}
