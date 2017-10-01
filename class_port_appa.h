#ifndef CLASS_PORT_APPA_H
#define CLASS_PORT_APPA_H

#include <string>
#include <QtSerialPort/QSerialPort>

class class_port_appa
{
public:
    class_port_appa();
    void set_com_port( QString );
    float m_read();
    std::string get_sn();

private:
    int result;
    float result_float;
    char buff_appa;
    std::string result_string;
    std::string buff_string;
    QSerialPort *port_appa;

};

#endif // CLASS_PORT_APPA_H
