#include "all_available_serial_ports.h"


#include <QMessageBox>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QTime>
#include <QDir>
#include <QProcess>
#include <string>
#include <QtWidgets>

all_available_serial_ports::all_available_serial_ports()
{

}


void all_available_serial_ports::get_all_available_serial_ports()
{

    QString str;
    QString name;
    QDir dirconf;
    QDateTime date=QDateTime::currentDateTime();
    str = "tmp/";
    dirconf.mkpath(str);
    name = date.toString("yyyy.MM.dd");
    name.prepend(str);
    name.append("_conf.txt");
    m_name = name.toStdString();

    number_of_APPA=0;
    number_of_other_d=0;

    QFile file(QString::fromStdString(m_name));

    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString str_r1;
    QString str_r2;
    QString str_r;

    int m_APPA = 0;
    int m_no_APPA = 0;
    number_of_APPA = 0;

    str_r = file.readLine();   //1
    str_r1 = file.readLine();   //2
    m_APPA = str_r1.split(" ")[0].toInt();

    str_r = file.readLine();    //3
    str_r2 = file.readLine();     //4
    m_no_APPA = str_r2.split(" ")[0].toInt();
    str_r = file.readLine();     //5

    number_of_other_d = m_no_APPA - m_APPA;

    while (1)
    {
        str_r1 = file.readLine(); //Com
        str_r2 = file.readLine(); //Device
        str_r = file.readLine(); //Empty

        str_r1.remove("\n");
        str_r2.remove("\n");

        if ( str_r2.contains("APPA", Qt::CaseInsensitive) )     //search word "APPA" in a string "str_r1"                         //QString t = QString::fromStdString(result_string);  //t.contains("Stanford", Qt::CaseInsensitive);
        {
            m_available_port_A[number_of_APPA]= str_r1.toStdString();
            m_available_port_A_SN[number_of_APPA]= str_r2.toStdString();
            number_of_APPA++;
        }
        else
        {
            if ( str_r2.contains("Keithley", Qt::CaseInsensitive) )
            {
                m_available_port_K = str_r1.toStdString();
            }
            else
            {
                if(str_r2.contains("SR850", Qt::CaseInsensitive))
                {
                    m_available_port_L = str_r1.toStdString();
                }
            }
        }

        if ((str_r1 == "end") or (str_r2 == "end"))
        {
            break;
        }
    }
}




int all_available_serial_ports::get_number_of_APPA()
{
return number_of_APPA;
}
int all_available_serial_ports::get_number_of_other_d()
{
return number_of_other_d;
}

std::string all_available_serial_ports::get_m_available_port_A(int number_appa_new)
{
return m_available_port_A[number_appa_new];
}
std::string all_available_serial_ports::get_m_available_port_A_SN(int number_appa_new)
{
return m_available_port_A_SN[number_appa_new];
}

std::string all_available_serial_ports::get_m_available_port_L()
{
return m_available_port_L;
}

std::string all_available_serial_ports::get_m_available_port_K()
{
return m_available_port_K;
}



/*
std::string all_available_serial_ports::get_m_available_port_other(int number_new)
{
return m_available_port_other[number_new];
}
std::string all_available_serial_ports::get_m_available_port_other_Manufacturer(int number_new)
{
return m_available_port_other_Manufacturer[number_new];
}*/

