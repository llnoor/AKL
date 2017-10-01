#ifndef DIALOG_K_H
#define DIALOG_K_H

#include <QDialog>
#include <QTextEdit>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
QT_END_NAMESPACE

class dialog_K : public QDialog
{
    Q_OBJECT

public:
    dialog_K(
            //QWidget *parent = 0
            );

private:
    QLabel *label;
    QLineEdit *lineEdit;
    QCheckBox *CheckBox;
    QPushButton *moreButton;
    QTextEdit *TextEdit;

};

#endif // DIALOG_K_H
