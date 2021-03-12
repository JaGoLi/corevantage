#include "corevantage.h"
#include "./ui_corevantage.h"
#include <QDebug>

#include <iostream>
#include <fstream>
#include <QPushButton>
#include <QScreen>
#include <QProcess>
#include <QDir>
#include <QFileDialog>

corevantage::corevantage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::corevantage)
{
    ui->setupUi(this);

    //construct maps

    //gfx_map
    gfx_map["32M"] = 0;
    gfx_map["48M"] = 1;
    gfx_map["64M"] = 2;
    gfx_map["98M"] = 3;
    gfx_map["128M"] = 4;
    gfx_map["160M"] = 5;
    gfx_map["224M"] = 6;
    gfx_map["256M"] = 7;
    gfx_map["352M"] = 8;

    //device_map
    device_map["0x0"] = 0;
    device_map["0x1"] = 1;
    device_map["0x2"] = 2;

    //set text max length
    ui->devicesLine->setMaxLength(64);

    //add menu items

    //gfx_uma_size
    gfx_options << "32" << "48" << "64" << "96" << "128" << "160" << "224" << "256" << "352";
    ui->gfxCombo->addItems(gfx_options);

    //sata_mode
    sata_options << "AHCI" << "Compatible" ;
    ui->sataCombo->addItems(sata_options);

    //first_battery
    battery_options << "Primary" << "Secondary";
    ui->batteryCombo->addItems(battery_options);

    //boot_option
    boot_options << "Normal" << "Fallback";
    ui->bootCombo->addItems(boot_options);

    //boot_default
    boot_defaults << "1st" << "2nd" << "3rd";
    ui->defaultCombo->addItems(boot_defaults);

    //debug_level
    debug_options << "Spew" << "Debug" << "Info" << "Notice" << "Warning" << "Error" << "Critical" << "Alert" << "Emergency";
    ui->debugCombo->addItems(debug_options);


    //Center window on screen
    move(QGuiApplication::screens().at(0)->geometry().center() - frameGeometry().center());

    //slider connections
    connect(ui->volumeSlider, &QSlider::valueChanged, this, &corevantage::setVolValue);
    connect(ui->rebootSlider, &QSlider::valueChanged, this, &corevantage::setRebootValue);

    //read and save to file connections
    connect(ui->actionImport_from_File, &QAction::triggered, this, &corevantage::getFromFile);
    connect(ui->actionSave_to_File, &QAction::triggered, this, &corevantage::writeSettings);


    //close connections
    connect(ui->confirmBox, &QDialogButtonBox::rejected, this, &corevantage::closeWindow);
    connect(ui->confirmBox, &QDialogButtonBox::accepted, this, &corevantage::saveAndClose);

    connect(ui->actionExit, &QAction::triggered, this, &corevantage::closeWindow);
    connect(ui->actionSave_and_Exit, &QAction::triggered, this, &corevantage::saveAndClose);
}

corevantage::~corevantage()
{
    delete ui;
}

//OVERRIDES
void corevantage::showEvent(QShowEvent *ev)
{
    QMainWindow::showEvent(ev);
    getSettings();
}

//SLOTS

void corevantage::closeWindow() {
    this->close();
}

void corevantage::saveAndClose() {
    writeToFile(cfgpath_s);
    this->close();
}

void corevantage::setRebootValue() {
     ui->rebootValue->setText(QString::number(ui->rebootSlider->value()));
}

void corevantage::setVolValue() {
     ui->volumeValue->setText(QString::number(ui->volumeSlider->value()));
 }

void corevantage::getFromFile(){
    QFileDialog diag(this, "Select File", QDir::homePath(), "Coreboot Configuration Files (*.cfg)");
    diag.setDefaultSuffix(".cfg");
    diag.exec();
    QString user_file = diag.selectedFiles().constFirst();
    std::string selected_file = user_file.toUtf8().constData();
    if (!selected_file.empty()) {
        delete init_config;
        init_config = new readCfg(selected_file);
    }
    displaySettings(0);
}

void corevantage::writeSettings() {
    QFileDialog diag(this, "Enter File to Save", QDir::homePath(), "Coreboot Configuration Files (*.cfg)");
    diag.setDefaultSuffix(".cfg");
    diag.exec();
    QString user_file = diag.selectedFiles().constFirst();
    std::string selected_file = user_file.toUtf8().constData();
    if (!selected_file.empty()) {
        writeToFile(selected_file);
    }
}

void corevantage::getSettings() {
    //Program Details
    QProcess* nvram_a = new QProcess(this);
    QString sudo_prog = "pkexec";
    QStringList args = {"nvramtool", "-a"};

    //Configuration directory
    QString user_dir = QDir::homePath() + "/.config/corevantage/";
    if (!QDir(user_dir).exists()) {
        QDir().mkdir(user_dir);
    }

    //Config file location
    QString cfgpath_q = user_dir + "nvramtool.cfg";
    cfgpath_s = cfgpath_q.toUtf8().constData();
    nvram_a->setStandardOutputFile(cfgpath_q);

    connect(nvram_a, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished), this, [=](int num){displaySettings(num);});

    //start
    init_config = new readCfg(cfgpath_s);
    nvram_a->start(sudo_prog, args);
}

