#include "class_write_to_file.h"
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QTime>
#include <QDir>

class_write_to_file::class_write_to_file()
{

    QDateTime date=QDateTime::currentDateTime();
    str1 = "Files_AKL/";
    dir = date.toString("yyyy.MM.dd");
    dir.prepend(str1);
    dirconf.mkpath(dir);

}

void class_write_to_file::create_new_file()
{


    QDateTime date=QDateTime::currentDateTime();
    name = date.toString("yyyy.MM.dd/hh.mm.ss");
    name.prepend(str1);
    name.append(".txt");
    QFile file(name);

    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);

    out << "X\t";
    if (1==number_of_device[0]) out << "A1\t";
    if (1==number_of_device[1]) out << "A2\t";
    if (1==number_of_device[2]) out << "A3\t";
    if (1==number_of_device[3]) out << "A4\t";
    if (1==number_of_device[4]) out << "K1\t";
    if (1==number_of_device[5]) out << "K2\t";
    if (1==number_of_device[6]) out << "K3\t";
    if (1==number_of_device[7]) out << "K4\t";
    if (1==number_of_device[8]) out << "L1\t";
    if (1==number_of_device[9]) out << "L2\t";
    if (1==number_of_device[10]) out << "L3\t";
    if (1==number_of_device[11]) out << "L4\t";

    out << "Time\t\n";
    file.flush();
    file.close();


}

void class_write_to_file::write_to_file(float X, float A1, float A2, float A3, float A4, float K1, float K2, float K3, float K4, float L1, float L2, float L3, float L4)
{
    /*x_result = X;
    if (1==number_of_device[0]) all_results[0]=A1;
    if (1==number_of_device[1]) all_results[1]=A2;
    if (1==number_of_device[2]) all_results[2]=A3;
    if (1==number_of_device[3]) all_results[3]=A4;
    if (1==number_of_device[4]) all_results[4]=K1;
    if (1==number_of_device[5]) all_results[5]=K2;
    if (1==number_of_device[6]) all_results[6]=K3;
    if (1==number_of_device[7]) all_results[7]=K4;
    if (1==number_of_device[8]) all_results[8]=L1;
    if (1==number_of_device[9]) all_results[9]=L2;
    if (1==number_of_device[10]) all_results[10]=L3;
    if (1==number_of_device[11]) all_results[10]=L4;*/


    QFile file(name);
    file.open(QIODevice::Append | QIODevice::Text);
    QTextStream out(&file);

    QDateTime date=QDateTime::currentDateTime();
    QString time = date.toString("hh.mm.ss.zzz");
    out << X << "\t";
    if (1==number_of_device[0]) out << A1 << "\t";
    if (1==number_of_device[1]) out << A2 << "\t";
    if (1==number_of_device[2]) out << A3 << "\t";
    if (1==number_of_device[3]) out << A4 << "\t";
    if (1==number_of_device[4]) out << K1 << "\t";
    if (1==number_of_device[5]) out << K2 << "\t";
    if (1==number_of_device[6]) out << K3 << "\t";
    if (1==number_of_device[7]) out << K4 << "\t";
    if (1==number_of_device[8]) out << L1 << "\t";
    if (1==number_of_device[9]) out << L2 << "\t";
    if (1==number_of_device[10]) out << L3 << "\t";
    if (1==number_of_device[11]) out << L4 << "\t";

    out << time << "\t\n";

    file.flush();
    file.close();

}

void class_write_to_file::get_bool(bool new_bool, int new_int)
{
    number_of_device[new_int]=new_bool;
}

