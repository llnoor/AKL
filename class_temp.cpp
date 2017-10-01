#include "class_temp.h"
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QTime>
#include <QDir>

int i=0;

class_temp::class_temp()
{

}


void class_temp::open_new_file(QString name)
{
   str = "temp/";
   str.append(name);

   QFile file (str);
   file.open(QIODevice::ReadOnly | QIODevice::Text);

   //QString str1;
   QStringList list_temp;

   //QMap<QString, float> map_temp;   // <x,temp>


   QTextStream in(&file);
    while (!in.atEnd()) {
       QString line = in.readLine();


       list_temp = line.split("\t");


       //list_temp.append("0.11111");
       //list_temp.append("0.22222");
       list_temp[0].replace(",",".");  //rus_float->eng_float ))) lol
       list_temp[1].replace(",",".");

       QString Temp_X= QString::number(list_temp[0].toFloat(),'f',3);

       map_temp[Temp_X] = list_temp[1].toFloat();
       //qDebug("map_temp[%f]: %f", list_temp[0].toFloat(), map_temp.value(list_temp[0])  );

    }


   file.flush();
   file.close();

}

float class_temp::get_temp(QString x_result)
{
    if (map_temp.contains(x_result))
       temp = map_temp.value(x_result);
    else temp=0;
    return temp;
}





