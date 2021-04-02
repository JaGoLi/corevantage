#ifndef COREVANTAGE_H
#define COREVANTAGE_H

#include <QMainWindow>
#include "readcfg.h"
#include "infowindow.h"
#include "aboutwindow.h"

#include <string>
#include <QStringList>
#include <QComboBox>
#include <QCheckBox>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class corevantage; }
QT_END_NAMESPACE

class corevantage : public QMainWindow
{
    Q_OBJECT

public:
    corevantage(QWidget *parent = nullptr);
    readCfg* init_config;
    QString cfgpath_q;
    std::string cfgpath_s;
    ~corevantage();

    //String lists
    QStringList gfx_options;
    QStringList sata_options;
    QStringList battery_options;
    QStringList boot_options;
    QStringList boot_defaults;
    QStringList debug_options;
    QStringList usb_always_on;

    //maps
    std::map<std::string, int> gfx_map;
    std::map<std::string, int> usbAO_map;

    //windows
    QMessageBox error_win;
    infoWindow info_win;
    aboutWindow about_win;


protected:
    void showEvent(QShowEvent *ev);
    void closeEvent(QCloseEvent *ev);

public slots:
    //closing window
    void closeWindow(int result);
    void saveAndClose();

    //slider connections
    void setVolValue();
    void setRebootValue();

    //read settings
    void getSettings();
    void getFromFile();
    void displaySettings(int result);

    //write settings
    void writeSettings();
    void writeToFile(std::string out_file);


private:
    //read settings
    void textToDisplay(QStringList str_list, std::string in_string, QComboBox* box);
    void checkToDisplay(std::string in_string, QCheckBox* box);
    void hexToSlider(std::string in_string, QSlider* slider);

    //write settings
    void checkToFile(std::fstream& output, std::string precursor, QCheckBox* box);
    void comboToFile(std::fstream& output, std::string precursor, QComboBox* box, std::string successor);
    void sliderToFile(std::fstream& output, std::string precursor, QSlider* slider);
    void lineToFile(std::fstream& output, QLineEdit* line);

    Ui::corevantage *ui;
};
#endif // COREVANTAGE_H
