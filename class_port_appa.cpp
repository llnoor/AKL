#include "class_port_appa.h"

class_port_appa::class_port_appa()
{
    port_appa = new QSerialPort();
}

void class_port_appa::set_com_port(QString COM_port)
{
    port_appa->setPortName(COM_port);
    port_appa->setBaudRate(QSerialPort::Baud9600);
    port_appa->setStopBits(QSerialPort::OneStop);
    port_appa->setDataBits(QSerialPort::Data8);
    port_appa->setParity(QSerialPort::NoParity);
    port_appa->setFlowControl(QSerialPort::NoFlowControl);
    port_appa->open(QIODevice::ReadWrite);

    QByteArray ba;
    ba.resize(5);
    ba[0] = 0x55;
    ba[1] = 0x55;
    ba[2] = 0x00;
    ba[3] = 0x00;
    ba[4] = 0xaa;
    port_appa->write(ba);
    port_appa->waitForBytesWritten(300);

    QByteArray data = port_appa->readAll();
    char *buff = data.data();
    int buff_int_char[60];
    for (int l=0; l<30; l++){
        buff_int_char[l]=0;
        buff_int_char[l]= buff[l]  - '0';
    }
    int sn_appa =
            buff_int_char[12]* 10000000+
            buff_int_char[13]* 1000000+
            buff_int_char[14]* 100000+
            buff_int_char[15]* 10000+
            buff_int_char[16]* 1000+
            buff_int_char[17]* 100+
            buff_int_char[18]* 10+
            buff_int_char[19];
    QString str= QString::number(sn_appa);
    result_string = str.toStdString();
}

float class_port_appa::m_read()
{
    QByteArray ba;
    ba.resize(5);
    ba[0] = 0x55;
    ba[1] = 0x55;
    ba[2] = 0x00;
    ba[3] = 0x00;
    ba[4] = 0xaa;
    port_appa->write(ba);
    QByteArray data = port_appa->readAll();
    char *buff = data.data();
    int buff_int[60];
    for (int l=0; l<60; l++){
        buff_int[l]=buff[l];
    }

    int buff_int_34=buff_int[34];
    int buff_int_35=buff_int[35];
    if (buff_int[34]<0)
    {
        buff_int_34= buff_int[34]+ 256;
    }
    if (buff_int[35]<0)
    {
        buff_int_35= buff_int[35]+ 256;
    }

    result_float= buff_int_34 +(buff_int_35*256);

    if (buff_int[36]<0)
    {
        result_float=result_float*(-1);
    }

    switch (buff_int[37])
    {
    case 0: break;
    case 1: result_float=result_float*(0.1);break;
    case 2: result_float=result_float*(0.01);break;
    case 4: result_float=result_float*(0.001);break;
    case 8: result_float=result_float*(0.0001);break;
    }

    if (port_appa->isOpen())
    {
        return result_float;
    }else
    {
        return 0;
    }
}

std::string class_port_appa::get_sn()
{
    return result_string;
}
