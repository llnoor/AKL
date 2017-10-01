#ifndef CLASS_TEMP_H
#define CLASS_TEMP_H

#include <QString>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QDir>


class class_temp
{
public:
    class_temp();
    void open_new_file(QString );
    float get_temp(QString);
private:
    int number_of_x;
    float x;
    float temp;
    QString name;
    QString str;
    QString dir;
    QDir dirconf;
    QMap<QString, float> map_temp;


};

#endif // CLASS_TEMP_H