void corevantage::textToDisplay(QStringList str_list, std::string in_string, QComboBox* box) {
    QString q_string = QString::fromStdString(in_string);
    int index = str_list.indexOf(q_string, 0);
    if (index != -1) {
        box->setCurrentIndex(index);
    }
}

void corevantage::checkToDisplay(std::string in_string, QCheckBox* box) {
    if (in_string.compare("Enable") == 0) {
        box->setCheckState(Qt::Checked);
    }
    else {
        box->setCheckState(Qt::Unchecked);
    }
}

void corevantage::hexToSlider(std::string in_string, QSlider* slider) {
    int init_str_size = in_string.size();
    if (init_str_size >= 3) {
        std::string str_num = in_string.substr(2, init_str_size - 2);
        int str_int = std::stoi(str_num);

        slider->setValue(str_int);
    }
}

void corevantage::displaySettings(int result) {
    std::string result_num = std::to_string(result);
    init_config->get_values();


    //display text combos
    ui->gfxCombo->setCurrentIndex(gfx_map[init_config->values[18]]);
    ui->defaultCombo->setCurrentIndex(device_map[init_config->values[17]]);
    textToDisplay(sata_options, init_config->values[3], ui->sataCombo);
    textToDisplay(battery_options, init_config->values[5], ui->batteryCombo);
    textToDisplay(boot_options, init_config->values[0], ui->bootCombo);
    textToDisplay(debug_options, init_config->values[2], ui->debugCombo);

    //display slider values
    hexToSlider(init_config->values[10], ui->volumeSlider);
    hexToSlider(init_config->values[1], ui->rebootSlider);

    //display checkbox states
    checkToDisplay(init_config->values[8], ui->wlanBox);
    checkToDisplay(init_config->values[6], ui->btBox);
    checkToDisplay(init_config->values[7], ui->wwanBox);
    checkToDisplay(init_config->values[9], ui->tpBox);
    checkToDisplay(init_config->values[11], ui->swapBox);
    checkToDisplay(init_config->values[12], ui->stickyBox);
    checkToDisplay(init_config->values[13], ui->pmbeepBox);
    checkToDisplay(init_config->values[14], ui->lbbeepBox);
    checkToDisplay(init_config->values[4], ui->failBox);
    checkToDisplay(init_config->values[15], ui->uwbBox);

    //set device list text
    ui->devicesLine->setText(QString::fromStdString(init_config->values[16]));
}

void corevantage::comboToFile(std::fstream& output, std::string precursor, QComboBox* box, std::string successor = "") {
    std::string box_val = box->currentText().toUtf8().constData();
    output << precursor + box_val + successor << std::endl;
}

void corevantage::sliderToFile(std::fstream& output, std::string precursor, QSlider* slider) {
    std::string slider_val = std::to_string(slider->value());
    output << precursor + slider_val << std::endl;
}

void corevantage::checkToFile(std::fstream& output, std::string precursor, QCheckBox* box) {
    std::string status;
    if (box->isChecked()) {
        status = "Enable";
    }
    else {
        status = "Disable";
    }
    output << precursor + status << std::endl;
}

void corevantage::lineToFile(std::fstream& output, QLineEdit* line) {
        //handle special case boot_devices string
        if (!line->text().trimmed().isEmpty()) {
            output << "boot_devices = " << line->text().toUtf8().constData() << std::endl;
        }
        else {
            output << "boot_devices = 0x0" << std::endl;
        }
}

void corevantage::writeToFile(std::string out_file) {
    //clear file
    remove(out_file.c_str());

    //setup file for writing
    std::fstream out_stream;
    out_stream.open(out_file, std::ios_base::out);

    //start writing
    if(out_stream.is_open()) {

        comboToFile(out_stream, "boot_option = ", ui->bootCombo);
        sliderToFile(out_stream, "reboot_counter = 0x", ui->rebootSlider);
        comboToFile(out_stream, "debug_level = ", ui->debugCombo);
        comboToFile(out_stream, "sata_mode = ", ui->sataCombo);
        checkToFile(out_stream, "power_on_after_fail = ", ui->failBox);
        comboToFile(out_stream, "first_battery = ", ui->batteryCombo);
        checkToFile(out_stream, "bluetooth = ", ui->btBox);
        checkToFile(out_stream, "wwan = ", ui->wwanBox);
        checkToFile(out_stream, "wlan = ", ui->wlanBox);
        checkToFile(out_stream, "trackpoint = ", ui->tpBox);
        sliderToFile(out_stream, "volume = 0x", ui->volumeSlider);
        checkToFile(out_stream, "fn_ctrl_swap = ", ui->swapBox);
        checkToFile(out_stream, "sticky_fn = ", ui->stickyBox);
        checkToFile(out_stream, "power_management_beeps = ", ui->pmbeepBox);
        checkToFile(out_stream, "low_battery_beep = ", ui->lbbeepBox);
        checkToFile(out_stream, "uwb = ", ui->uwbBox);
        lineToFile(out_stream, ui->devicesLine);
        out_stream << "boot_default = 0x" << std::to_string(ui->defaultCombo->currentIndex()) << std::endl;
        comboToFile(out_stream, "gfx_uma_size = ", ui->gfxCombo, "M");

    }

    else {
        qDebug() << "Failed to write to file";
    }

    out_stream.close();
}
