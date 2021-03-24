#include "aboutwindow.h"
#include "ui_aboutwindow.h"

#include <QScreen>
#include <QIcon>

aboutWindow::aboutWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::aboutWindow)
{
    ui->setupUi(this);

    //set window title and icon
    this->setWindowTitle("About");
    this->setWindowIcon(QIcon::fromTheme("corevantage"));

    //Center window on screen
    move(QGuiApplication::screens().at(0)->geometry().center() - frameGeometry().center());

    //connect OK to closing window
    connect(ui->okButton, &QDialogButtonBox::accepted, this, &QWidget::close);
}

aboutWindow::~aboutWindow()
{
    delete ui;
}
