#ifndef CLASS_PORT_LOCK_IN_H
#define CLASS_PORT_LOCK_IN_H

#include <string>
#include <QtSerialPort/QSerialPort>

class class_port_lock_in
{
public:
    class_port_lock_in();
    void set_com_port(QString);
    void m_read();
    float get_result(int);

private:
    float result_float_array[4];
    int buff_int[1024];
    QSerialPort *port_lock_in;
};

#endif // CLASS_PORT_LOCK_IN_H
