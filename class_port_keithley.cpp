#include "class_port_keithley.h"
#include <math.h>
#include <string>
#include <QStringList>

class_port_keithley::class_port_keithley()
{
    port_keithley = new QSerialPort();
    cycle_number=0;
    result_float_array[0] = 0;
    result_float_array[1] = 0;
    result_float_array[2] = 0;
    result_float_array[3] = 0;
}

void class_port_keithley::set_com_port(QString COM_port)
{
    port_keithley->setPortName(COM_port);
    port_keithley->setBaudRate(QSerialPort::Baud9600);
    port_keithley->setStopBits(QSerialPort::OneStop);
    port_keithley->setDataBits(QSerialPort::Data8);
    port_keithley->setParity(QSerialPort::NoParity);
    port_keithley->setFlowControl(QSerialPort::NoFlowControl);
    port_keithley->open(QIODevice::ReadWrite);

    QByteArray data;

    //port_keithley->write("*RST\r\n");
    //port_keithley->waitForBytesWritten(500);

    port_keithley->write("*RST\r\n");
    port_keithley->write(":SENS:FUNC 'VOLT:DC'\r\n");
    //port_keithley->write(":SENS:FRES:NPLC 0.5\r\n");
    //port_keithley->write(":SENS:FRES:RANG 100000\r\n");
    port_keithley->write(":SENS:FRES:DIG 6\r\n");

    //port_keithley->write(":DISP:ENAB OFF\r\n");
    //port_keithley->write(":SENS:FUNC 'FRES'\r\n");
    //port_keithley->write(":SENS:FRES:NPLC 0.5\r\n");
    //port_keithley->write(":SENS:FRES:RANG 100000\r\n");
    //port_keithley->write(":SENS:FRES:DIG 4\r\n");
    //port_keithley->write(":ROUTE:CLOSE (@2)\r\n");
    //port_keithley->write(":READ?\r\n");
    //port_keithley->write("FMOD2\r\n");

    data = port_keithley->readAll();
}

void class_port_keithley::m_read()
{
    QByteArray data;

    port_keithley->write(":READ?\r\n");

        data = port_keithley->readAll();
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


        result_float_array[0] = list1[0].toFloat();

        /*port_keithley->waitForReadyRead(200);
        port_keithley->write(":SENS:FUNC 'FRES'\r\n");
        port_keithley->write(":SENS:FRES:NPLC 0.5\r\n");
        port_keithley->write(":SENS:FRES:DIG 6\r\n");
        port_keithley->write(":ROUTE:CLOSE (@3)\r\n");
        port_keithley->waitForBytesWritten(200);*/
        /*
         if (port_keithley->write("LIAS?2\r\n")==1)
         port_keithley->write("AGAN\r\n");;
         */
}

float class_port_keithley::get_result(int ii)
{
    return result_float_array[ii];
}







