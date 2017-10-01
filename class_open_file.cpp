#include <QtWidgets>
#include <QPushButton>
#include "class_open_file.h"

class_open_file::class_open_file()
{
    //class_open_file::open_file();

}

void class_open_file::open_file()
{
    QString filePath = QFileDialog::getOpenFileName( this, trUtf8( "Open file" ), ".", trUtf8( "Data (*.txt *.dat)" ) );

    F_name = filePath.toStdString();

    QFile file(QString::fromStdString(F_name));

    QString str_file;
    QStringList list_file;
    t_file=0;

    for (int i=0; i<14;i++)
    F_bool[i]=0;

    file.open(QIODevice::ReadOnly | QIODevice::Text);

    str_file= file.readLine();
    str_file.remove("\n");

    list_file = str_file.split('\t');
    t_file = list_file.size();

    file.flush();
    file.close();

    mainLayout = new QGridLayout;

    checkBox_F_X = new QCheckBox("X");
    checkBox_F_X->setChecked(true);
    checkBox_F_X->setEnabled(false);
    mainLayout->addWidget(checkBox_F_X, 0, 0);

    for (int i=1; i<14; i++)
    {
    checkBox_F_Y[i] = new QCheckBox(" ");
    }

    for (int i=1; i<(t_file-1); i++)
    {
        //checkBox_F_Y[i] = new QCheckBox(" ");
        checkBox_F_Y[i]->setText(list_file[i]);
        mainLayout->addWidget(checkBox_F_Y[i], 0, i);
    }

    Button_plot = new QPushButton(tr("Plot"));

    mainLayout->addWidget(Button_plot, 2, 0);
    connect(Button_plot, SIGNAL(clicked()), this, SLOT(F_plot()));

    setLayout(mainLayout);

    setWindowTitle(tr("Open File"));

}

void class_open_file::F_plot()
{
    Q_EMIT start_F_get_file_name_and_bool();
    delete mainLayout;
    delete checkBox_F_X;
    delete Button_plot;
    for (int i=1; i<14; i++)
        {
            delete checkBox_F_Y[i];
        }
}

std::string class_open_file::get_file_name()
{
    return F_name;
}

int class_open_file::get_number_of_bool()
{
    number_of_bool=0;
    for (int i=1; i<(t_file-1); i++)
        {
        if (checkBox_F_Y[i]->isChecked()) number_of_bool=i;
        }
    return number_of_bool;
}







