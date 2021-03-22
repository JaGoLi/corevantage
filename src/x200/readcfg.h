#ifndef READCFG_H
#define READCFG_H

#include <QObject>

class readCfg : public QObject
{
    Q_OBJECT
public:
    explicit readCfg(std::string in_file);

    std::string values[19];
    void get_values();

private:
    std::string in_file;
    std::string shrink_string(std::string input);

signals:

};

#endif // READCFG_H
