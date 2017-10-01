#ifndef CLASS_PORT_KEITHLEY_H
#define CLASS_PORT_KEITHLEY_H


#include <string>
#include <QtSerialPort/QSerialPort>

class class_port_keithley
{
public:
    class_port_keithley();
    void set_com_port(QString);
    void m_read();
    float get_result(int);
private:
    int cycle_number;
    float result_float_array[4];
    int buff_int[1024];
    QSerialPort *port_keithley;
};

#endif // CLASS_PORT_KEITHLEY_H
