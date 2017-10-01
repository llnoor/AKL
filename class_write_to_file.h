#ifndef CLASS_WRITE_TO_FILE_H
#define CLASS_WRITE_TO_FILE_H
#define CurvCnt 14
#include <QString>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QDir>

class class_write_to_file
{
public:
    class_write_to_file();
    void write_to_file(float, float, float, float, float, float, float, float, float, float, float, float, float);
    //                  X,      A1,    A2,    A3,    A4,    K1,    K2,    K3,    K4,    L1,    L2,    L3,    L4,
    void get_bool(bool , int );
    void create_new_file();

private:
    bool number_of_device[CurvCnt];
    float all_results[CurvCnt];
    float x_result;
    QString name;
    QString str;
    QString str1;
    QString dir;
    QDir dirconf;

};

#endif // CLASS_WRITE_TO_FILE_H
