#ifndef APPA_FILE_H
#define APPA_FILE_H
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QDir>

#pragma once /* Защита от двойного подключения заголовочного файла */

class appa_file
{
public:
    appa_file();
    void write_appa_file(float);
    void write_appa_file2(float);
    void write_appa_file3(float);
    void set_new_name_appa_file();

private:
    void write_files();
    bool appa_bool;
    bool appa_bool2;
    bool appa_bool3;
    float result_appa_file;
    float result_appa_file2;
    float result_appa_file3;
    float result_appa_file_check;
    float result_appa_file_check2;
    float result_appa_file_check3;

    QString str;
    QString str1;
    QString name;
    QString dir;
    QDir dirconf;

};

#endif // APPA_FILE_H
