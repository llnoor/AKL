#ifndef SETTINGS_WIDGET_H
#define SETTINGS_WIDGET_H

#include <QDialog>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
QT_END_NAMESPACE



class Settings_Widget : public QWidget
{
    Q_OBJECT
public:
    //explicit Settings_Widget(QWidget *parent = 0);
    Settings_Widget(QWidget *parent = 0);
    QLabel *label;
    QLineEdit *lineEdit;

//signals:

//public slots:
private:
    //QLabel *label;
    QLabel *label_APPA1;
    QLabel *label_APPA2;
    QLabel *label_APPA3;
    QLabel *label_APPA4;
    QLabel *label_Keithley_ch1;
    QLabel *label_Keithley_ch2;
    QLabel *label_Keithley_ch3;
    QLabel *label_Keithley_ch4;
    QLabel *label_Lock_in_ch1;
    QLabel *label_Lock_in_ch2;
    QLabel *label_Lock_in_ch3;
    QLabel *label_Lock_in_ch4;

    QPushButton *Button_Start_X1;  //X (please don't start)
    QPushButton *Button_Pause_X1;
    QPushButton *Button_Clear_X1;

    QPushButton *Button_Start1;
    QPushButton *Button_Pause1;
    QPushButton *Button_Clear1;
    QPushButton *Button_Start2;
    QPushButton *Button_Pause2;
    QPushButton *Button_Clear2;

    QPushButton *Button_Start1_A1;
    QPushButton *Button_Pause1_A1;
    QPushButton *Button_Clear1_A1;
    QPushButton *Button_Start2_A1;
    QPushButton *Button_Pause2_A1;
    QPushButton *Button_Clear2_A1;

    QPushButton *Button_Start1_A2;
    QPushButton *Button_Pause1_A2;
    QPushButton *Button_Clear1_A2;
    QPushButton *Button_Start2_A2;
    QPushButton *Button_Pause2_A2;
    QPushButton *Button_Clear2_A2;

    QPushButton *Button_Start1_A3;
    QPushButton *Button_Pause1_A3;
    QPushButton *Button_Clear1_A3;
    QPushButton *Button_Start2_A3;
    QPushButton *Button_Pause2_A3;
    QPushButton *Button_Clear2_A3;

    QPushButton *Button_Start1_A4;
    QPushButton *Button_Pause1_A4;
    QPushButton *Button_Clear1_A4;
    QPushButton *Button_Start2_A4;
    QPushButton *Button_Pause2_A4;
    QPushButton *Button_Clear2_A4;


    //QLineEdit *lineEdit;
    QCheckBox *caseCheckBox;
    QCheckBox *fromStartCheckBox;
    QCheckBox *wholeWordsCheckBox;
    QCheckBox *searchSelectionCheckBox;
    QCheckBox *backwardCheckBox;
    QDialogButtonBox *buttonBox;
    QPushButton *findButton;
    QPushButton *moreButton;
    QWidget *extension;

};

#endif // SETTINGS_WIDGET_H
