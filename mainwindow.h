#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_ 1



#include <qmainwindow.h>
#include <qaction.h>
#include <QLineEdit>
#include <QtCore/QtGlobal>
#include <QMainWindow>   // убрать
#include <QMessageBox>
#include <QtSerialPort/QSerialPort>
#include "dialog_k.h"
#include <QPushButton>
#include <QLabel>
#include <QDialog>

#include "class_port_appa.h"
#include "class_port_lock_in.h"
#include "class_write_to_file.h"
#include "class_port_keithley.h"
#include "class_open_file.h"
#include "class_temp.h"

#define CurvCnt 14

class QSpinBox;
class QPushButton;
class APPA;
class Counter;
class QCheckBox;
class QMenu;

class MainWindow: public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    float writeData_appa();
    dialog_K *dialog_K1;
    class_open_file *class_open_F1;
    class_open_file *class_open_F2;





private Q_SLOTS:
    void showRunning( bool );
    void appendPoints( bool );
    void showElapsed( int );

    void openSerialPort();
    void closeSerialPort();
    void writeData();
    void m_checkBox_X(bool);
    void m_update(bool);

    void ScrollArea_Setting_K();
    void Open_F1();
    void Open_F2();
    void Now_Replot();
    void save_points();
    void get_file_name_F1();
    void get_file_name_F2();
    void Temp();

    void about();
    //void setting();

    //void handleError(QSerialPort::SerialPortError error);

private:
    void createMenus();
    QMenu *fileMenu;
    QMenu *recentFilesMenu;
    QMenu *helpMenu;

    QToolBar *toolBar();
    QToolBar *toolBar_A();
    QToolBar *toolBar_K();
    QToolBar *toolBar_L();
    QToolBar *toolBar_O();
    QToolBar *toolBar_P();
    QToolBar *toolBar_F();
    QToolBar *toolBar_S();
    QToolBar *toolBar_T();

    void initWhatsThis();

    class_port_appa *class_port_APPA_1;
    class_port_appa *class_port_APPA_2;
    class_port_appa *class_port_APPA_3;
    class_port_appa *class_port_APPA_4;
    class_port_lock_in *class_port_Lock_in_1;
    class_port_keithley *class_port_keithley_1;
    class_temp *class_temp_1;

    bool number_of_point[CurvCnt];
    int number_of_point_X;
    float result_appa[4];
    float result_lock_in[4];
    float result_keithley[4];
    float result_X;

