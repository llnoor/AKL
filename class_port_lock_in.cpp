#include "class_port_lock_in.h"
#include <math.h>
#include <string>
#include <QStringList>

class_port_lock_in::class_port_lock_in()
{
    port_lock_in = new QSerialPort();
}

void class_port_lock_in::set_com_port(QString COM_port)
{
    port_lock_in->setPortName(COM_port);
    port_lock_in->setBaudRate(QSerialPort::Baud9600);
    port_lock_in->setStopBits(QSerialPort::OneStop);
    port_lock_in->setDataBits(QSerialPort::Data8);
    port_lock_in->setParity(QSerialPort::NoParity);
    port_lock_in->setFlowControl(QSerialPort::NoFlowControl);
    port_lock_in->open(QIODevice::ReadWrite);

    QByteArray data;

    //port_lock_in->write("*RST\r\n");
    //port_lock_in->waitForBytesWritten(500);
    //port_lock_in->write("*CLS\r\n");
    //port_lock_in->write("OUTX0\r\n");
    //port_lock_in->write("ICPL1\r\n");
    //port_lock_in->write("ILIN1\r\n");
    port_lock_in->write("FMOD2\r\n");

    data = port_lock_in->readAll();
}

void class_port_lock_in::m_read()
{
    QByteArray data;

    port_lock_in->write("SNAP?1,2,4,9\r\n");

    data = port_lock_in->readAll();
    char *buff = data.data();
    for (int l=0; l<102; l++){
        buff_int[l]=0;
        buff_int[l]= buff[l]  - '0';
    }

    std::string result_tmp = data.toStdString();
    QString data_tmp = QString::fromStdString(result_tmp);
    data_tmp.remove("\n");
    data_tmp.remove("\r");

    QStringList list1 = data_tmp.split(',');
    list1.append("0");
    list1.append("0");
    list1.append("0");
    list1.append("0");
    list1.append("0");
    list1.append("0");

    for (int i=0; i<4;i++)
    {
    result_float_array[i] = list1[i].toFloat();
    }
}

float class_port_lock_in::get_result(int ii)
{
    return result_float_array[ii];
}





