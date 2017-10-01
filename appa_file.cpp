#include "appa_file.h"
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QTime>
#include <QDir>

appa_file::appa_file()
{
    QDateTime date=QDateTime::currentDateTime();
    appa_bool=0;
    appa_bool2=0;
    result_appa_file=0;
    result_appa_file2=0;
    result_appa_file_check=0;
    result_appa_file_check2=0;

    str1 = "Files_keithley/";
    dir = date.toString("yyyy.MM.dd");
    dir.prepend(str1);
    dirconf.mkpath(dir);
}

void appa_file::set_new_name_appa_file()
{
    QDateTime date=QDateTime::currentDateTime();
    name = date.toString("yyyy.MM.dd/hh.mm.ss");
    name.prepend(str1);
    name.append(".txt");
    QFile file(name);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << "X\tY\tTime\t\n";
    out << "mV\tOm\tTime\t\n";

    file.flush();
    file.close();

}

void appa_file::write_appa_file(float result_appa_file)
{
    appa_file::result_appa_file = result_appa_file;
    appa_bool=1;
    if (appa_bool and appa_bool2)
    {
        write_files();
        appa_bool=0;
        appa_bool3=0;
    }



}

void appa_file::write_appa_file2(float result_appa_file2)
{
    appa_file::result_appa_file2 = result_appa_file2;
    appa_bool2=1;
    if (appa_bool and appa_bool2)
    {
        write_files();
        appa_bool=0;
        appa_bool2=0;
    }

}

void appa_file::write_appa_file3(float result_appa_file2)
{
    appa_file::result_appa_file2 = result_appa_file2;
    appa_bool2=1;
    if (appa_bool and appa_bool2)
    {
        write_files();
        appa_bool=0;
        appa_bool2=0;
    }

}


void appa_file::write_files()
{
    QFile file(name);
    file.open(QIODevice::Append | QIODevice::Text);
    QTextStream out(&file);

    QDateTime date=QDateTime::currentDateTime();
    QString time = date.toString("hh.mm.ss.zzz");

    result_appa_file_check = result_appa_file;
    result_appa_file_check2 = result_appa_file2;



    out << result_appa_file_check << "\t" << result_appa_file_check2 << "\t" << time << "\t\n";
    file.flush();
    file.close();
    //}

}