private:
    Counter *d_randomCount;
    Counter *d_timerCount;
    QCheckBox *d_symbolType;
    QCheckBox *d_appaType;
    QAction *d_startAction;
    QAction *d_start_New;
    QAction *d_save_points;
    QAction *d_clearAction;
    QAction *d_connectAction;
    QAction *d_readDataAction;
    QAction *d_writeDataAction;
    QAction *d_writeDataAction2;
    QAction *d_writeDataAction3;
    QAction *d_about;
    QAction *d_disconnectAction;
    QAction *d_OpenWindow_A; //APPA
    QAction *d_OpenWindow_K; //Keithley
    QAction *d_OpenWindow_L; //Lock_in
    QAction *d_OpenWindow_O; //Other devise
    QAction *d_OpenWindow_P; //Plot
    QAction *d_OpenWindow_F; //File
    QAction *d_OpenWindow_S; //Setting
    QAction *d_OpenWindow_T; //Temp
    QAction *d_OpenWindow_SK; //Setting Keithley
    QAction *d_OpenWindow_SL; //Setting Lock-in

    APPA *d_plot;
    class_write_to_file *W_File;
    bool W_File_for_create_new_file;

    QWidget *hBox_A;
    QWidget *hBox_K;
    QWidget *hBox_L;
    QWidget *hBox_O;
    QWidget *hBox_P;
    QWidget *hBox_F;
    QWidget *hBox_S;
    QWidget *hBox_T;

    QLineEdit *lineEdit1;
    QLineEdit *lineEdit2;
    QLineEdit *lineEdit3;

    QLineEdit *lineEdit_A1;//APPA
    QLineEdit *lineEdit_A2;
    QLineEdit *lineEdit_A3;
    QLineEdit *lineEdit_A4;
    QLineEdit *lineEdit_K1;//Keithley
    QLineEdit *lineEdit_K2;
    QLineEdit *lineEdit_K3;
    QLineEdit *lineEdit_K4;
    QLineEdit *lineEdit_L1;//Lock_in
    QLineEdit *lineEdit_L2;
    QLineEdit *lineEdit_L3;
    QLineEdit *lineEdit_L4;
    QLineEdit *lineEdit_O1;//other
    QLineEdit *lineEdit_O2;
    QLineEdit *lineEdit_O3;
    QLineEdit *lineEdit_O4;
    QLineEdit *lineEdit_F1;//File
    QLineEdit *lineEdit_F2;

    QLabel *label_A1;       //APPA
    QLabel *label_A2;
    QLabel *label_A3;
    QLabel *label_A4;
    QLabel *label_K1;       //Keithley
    QLabel *label_K2;
    QLabel *label_K3;
    QLabel *label_K4;
    QLabel *label_L1;       //Lock_in
    QLabel *label_L2;
    QLabel *label_L3;
    QLabel *label_L4;
    QLabel *label_O1;       //other
    QLabel *label_O2;
    QLabel *label_O3;
    QLabel *label_O4;
    QLabel *label_F1;       //File
    QLabel *label_F2;

    QPushButton *Button_Start_A1;   //APPA
    QPushButton *Button_Clear_A1;
    QPushButton *Button_Start_A2;
    QPushButton *Button_Clear_A2;
    QPushButton *Button_Start_A3;
    QPushButton *Button_Clear_A3;
    QPushButton *Button_Start_A4;
    QPushButton *Button_Clear_A4;

    QPushButton *Button_Start_K1;   //Keithley
    QPushButton *Button_Clear_K1;
    QPushButton *Button_Start_K2;
    QPushButton *Button_Clear_K2;
    QPushButton *Button_Start_K3;
    QPushButton *Button_Clear_K3;
    QPushButton *Button_Start_K4;
    QPushButton *Button_Clear_K4;

    QPushButton *Button_Start_L1;   //Lock_in
    QPushButton *Button_Clear_L1;
    QPushButton *Button_Start_L2;
    QPushButton *Button_Clear_L2;
    QPushButton *Button_Start_L3;
    QPushButton *Button_Clear_L3;
    QPushButton *Button_Start_L4;
    QPushButton *Button_Clear_L4;

    QPushButton *Button_Start_O1;   //other
    QPushButton *Button_Clear_O1;
    QPushButton *Button_Start_O2;
    QPushButton *Button_Clear_O2;
    QPushButton *Button_Start_O3;
    QPushButton *Button_Clear_O3;
    QPushButton *Button_Start_O4;
    QPushButton *Button_Clear_O4;

    QPushButton *Button_Open_F1;        //File
    QPushButton *Button_Open_F2;
    QPushButton *Button_Clear_F1;
    QPushButton *Button_Clear_F2;



    QLineEdit *lineEdit_Temp_X;
    QLineEdit *lineEdit_Temp_T;
    QCheckBox *checkBox_Temp;
    QPushButton *Button_Temp;


    QPushButton *Button_Setting_K;
    QPushButton *Button_Setting_L;
    QPushButton *Button_Setting_O;
    QPushButton *Button_Setting_F;

    int int_save_points;
    int number_of_checkBox;
    int number_of_checkBox_tmp;
    QCheckBox *checkBox_A1_X; //APPA1
    QCheckBox *checkBox_A2_X;
    QCheckBox *checkBox_A3_X;
    QCheckBox *checkBox_A4_X;
    QCheckBox *checkBox_K1_X; //Keithley
    QCheckBox *checkBox_K2_X;
    QCheckBox *checkBox_K3_X;
    QCheckBox *checkBox_K4_X;
    QCheckBox *checkBox_L1_X; //Lock_in
    QCheckBox *checkBox_L2_X;
    QCheckBox *checkBox_L3_X;
    QCheckBox *checkBox_L4_X;
    QCheckBox *checkBox_O1_X; //other
    QCheckBox *checkBox_O2_X;
    QCheckBox *checkBox_O3_X;
    QCheckBox *checkBox_O4_X;

    QCheckBox *checkBox_A1_Y; //APPA1
    QCheckBox *checkBox_A2_Y;
    QCheckBox *checkBox_A3_Y;
    QCheckBox *checkBox_A4_Y;
    QCheckBox *checkBox_K1_Y; //Keithley
    QCheckBox *checkBox_K2_Y;
    QCheckBox *checkBox_K3_Y;
    QCheckBox *checkBox_K4_Y;
    QCheckBox *checkBox_L1_Y; //Lock_in
    QCheckBox *checkBox_L2_Y;
    QCheckBox *checkBox_L3_Y;
    QCheckBox *checkBox_L4_Y;
    QCheckBox *checkBox_O1_Y; //Other
    QCheckBox *checkBox_O2_Y;
    QCheckBox *checkBox_O3_Y;
    QCheckBox *checkBox_O4_Y;

    QCheckBox *checkBox_L_1000;


    QCheckBox *checkBox_F1; //File
    QCheckBox *checkBox_F2;

    QCheckBox *checkBox_reversal;

    QLabel *label_Empty3;

    QLabel *Label_replot;
    QLineEdit *lineEdit_Plot_x_min;
    QLineEdit *lineEdit_Plot_x_max;
    QLineEdit *lineEdit_Plot_y_min;
    QLineEdit *lineEdit_Plot_y_max;
    QPushButton *Button_replot;





    //int Keithley_APPA_int;
    float x_appa;
};

#endif
