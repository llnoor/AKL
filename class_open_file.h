#ifndef CLASS_OPEN_FILE_H
#define CLASS_OPEN_FILE_H

#include <QDialog>
#include <QTextEdit>
#include <string>
#include <QGridLayout>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
QT_END_NAMESPACE

class class_open_file : public QDialog
{
    Q_OBJECT
public:
    class_open_file();
    QLineEdit *lineEdit_public;
    void open_file();
    std::string get_file_name();
    int get_number_of_bool();

Q_SIGNALS:
    void start_F_get_file_name_and_bool();

private Q_SLOTS:
    void F_plot();

private:
    bool F_bool[14];
    int number_of_bool;
    int t_file;
    std::string F_name;

    QLabel *label;
    QLineEdit *lineEdit;
    QCheckBox *caseCheckBox;
    QCheckBox *fromStartCheckBox;
    QCheckBox *wholeWordsCheckBox;
    QCheckBox *searchSelectionCheckBox;
    QCheckBox *backwardCheckBox;
    QCheckBox *checkBox_F_X;
    QCheckBox *checkBox_F_Y[14];
    QDialogButtonBox *buttonBox;
    QPushButton *findButton;
    QPushButton *Button_plot;
    QPushButton *moreButton;
    QWidget *extension;
    QTextEdit *TextEdit;

    QGridLayout *mainLayout;
};

#endif // CLASS_OPEN_FILE_H
