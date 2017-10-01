#include <qlabel.h>
#include <qlayout.h>
#include <qstatusbar.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qspinbox.h>
#include <qcheckbox.h>
#include <qwhatsthis.h>
#include <qpixmap.h>
#include <QLineEdit>
#include "appa.h"
#include "mainwindow.h"
#include "dialog_k.h"

#include "start.xpm"
#include "clear.xpm"

#include <QMenu>
#include <QMenuBar>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QMessageBox>
#include <QtSerialPort/QSerialPort>

#include <QFileDialog>
#include <QPushButton>

#include <class_port_appa.h>
#include <class_port_lock_in.h>
#include <class_write_to_file.h>
#include <class_port_keithley.h>
#include <class_open_file.h>

QT_USE_NAMESPACE

class MyToolBar: public QToolBar
{
public:
    MyToolBar( MainWindow *parent ):
        QToolBar( parent )
    {
    }
    void addSpacing( int spacing )
    {
        QLabel *label = new QLabel( this );
        addWidget( label );
        label->setFixedWidth( spacing );
    }
};

class Counter: public QWidget
{
public:
    Counter( QWidget *parent,
            const QString &prefix, const QString &suffix,
            int min, int max, int step ):
        QWidget( parent )
    {
        QHBoxLayout *layout = new QHBoxLayout( this );

        if ( !prefix.isEmpty() )
            layout->addWidget( new QLabel( prefix + " ", this ) );

        d_counter = new QSpinBox( this );
        d_counter->setRange( min, max );
        d_counter->setSingleStep( step );
        layout->addWidget( d_counter );

        if ( !suffix.isEmpty() )
            layout->addWidget( new QLabel( QString( " " ) + suffix, this ) );
    }

    void setValue( int value ) { d_counter->setValue( value ); }
    int value() const { return d_counter->value(); }

private:
    QSpinBox *d_counter;
};

MainWindow::MainWindow()
{
    addToolBar(Qt::TopToolBarArea, toolBar());
    addToolBar(Qt::LeftToolBarArea, toolBar_A());
    addToolBar(Qt::LeftToolBarArea, toolBar_K());
    addToolBar(Qt::LeftToolBarArea, toolBar_L());
    addToolBar(Qt::LeftToolBarArea, toolBar_O());
    addToolBar(Qt::LeftToolBarArea, toolBar_F());
    addToolBar(Qt::LeftToolBarArea, toolBar_S());
    addToolBar(Qt::LeftToolBarArea, toolBar_P());
    addToolBar(Qt::RightToolBarArea, toolBar_T());

    createMenus();

#ifndef QT_NO_STATUSBAR
    ( void )statusBar();
#endif
    int_save_points=0;
    x_appa = 0;
    number_of_checkBox = 0;

    const int margin = 4;
    for (int i=0; i<CurvCnt; i++)
    number_of_point[i]=0;
    number_of_point_X = 20;  //20 - nothing, from 0 to 11 - devices//

    d_plot = new APPA( this );
    d_plot->setContentsMargins( margin, margin, margin, margin );
    setCentralWidget( d_plot );

    class_port_APPA_1 = new class_port_appa();
    class_port_APPA_2 = new class_port_appa();
    class_port_APPA_3 = new class_port_appa();
    class_port_APPA_4 = new class_port_appa();
    class_port_Lock_in_1 = new class_port_lock_in();
    class_port_keithley_1 = new class_port_keithley();
    class_open_F1 = new class_open_file();
    class_open_F2 = new class_open_file();
    class_temp_1 = new class_temp();
    class_temp_1->open_new_file("1.txt");
    W_File = new class_write_to_file();

    connect( d_startAction, SIGNAL( toggled( bool ) ), this, SLOT( appendPoints( bool ) ) );
    connect(Button_Setting_K, SIGNAL (released()),this,SLOT(ScrollArea_Setting_K()));
    connect(Button_Open_F1, SIGNAL (released()),this,SLOT(Open_F1()));
    connect(Button_Open_F2, SIGNAL (released()),this,SLOT(Open_F2()));
    connect(Button_replot, SIGNAL (released()),this,SLOT(Now_Replot()));
    connect(Button_Temp, SIGNAL (released()),this,SLOT(Temp()));
    connect( d_clearAction, SIGNAL( triggered() ), this, SLOT( clear() ) );
    connect( d_save_points, SIGNAL( triggered() ), this, SLOT( save_points() ) );
    connect( d_symbolType, SIGNAL( toggled( bool ) ), d_plot, SLOT( showSymbols( bool ) ) );
    connect( d_plot, SIGNAL( running( bool ) ), this, SLOT( showRunning( bool ) ) );
    connect( d_plot, SIGNAL( elapsed( int ) ), this, SLOT( showElapsed( int ) ) );

    connect( class_open_F1, SIGNAL( start_F_get_file_name_and_bool() ), this, SLOT( get_file_name_F1() ) );
    connect( class_open_F2, SIGNAL( start_F_get_file_name_and_bool() ), this, SLOT( get_file_name_F2() ) );
    connect(Button_Clear_A1, SIGNAL (released()), d_plot,SLOT(Clear_A1()));
    connect(Button_Clear_A2, SIGNAL (released()), d_plot,SLOT(Clear_A2()));
    connect(Button_Clear_A3, SIGNAL (released()), d_plot,SLOT(Clear_A3()));
    connect(Button_Clear_A4, SIGNAL (released()), d_plot,SLOT(Clear_A4()));
    connect(Button_Clear_K1, SIGNAL (released()), d_plot,SLOT(Clear_K1()));
    connect(Button_Clear_K2, SIGNAL (released()), d_plot,SLOT(Clear_K2()));
    connect(Button_Clear_K3, SIGNAL (released()), d_plot,SLOT(Clear_K3()));
    connect(Button_Clear_K4, SIGNAL (released()), d_plot,SLOT(Clear_K4()));
    connect(Button_Clear_L1, SIGNAL (released()), d_plot,SLOT(Clear_L1()));
    connect(Button_Clear_L2, SIGNAL (released()), d_plot,SLOT(Clear_L2()));
    connect(Button_Clear_L3, SIGNAL (released()), d_plot,SLOT(Clear_L3()));
    connect(Button_Clear_L4, SIGNAL (released()), d_plot,SLOT(Clear_L4()));
    connect(Button_Clear_F1, SIGNAL (released()), d_plot,SLOT(Clear_F1()));
    connect(Button_Clear_F2, SIGNAL (released()), d_plot,SLOT(Clear_F2()));
    connect(d_connectAction, SIGNAL(triggered()), this, SLOT(openSerialPort()));
    connect(d_writeDataAction, SIGNAL(triggered()), this, SLOT(writeData()));
    connect(d_about, SIGNAL(triggered()), this, SLOT(about()));
    connect( d_plot, SIGNAL( running_writeData( bool ) ), this, SLOT( writeData() ) );
    connect(checkBox_A1_X,SIGNAL(toggled(bool)),this,SLOT(m_checkBox_X(bool)));
    //connect(checkBox_A1_Y,SIGNAL(toggled(bool)),this,SLOT(m_checkBox_X(bool)));
    connect(checkBox_A2_X,SIGNAL(toggled(bool)),this,SLOT(m_checkBox_X(bool)));
    connect(checkBox_A3_X,SIGNAL(toggled(bool)),this,SLOT(m_checkBox_X(bool)));
    connect(checkBox_A4_X,SIGNAL(toggled(bool)),this,SLOT(m_checkBox_X(bool)));
    connect(checkBox_L1_X,SIGNAL(toggled(bool)),this,SLOT(m_checkBox_X(bool)));
    connect(checkBox_L2_X,SIGNAL(toggled(bool)),this,SLOT(m_checkBox_X(bool)));
    connect(checkBox_L3_X,SIGNAL(toggled(bool)),this,SLOT(m_checkBox_X(bool)));
    connect(checkBox_L4_X,SIGNAL(toggled(bool)),this,SLOT(m_checkBox_X(bool)));
    connect(checkBox_K1_X,SIGNAL(toggled(bool)),this,SLOT(m_checkBox_X(bool)));
    connect(checkBox_K2_X,SIGNAL(toggled(bool)),this,SLOT(m_checkBox_X(bool)));
    connect(checkBox_K3_X,SIGNAL(toggled(bool)),this,SLOT(m_checkBox_X(bool)));
    connect(checkBox_K4_X,SIGNAL(toggled(bool)),this,SLOT(m_checkBox_X(bool)));

    //update
    connect(checkBox_A1_X,SIGNAL(toggled(bool)),this,SLOT(m_update(bool)));
    connect(checkBox_A2_X,SIGNAL(toggled(bool)),this,SLOT(m_update(bool)));
    connect(checkBox_A3_X,SIGNAL(toggled(bool)),this,SLOT(m_update(bool)));
    connect(checkBox_A4_X,SIGNAL(toggled(bool)),this,SLOT(m_update(bool)));
    connect(checkBox_L1_X,SIGNAL(toggled(bool)),this,SLOT(m_update(bool)));
    connect(checkBox_L2_X,SIGNAL(toggled(bool)),this,SLOT(m_update(bool)));
    connect(checkBox_L3_X,SIGNAL(toggled(bool)),this,SLOT(m_update(bool)));
    connect(checkBox_L4_X,SIGNAL(toggled(bool)),this,SLOT(m_update(bool)));
    connect(checkBox_K1_X,SIGNAL(toggled(bool)),this,SLOT(m_update(bool)));
    connect(checkBox_K2_X,SIGNAL(toggled(bool)),this,SLOT(m_update(bool)));
    connect(checkBox_K3_X,SIGNAL(toggled(bool)),this,SLOT(m_update(bool)));
    connect(checkBox_K4_X,SIGNAL(toggled(bool)),this,SLOT(m_update(bool)));
    connect(checkBox_A1_Y,SIGNAL(toggled(bool)),this,SLOT(m_update(bool)));
    connect(checkBox_A2_Y,SIGNAL(toggled(bool)),this,SLOT(m_update(bool)));
    connect(checkBox_A3_Y,SIGNAL(toggled(bool)),this,SLOT(m_update(bool)));
    connect(checkBox_A4_Y,SIGNAL(toggled(bool)),this,SLOT(m_update(bool)));
    connect(checkBox_L1_Y,SIGNAL(toggled(bool)),this,SLOT(m_update(bool)));
    connect(checkBox_L2_Y,SIGNAL(toggled(bool)),this,SLOT(m_update(bool)));
    connect(checkBox_L3_Y,SIGNAL(toggled(bool)),this,SLOT(m_update(bool)));
    connect(checkBox_L4_Y,SIGNAL(toggled(bool)),this,SLOT(m_update(bool)));
    connect(checkBox_K1_Y,SIGNAL(toggled(bool)),this,SLOT(m_update(bool)));
    connect(checkBox_K2_Y,SIGNAL(toggled(bool)),this,SLOT(m_update(bool)));
    connect(checkBox_K3_Y,SIGNAL(toggled(bool)),this,SLOT(m_update(bool)));
    connect(checkBox_K4_Y,SIGNAL(toggled(bool)),this,SLOT(m_update(bool)));

    initWhatsThis();
    setContextMenuPolicy( Qt::NoContextMenu );
}

QToolBar *MainWindow::toolBar()
{
    MyToolBar *toolBar = new MyToolBar( this );
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    d_startAction = new QAction( QPixmap( start_xpm ), "Start", toolBar );
    d_startAction->setCheckable( true );
    d_startAction->setShortcut(QKeySequence(tr("Ctrl+S")));
    d_save_points = new QAction( QPixmap( start_xpm ), "Save points", toolBar );
    d_save_points->setShortcut(QKeySequence::InsertParagraphSeparator); //Enter
    //d_save_points->setCheckable( true );
    d_connectAction = new QAction( QPixmap( start_xpm ), "Connect", toolBar );
    d_writeDataAction = new QAction( QPixmap( start_xpm ), "WriteData", toolBar );
    d_about = new QAction( QPixmap( start_xpm ), "About", toolBar );
    d_clearAction = new QAction( QPixmap( clear_xpm ), "Clear", toolBar );

    QAction *whatsThisAction = QWhatsThis::createAction( toolBar );
    whatsThisAction->setText( "Help" );

    toolBar->addAction( d_startAction );
    toolBar->addAction( d_clearAction );
    toolBar->addAction( d_connectAction );
    toolBar->addAction( d_writeDataAction );
    toolBar->addAction( d_save_points );
    toolBar->addAction( d_about );

    toolBar->addAction( whatsThisAction );

    setIconSize( QSize( 22, 22 ) );

    QWidget *hBox = new QWidget( toolBar );

    d_symbolType = new QCheckBox( "Symbols", hBox );
    d_symbolType->setChecked( true );

    lineEdit1 = new QLineEdit;
    lineEdit2 = new QLineEdit;
    lineEdit3 = new QLineEdit;
    lineEdit1->setText(tr("1 point"));
    lineEdit1->setReadOnly(true);
    lineEdit2->setText(tr("2 point"));
    lineEdit2->setReadOnly(true);
    lineEdit3->setText(tr("3 point"));
    lineEdit3->setReadOnly(true);

    d_timerCount = new Counter( hBox, "Delay", "ms", 0, 100000, 100 );
    d_timerCount->setValue( 600 );

    QHBoxLayout *layout = new QHBoxLayout( hBox );
    layout->setMargin( 0 );
    layout->setSpacing( 0 );
    layout->addSpacing( 10 );
    layout->addWidget( new QWidget( hBox ), 10 ); // spacer
    layout->addWidget( lineEdit1 );
    layout->addSpacing( 5 );
    layout->addWidget( lineEdit2 );
    layout->addSpacing( 5 );
    layout->addWidget( lineEdit3 );
    layout->addSpacing( 5 );
    layout->addWidget( d_symbolType );
    layout->addSpacing( 5 );
    layout->addWidget( d_timerCount );
    showRunning( false );
    toolBar->addWidget( hBox );

    return toolBar;
}

QToolBar *MainWindow::toolBar_A()
{
    MyToolBar *toolBar_A = new MyToolBar( this );
    toolBar_A->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    hBox_A = new QWidget( toolBar_A );

    d_OpenWindow_A = toolBar_A->toggleViewAction();
    d_OpenWindow_A->setIconText("APPA");
    d_OpenWindow_A->setIcon(QPixmap( start_xpm ));
    d_OpenWindow_A->setText("APPA");
    d_OpenWindow_A->setShortcut(QKeySequence(tr("Ctrl+A")));
    d_OpenWindow_A->setStatusTip(tr("Open Window"));

    lineEdit_A1 = new QLineEdit(tr("APPA 1"));
    checkBox_A1_X = new QCheckBox(tr("X"));
    checkBox_A1_Y = new QCheckBox(tr("Y"));
    Button_Clear_A1  = new QPushButton(tr("Clear"));

    lineEdit_A2 = new QLineEdit(tr("APPA 2"));
    checkBox_A2_X = new QCheckBox(tr("X"));
    checkBox_A2_Y = new QCheckBox(tr("Y"));
    Button_Clear_A2  = new QPushButton(tr("Clear"));

    lineEdit_A3 = new QLineEdit(tr("APPA 3"));
    checkBox_A3_X = new QCheckBox(tr("X"));
    checkBox_A3_Y = new QCheckBox(tr("Y"));
    Button_Clear_A3  = new QPushButton(tr("Clear"));

    lineEdit_A4 = new QLineEdit(tr("APPA 4"));
    checkBox_A4_X = new QCheckBox(tr("X"));
    checkBox_A4_Y = new QCheckBox(tr("Y"));
    Button_Clear_A4  = new QPushButton(tr("Clear"));

    lineEdit_A1->setReadOnly(true);
    lineEdit_A2->setReadOnly(true);
    lineEdit_A3->setReadOnly(true);
    lineEdit_A4->setReadOnly(true);

    lineEdit_A1->setEnabled(false);
    checkBox_A1_X->setEnabled(false);
    checkBox_A1_Y->setEnabled(false);
    Button_Clear_A1->setEnabled(false);
    lineEdit_A2->setEnabled(false);
    checkBox_A2_X->setEnabled(false);
    checkBox_A2_Y->setEnabled(false);
    Button_Clear_A2->setEnabled(false);
    lineEdit_A3->setEnabled(false);
    checkBox_A3_X->setEnabled(false);
    checkBox_A3_Y->setEnabled(false);
    Button_Clear_A3->setEnabled(false);
    lineEdit_A4->setEnabled(false);
    checkBox_A4_X->setEnabled(false);
    checkBox_A4_Y->setEnabled(false);
    Button_Clear_A4->setEnabled(false);

    QGridLayout *mainLayout = new QGridLayout( hBox_A );
    mainLayout->addWidget(lineEdit_A1, 0, 0);
    mainLayout->addWidget(checkBox_A1_X, 0, 1);
    mainLayout->addWidget(checkBox_A1_Y, 0, 2);
    mainLayout->addWidget(Button_Clear_A1, 0, 3);

    mainLayout->addWidget(lineEdit_A2, 1, 0);
    mainLayout->addWidget(checkBox_A2_X, 1, 1);
    mainLayout->addWidget(checkBox_A2_Y, 1, 2);
    mainLayout->addWidget(Button_Clear_A2, 1, 3);

    mainLayout->addWidget(lineEdit_A3, 2, 0);
    mainLayout->addWidget(checkBox_A3_X, 2, 1);
    mainLayout->addWidget(checkBox_A3_Y, 2, 2);
    mainLayout->addWidget(Button_Clear_A3, 2, 3);

    mainLayout->addWidget(lineEdit_A4, 3, 0);
    mainLayout->addWidget(checkBox_A4_X, 3, 1);
    mainLayout->addWidget(checkBox_A4_Y, 3, 2);
    mainLayout->addWidget(Button_Clear_A4, 3, 3);

    toolBar_A->addWidget( hBox_A );
    return toolBar_A;
}

QToolBar *MainWindow::toolBar_K()
{
    MyToolBar *toolBar_K = new MyToolBar( this );
    toolBar_K->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    hBox_K = new QWidget( toolBar_K );

    d_OpenWindow_K = toolBar_K->toggleViewAction();
    d_OpenWindow_K->setIconText("Keithley");
    d_OpenWindow_K->setIcon(QPixmap( start_xpm ));
    d_OpenWindow_K->setText("Keithley");
    d_OpenWindow_K->setShortcut(QKeySequence(tr("Ctrl+K")));
    d_OpenWindow_K->setStatusTip(tr("Open Window"));

    lineEdit_K1 = new QLineEdit(tr("Keithley 1"));
    checkBox_K1_X = new QCheckBox(tr("X"));
    checkBox_K1_Y = new QCheckBox(tr("Y"));
    Button_Clear_K1  = new QPushButton(tr("Clear"));

    lineEdit_K2 = new QLineEdit(tr("Keithley 2"));
    checkBox_K2_X = new QCheckBox(tr("X"));
    checkBox_K2_Y = new QCheckBox(tr("Y"));
    Button_Clear_K2  = new QPushButton(tr("Clear"));

    lineEdit_K3 = new QLineEdit(tr("Keithley 3"));
    checkBox_K3_X = new QCheckBox(tr("X"));
    checkBox_K3_Y = new QCheckBox(tr("Y"));
    Button_Clear_K3  = new QPushButton(tr("Clear"));

    lineEdit_K4 = new QLineEdit(tr("Keithley 4"));
    checkBox_K4_X = new QCheckBox(tr("X"));
    checkBox_K4_Y = new QCheckBox(tr("Y"));
    Button_Clear_K4  = new QPushButton(tr("Clear"));

    lineEdit_K1->setReadOnly(true);
    lineEdit_K2->setReadOnly(true);
    lineEdit_K3->setReadOnly(true);
    lineEdit_K4->setReadOnly(true);

    lineEdit_K1->setEnabled(false);
    checkBox_K1_X->setEnabled(false);
    checkBox_K1_Y->setEnabled(false);
    Button_Clear_K1->setEnabled(false);
    lineEdit_K2->setEnabled(false);
    checkBox_K2_X->setEnabled(false);
    checkBox_K2_Y->setEnabled(false);
    Button_Clear_K2->setEnabled(false);
    lineEdit_K3->setEnabled(false);
    checkBox_K3_X->setEnabled(false);
    checkBox_K3_Y->setEnabled(false);
    Button_Clear_K3->setEnabled(false);
    lineEdit_K4->setEnabled(false);
    checkBox_K4_X->setEnabled(false);
    checkBox_K4_Y->setEnabled(false);
    Button_Clear_K4->setEnabled(false);

    QGridLayout *mainLayout = new QGridLayout( hBox_K );
    mainLayout->addWidget(lineEdit_K1, 0, 0);
    mainLayout->addWidget(checkBox_K1_X, 0, 1);
    mainLayout->addWidget(checkBox_K1_Y, 0, 2);
    mainLayout->addWidget(Button_Clear_K1, 0, 3);

    mainLayout->addWidget(lineEdit_K2, 1, 0);
    mainLayout->addWidget(checkBox_K2_X, 1, 1);
    mainLayout->addWidget(checkBox_K2_Y, 1, 2);
    mainLayout->addWidget(Button_Clear_K2, 1, 3);

    mainLayout->addWidget(lineEdit_K3, 2, 0);
    mainLayout->addWidget(checkBox_K3_X, 2, 1);
    mainLayout->addWidget(checkBox_K3_Y, 2, 2);
    mainLayout->addWidget(Button_Clear_K3, 2, 3);

    mainLayout->addWidget(lineEdit_K4, 3, 0);
    mainLayout->addWidget(checkBox_K4_X, 3, 1);
    mainLayout->addWidget(checkBox_K4_Y, 3, 2);
    mainLayout->addWidget(Button_Clear_K4, 3, 3);

    toolBar_K->addWidget( hBox_K );
    return toolBar_K;
}

QToolBar *MainWindow::toolBar_L()
{
    MyToolBar *toolBar_L = new MyToolBar( this );
    toolBar_L->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    hBox_L = new QWidget( toolBar_L );

    d_OpenWindow_L = toolBar_L->toggleViewAction();
    d_OpenWindow_L->setIconText("Lock-in");
    d_OpenWindow_L->setIcon(QPixmap( start_xpm ));
    d_OpenWindow_L->setText("Lock-in");
    d_OpenWindow_L->setShortcut(QKeySequence(tr("Ctrl+L")));
    d_OpenWindow_L->setStatusTip(tr("Open Window"));

    lineEdit_L1 = new QLineEdit(tr("Lock-in 1"));
    checkBox_L1_X = new QCheckBox(tr("X"));
    checkBox_L1_Y = new QCheckBox(tr("Y"));
    Button_Clear_L1  = new QPushButton(tr("Clear"));

    lineEdit_L2 = new QLineEdit(tr("Lock-in 2"));
    checkBox_L2_X = new QCheckBox(tr("X"));
    checkBox_L2_Y = new QCheckBox(tr("Y"));
    Button_Clear_L2  = new QPushButton(tr("Clear"));

    lineEdit_L3 = new QLineEdit(tr("Lock-in 3"));
    checkBox_L3_X = new QCheckBox(tr("X"));
    checkBox_L3_Y = new QCheckBox(tr("Y"));
    Button_Clear_L3  = new QPushButton(tr("Clear"));

    lineEdit_L4 = new QLineEdit(tr("Lock-in 4"));
    checkBox_L4_X = new QCheckBox(tr("X"));
    checkBox_L4_Y = new QCheckBox(tr("Y"));
    Button_Clear_L4  = new QPushButton(tr("Clear"));

    checkBox_L_1000 = new QCheckBox(tr("result of Lock-in * 1000"));

    lineEdit_L1->setReadOnly(true);
    lineEdit_L2->setReadOnly(true);
    lineEdit_L3->setReadOnly(true);
    lineEdit_L4->setReadOnly(true);

    lineEdit_L1->setEnabled(false);
    checkBox_L1_X->setEnabled(false);
    checkBox_L1_Y->setEnabled(false);
    Button_Clear_L1->setEnabled(false);
    lineEdit_L2->setEnabled(false);
    checkBox_L2_X->setEnabled(false);
    checkBox_L2_Y->setEnabled(false);
    Button_Clear_L2->setEnabled(false);
    lineEdit_L3->setEnabled(false);
    checkBox_L3_X->setEnabled(false);
    checkBox_L3_Y->setEnabled(false);
    Button_Clear_L3->setEnabled(false);
    lineEdit_L4->setEnabled(false);
    checkBox_L4_X->setEnabled(false);
    checkBox_L4_Y->setEnabled(false);
    Button_Clear_L4->setEnabled(false);
    checkBox_L_1000->setEnabled(false);

    QGridLayout *mainLayout = new QGridLayout( hBox_L );
    mainLayout->addWidget(lineEdit_L1, 0, 0);
    mainLayout->addWidget(checkBox_L1_X, 0, 1);
    mainLayout->addWidget(checkBox_L1_Y, 0, 2);
    mainLayout->addWidget(Button_Clear_L1, 0, 3);

    mainLayout->addWidget(lineEdit_L2, 1, 0);
    mainLayout->addWidget(checkBox_L2_X, 1, 1);
    mainLayout->addWidget(checkBox_L2_Y, 1, 2);
    mainLayout->addWidget(Button_Clear_L2, 1, 3);

    mainLayout->addWidget(lineEdit_L3, 2, 0);
    mainLayout->addWidget(checkBox_L3_X, 2, 1);
    mainLayout->addWidget(checkBox_L3_Y, 2, 2);
    mainLayout->addWidget(Button_Clear_L3, 2, 3);

    mainLayout->addWidget(lineEdit_L4, 3, 0);
    mainLayout->addWidget(checkBox_L4_X, 3, 1);
    mainLayout->addWidget(checkBox_L4_Y, 3, 2);
    mainLayout->addWidget(Button_Clear_L4, 3, 3);

    //mainLayout->addWidget(checkBox_L_1000, 4, 0);

    toolBar_L->addWidget( hBox_L );
    return toolBar_L;
}

QToolBar *MainWindow::toolBar_O()
{
    MyToolBar *toolBar_O = new MyToolBar( this );
    toolBar_O->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    hBox_O = new QWidget( toolBar_O );

    d_OpenWindow_O = toolBar_O->toggleViewAction();
    d_OpenWindow_O->setIconText("Other");
    d_OpenWindow_O->setIcon(QPixmap( start_xpm ));
    d_OpenWindow_O->setText("Other");
    d_OpenWindow_O->setShortcut(QKeySequence(tr("Ctrl+O")));
    d_OpenWindow_O->setStatusTip(tr("Open Window"));

    lineEdit_O1 = new QLineEdit(tr("Other 1"));
    checkBox_O1_X = new QCheckBox(tr("X"));
    checkBox_O1_Y = new QCheckBox(tr("Y"));
    Button_Clear_O1  = new QPushButton(tr("Clear"));

    lineEdit_O2 = new QLineEdit(tr("Other 2"));
    checkBox_O2_X = new QCheckBox(tr("X"));
    checkBox_O2_Y = new QCheckBox(tr("Y"));
    Button_Clear_O2  = new QPushButton(tr("Clear"));

    lineEdit_O3 = new QLineEdit(tr("Other 3"));
    checkBox_O3_X = new QCheckBox(tr("X"));
    checkBox_O3_Y = new QCheckBox(tr("Y"));
    Button_Clear_O3  = new QPushButton(tr("Clear"));

    lineEdit_O4 = new QLineEdit(tr("Other 4"));
    checkBox_O4_X = new QCheckBox(tr("X"));
    checkBox_O4_Y = new QCheckBox(tr("Y"));
    Button_Clear_O4  = new QPushButton(tr("Clear"));

    lineEdit_O1->setReadOnly(true);
    lineEdit_O2->setReadOnly(true);
    lineEdit_O3->setReadOnly(true);
    lineEdit_O4->setReadOnly(true);

    lineEdit_O1->setEnabled(false);
    checkBox_O1_X->setEnabled(false);
    checkBox_O1_Y->setEnabled(false);
    Button_Clear_O1->setEnabled(false);
    lineEdit_O2->setEnabled(false);
    checkBox_O2_X->setEnabled(false);
    checkBox_O2_Y->setEnabled(false);
    Button_Clear_O2->setEnabled(false);
    lineEdit_O3->setEnabled(false);
    checkBox_O3_X->setEnabled(false);
    checkBox_O3_Y->setEnabled(false);
    Button_Clear_O3->setEnabled(false);
    lineEdit_O4->setEnabled(false);
    checkBox_O4_X->setEnabled(false);
    checkBox_O4_Y->setEnabled(false);
    Button_Clear_O4->setEnabled(false);

    QGridLayout *mainLayout = new QGridLayout( hBox_O );
    mainLayout->addWidget(lineEdit_O1, 0, 0);
    mainLayout->addWidget(checkBox_O1_X, 0, 1);
    mainLayout->addWidget(checkBox_O1_Y, 0, 2);
    mainLayout->addWidget(Button_Clear_O1, 0, 3);

    mainLayout->addWidget(lineEdit_O2, 1, 0);
    mainLayout->addWidget(checkBox_O2_X, 1, 1);
    mainLayout->addWidget(checkBox_O2_Y, 1, 2);
    mainLayout->addWidget(Button_Clear_O2, 1, 3);

    mainLayout->addWidget(lineEdit_O3, 2, 0);
    mainLayout->addWidget(checkBox_O3_X, 2, 1);
    mainLayout->addWidget(checkBox_O3_Y, 2, 2);
    mainLayout->addWidget(Button_Clear_O3, 2, 3);

    mainLayout->addWidget(lineEdit_O4, 3, 0);
    mainLayout->addWidget(checkBox_O4_X, 3, 1);
    mainLayout->addWidget(checkBox_O4_Y, 3, 2);
    mainLayout->addWidget(Button_Clear_O4, 3, 3);

    toolBar_O->addWidget( hBox_O );
    toolBar_O->hide();
    return toolBar_O;
}

QToolBar *MainWindow::toolBar_P()
{

    MyToolBar *toolBar_P = new MyToolBar( this );
    toolBar_P->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    hBox_P = new QWidget( toolBar_P );

    d_OpenWindow_P = toolBar_P->toggleViewAction();
    d_OpenWindow_P->setIconText("Plot");
    d_OpenWindow_P->setIcon(QPixmap( start_xpm ));
    d_OpenWindow_P->setText("Plot");
    d_OpenWindow_P->setShortcut(QKeySequence(tr("Ctrl+P")));
    d_OpenWindow_P->setStatusTip(tr("Open Window"));

    Label_replot = new QLabel(tr("Plot Size"));
    lineEdit_Plot_x_min = new QLineEdit(tr("Plot Size: x_min: -10"));
    lineEdit_Plot_x_max = new QLineEdit(tr("Plot Size: x_max: 10"));
    lineEdit_Plot_y_min = new QLineEdit(tr("Plot Size: y_min: -10"));
    lineEdit_Plot_y_max = new QLineEdit(tr("Plot Size: y_max: 10"));
    Button_replot = new QPushButton(tr("Replot"));

    QGridLayout *mainLayout = new QGridLayout( hBox_P );

    mainLayout->addWidget(Label_replot, 0, 0);
    mainLayout->addWidget(lineEdit_Plot_x_min, 1, 0);
    mainLayout->addWidget(lineEdit_Plot_x_max, 2, 0);
    mainLayout->addWidget(lineEdit_Plot_y_min, 3, 0);
    mainLayout->addWidget(lineEdit_Plot_y_max, 4, 0);
    mainLayout->addWidget(Button_replot, 5, 0);

    toolBar_P->addWidget( hBox_P );

    return toolBar_P;
}

QToolBar *MainWindow::toolBar_T()
{
    MyToolBar *toolBar_T = new MyToolBar( this );
    toolBar_T->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    hBox_T = new QWidget( toolBar_T );

    d_OpenWindow_T = toolBar_T->toggleViewAction();
    d_OpenWindow_T->setIconText("Temp");
    d_OpenWindow_T->setIcon(QPixmap( start_xpm ));
    d_OpenWindow_T->setText("Temp");
    d_OpenWindow_T->setShortcut(QKeySequence(tr("Ctrl+T")));
    d_OpenWindow_T->setStatusTip(tr("Open Window"));

    lineEdit_Temp_X = new QLineEdit(tr("X: "));
    lineEdit_Temp_T = new QLineEdit(tr("T: "));
    Button_Temp = new QPushButton(tr("Temp"));

    QGridLayout *mainLayout = new QGridLayout( hBox_T );

    mainLayout->addWidget(lineEdit_Temp_X, 0, 0);
    mainLayout->addWidget(lineEdit_Temp_T, 0, 1);
    mainLayout->addWidget(Button_Temp, 1, 0);

    toolBar_T->addWidget( hBox_T );

    return toolBar_T;
}

QToolBar *MainWindow::toolBar_F()
{
    MyToolBar *toolBar_F = new MyToolBar( this );
    toolBar_F->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    hBox_F = new QWidget( toolBar_F );

    d_OpenWindow_F = toolBar_F->toggleViewAction();
    d_OpenWindow_F->setIconText("File");
    d_OpenWindow_F->setIcon(QPixmap( start_xpm ));
    d_OpenWindow_F->setText("File");
    d_OpenWindow_F->setShortcut(QKeySequence(tr("Ctrl+F")));
    d_OpenWindow_F->setStatusTip(tr("Open Window"));

    lineEdit_F1 = new QLineEdit(tr("File 1"));
    Button_Open_F1  = new QPushButton(tr("Open File"));
    Button_Clear_F1  = new QPushButton(tr("Clear"));

    lineEdit_F2 = new QLineEdit(tr("File 2"));
    Button_Open_F2  = new QPushButton(tr("Open File"));
    Button_Clear_F2  = new QPushButton(tr("Clear"));

    lineEdit_F1->setReadOnly(true);
    lineEdit_F2->setReadOnly(true);

    QGridLayout *mainLayout = new QGridLayout( hBox_F );

    mainLayout->addWidget(lineEdit_F1, 0, 0);
    mainLayout->addWidget(Button_Open_F1, 0, 3);
    mainLayout->addWidget(Button_Clear_F1, 1, 3);
    mainLayout->addWidget(lineEdit_F2, 2, 0);
    mainLayout->addWidget(Button_Open_F2, 2, 3);
    mainLayout->addWidget(Button_Clear_F2, 3, 3);

    toolBar_F->addWidget( hBox_F );

    return toolBar_F;
}

QToolBar *MainWindow::toolBar_S()
{

    MyToolBar *toolBar_S = new MyToolBar( this );
    toolBar_S->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    hBox_S = new QWidget( toolBar_S );

    d_OpenWindow_S = toolBar_S->toggleViewAction();
    d_OpenWindow_S->setIconText("Setting");
    d_OpenWindow_S->setIcon(QPixmap( start_xpm ));
    d_OpenWindow_S->setText("Setting");
    d_OpenWindow_S->setShortcut(QKeySequence(tr("Ctrl+Z")));
    d_OpenWindow_S->setStatusTip(tr("Open Window"));

    Button_Setting_K   = new QPushButton(tr("Setting Keithley"));
    Button_Setting_L   = new QPushButton(tr("Setting Lock-in"));

    QGridLayout *mainLayout = new QGridLayout( hBox_S );

    mainLayout->addWidget(Button_Setting_K, 0, 0);
    mainLayout->addWidget(Button_Setting_L, 1, 0);

    toolBar_S->addWidget( hBox_S );
    toolBar_S->hide();
    return toolBar_S;
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&Windows"));
    fileMenu->addAction(d_startAction);
    fileMenu->addAction(d_OpenWindow_A);
    fileMenu->addAction(d_OpenWindow_K);
    fileMenu->addAction(d_OpenWindow_L);
    fileMenu->addAction(d_OpenWindow_O);
    fileMenu->addAction(d_OpenWindow_P);
    fileMenu->addAction(d_OpenWindow_F);
    fileMenu->addAction(d_OpenWindow_S);
    fileMenu->addAction(d_OpenWindow_T);
}

void MainWindow::m_checkBox_X(bool t)
{
    int new_int=0;t=t;

    if (checkBox_A1_X->isChecked()) {number_of_checkBox = 1; new_int++;}
    if (checkBox_A2_X->isChecked()) {number_of_checkBox = 2; new_int++;}
    if (checkBox_A3_X->isChecked()) {number_of_checkBox = 3; new_int++;}
    if (checkBox_A4_X->isChecked()) {number_of_checkBox = 4; new_int++;}

    if (checkBox_K1_X->isChecked()) {number_of_checkBox = 11; new_int++;}
    if (checkBox_K2_X->isChecked()) {number_of_checkBox = 12; new_int++;}
    if (checkBox_K3_X->isChecked()) {number_of_checkBox = 13; new_int++;}
    if (checkBox_K4_X->isChecked()) {number_of_checkBox = 14; new_int++;}

    if (checkBox_L1_X->isChecked()) {number_of_checkBox = 21; new_int++;}
    if (checkBox_L2_X->isChecked()) {number_of_checkBox = 22; new_int++;}
    if (checkBox_L3_X->isChecked()) {number_of_checkBox = 23; new_int++;}
    if (checkBox_L4_X->isChecked()) {number_of_checkBox = 24; new_int++;}

    if (new_int>1)
    {
        switch (number_of_checkBox_tmp) {
        case 1:checkBox_A1_X->setChecked(false);checkBox_A1_Y->setChecked(true);break;
        case 2:checkBox_A2_X->setChecked(false);checkBox_A2_Y->setChecked(true);break;
        case 3:checkBox_A3_X->setChecked(false);checkBox_A3_Y->setChecked(true);break;
        case 4:checkBox_A4_X->setChecked(false);checkBox_A4_Y->setChecked(true);break;

        case 11:checkBox_K1_X->setChecked(false);checkBox_K1_Y->setChecked(true);break;
        case 12:checkBox_K2_X->setChecked(false);checkBox_K2_Y->setChecked(true);break;
        case 13:checkBox_K3_X->setChecked(false);checkBox_K3_Y->setChecked(true);break;
        case 14:checkBox_K4_X->setChecked(false);checkBox_K4_Y->setChecked(true);break;

        case 21:checkBox_L1_X->setChecked(false);checkBox_L1_Y->setChecked(true);break;
        case 22:checkBox_L2_X->setChecked(false);checkBox_L2_Y->setChecked(true);break;
        case 23:checkBox_L3_X->setChecked(false);checkBox_L3_Y->setChecked(true);break;
        case 24:checkBox_L4_X->setChecked(false);checkBox_L4_Y->setChecked(true);break;
        }
        number_of_checkBox=number_of_checkBox_tmp;
    }
        number_of_checkBox_tmp=number_of_checkBox;
    switch (number_of_checkBox) {
    case 1:if (new_int!=0)checkBox_A1_Y->setChecked(false);else checkBox_A1_Y->setChecked(true);break;
    case 2:if (new_int!=0)checkBox_A2_Y->setChecked(false);else checkBox_A2_Y->setChecked(true);break;
    case 3:if (new_int!=0)checkBox_A3_Y->setChecked(false);else checkBox_A3_Y->setChecked(true);break;
    case 4:if (new_int!=0)checkBox_A4_Y->setChecked(false);else checkBox_A4_Y->setChecked(true);break;
    case 11:if (new_int!=0)checkBox_K1_Y->setChecked(false);else checkBox_K1_Y->setChecked(true);break;
    case 12:if (new_int!=0)checkBox_K2_Y->setChecked(false);else checkBox_K2_Y->setChecked(true);break;
    case 13:if (new_int!=0)checkBox_K3_Y->setChecked(false);else checkBox_K3_Y->setChecked(true);break;
    case 14:if (new_int!=0)checkBox_K4_Y->setChecked(false);else checkBox_K4_Y->setChecked(true);break;
    case 21:if (new_int!=0)checkBox_L1_Y->setChecked(false);else checkBox_L1_Y->setChecked(true);break;
    case 22:if (new_int!=0)checkBox_L2_Y->setChecked(false);else checkBox_L2_Y->setChecked(true);break;
    case 23:if (new_int!=0)checkBox_L3_Y->setChecked(false);else checkBox_L3_Y->setChecked(true);break;
    case 24:if (new_int!=0)checkBox_L4_Y->setChecked(false);else checkBox_L4_Y->setChecked(true);break;
    }
}

void MainWindow::m_update(bool t)
{
    t=t;

    if (checkBox_A1_Y->isChecked())  {number_of_point[0]=1;d_plot->get_bool(1,0);W_File->get_bool(1,0);} else {number_of_point[0]=0;d_plot->get_bool(0,0);W_File->get_bool(0,0);}
    if (checkBox_A2_Y->isChecked())  {number_of_point[1]=1;d_plot->get_bool(1,1);W_File->get_bool(1,1);} else {number_of_point[1]=0;d_plot->get_bool(0,1);W_File->get_bool(0,1);}
    if (checkBox_A3_Y->isChecked())  {number_of_point[2]=1;d_plot->get_bool(1,2);W_File->get_bool(1,2);} else {number_of_point[2]=0;d_plot->get_bool(0,2);W_File->get_bool(0,2);}
    if (checkBox_A4_Y->isChecked())  {number_of_point[3]=1;d_plot->get_bool(1,3);W_File->get_bool(1,3);} else {number_of_point[3]=0;d_plot->get_bool(0,3);W_File->get_bool(0,3);}

    if (checkBox_K1_Y->isChecked())  {number_of_point[4]=1;d_plot->get_bool(1,4);W_File->get_bool(1,4);} else {number_of_point[4]=0;d_plot->get_bool(0,4);W_File->get_bool(0,4);}
    if (checkBox_K2_Y->isChecked())  {number_of_point[5]=1;d_plot->get_bool(1,5);W_File->get_bool(1,5);} else {number_of_point[5]=0;d_plot->get_bool(0,5);W_File->get_bool(0,5);}
    if (checkBox_K3_Y->isChecked())  {number_of_point[6]=1;d_plot->get_bool(1,6);W_File->get_bool(1,6);} else {number_of_point[6]=0;d_plot->get_bool(0,6);W_File->get_bool(0,6);}
    if (checkBox_K4_Y->isChecked())  {number_of_point[7]=1;d_plot->get_bool(1,7);W_File->get_bool(1,7);} else {number_of_point[7]=0;d_plot->get_bool(0,7);W_File->get_bool(0,7);}

    if (checkBox_L1_Y->isChecked())  {number_of_point[8]=1;d_plot->get_bool(1,8);W_File->get_bool(1,8);} else {number_of_point[8]=0;d_plot->get_bool(0,8);W_File->get_bool(0,8);}
    if (checkBox_L2_Y->isChecked())  {number_of_point[9]=1;d_plot->get_bool(1,9);W_File->get_bool(1,9);} else {number_of_point[9]=0;d_plot->get_bool(0,9);W_File->get_bool(0,9);}
    if (checkBox_L3_Y->isChecked())  {number_of_point[10]=1;d_plot->get_bool(1,10);W_File->get_bool(1,10);} else {number_of_point[10]=0;d_plot->get_bool(0,10);W_File->get_bool(0,10);}
    if (checkBox_L4_Y->isChecked())  {number_of_point[11]=1;d_plot->get_bool(1,11);W_File->get_bool(1,11);} else {number_of_point[11]=0;d_plot->get_bool(0,11);W_File->get_bool(0,11);}

    if (checkBox_A1_X->isChecked()) number_of_point_X=0;
    if (checkBox_A2_X->isChecked()) number_of_point_X=1;
    if (checkBox_A3_X->isChecked()) number_of_point_X=2;
    if (checkBox_A4_X->isChecked()) number_of_point_X=3;

    if (checkBox_K1_X->isChecked()) number_of_point_X=4;
    if (checkBox_K2_X->isChecked()) number_of_point_X=5;
    if (checkBox_K3_X->isChecked()) number_of_point_X=6;
    if (checkBox_K4_X->isChecked()) number_of_point_X=7;

    if (checkBox_L1_X->isChecked()) number_of_point_X=8;
    if (checkBox_L2_X->isChecked()) number_of_point_X=9;
    if (checkBox_L3_X->isChecked()) number_of_point_X=10;
    if (checkBox_L4_X->isChecked()) number_of_point_X=11;

}

void MainWindow::openSerialPort()
{

    QString str;
    QString name;
    QString name2;
    QString name3;
    QDir dirconf;
    QDateTime date=QDateTime::currentDateTime();
    str = "conf/";
    dirconf.mkpath(str);
    name = date.toString("yyyy.MM.dd");
    name.prepend(str);
    name.append("_appa.txt");
    std::string m_name = name.toStdString();

    name2 = date.toString("yyyy.MM.dd");
    name2.prepend(str);
    name2.append("_other.txt");
    std::string m_name2 = name2.toStdString();

    name3 = date.toString("yyyy.MM.dd");
    name3.prepend(str);
    name3.append("_keithley.txt");
    std::string m_name3 = name3.toStdString();

    QFile file(QString::fromStdString(m_name));
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString str_r;

    std::string str_APPA1_SN;
    std::string str_APPA2_SN;
    std::string str_APPA3_SN;
    std::string str_APPA4_SN;

    for (int rr=0; rr<4; rr++)
    {
        str_r = file.readLine();
        str_r.remove("\n");
        if (str_r == "end") break;

        switch (rr) {
        case 0:
            class_port_APPA_1->set_com_port(str_r);

            str_APPA1_SN="APPA 1 SN: ";
            str_APPA1_SN.append(class_port_APPA_1->get_sn());
            lineEdit_A1->setText(QString::fromStdString(str_APPA1_SN));

            lineEdit_A1->setEnabled(true);
            checkBox_A1_X->setEnabled(true);
            checkBox_A1_Y->setEnabled(true);
            checkBox_A1_Y->setChecked(true);
            Button_Clear_A1->setEnabled(true);
            break;
        case 1:
            class_port_APPA_2->set_com_port(str_r);

            str_APPA2_SN="APPA 2 SN: ";
            str_APPA2_SN.append(class_port_APPA_2->get_sn());
            lineEdit_A2->setText(QString::fromStdString(str_APPA2_SN));

            lineEdit_A2->setEnabled(true);
            checkBox_A2_X->setEnabled(true);
            checkBox_A2_Y->setEnabled(true);
            checkBox_A2_Y->setChecked(true);
            Button_Clear_A2->setEnabled(true);
            break;
        case 2:
            class_port_APPA_3->set_com_port(str_r);

            str_APPA3_SN="APPA 3 SN: ";
            str_APPA3_SN.append(class_port_APPA_3->get_sn());
            lineEdit_A3->setText(QString::fromStdString(str_APPA3_SN));

            lineEdit_A3->setEnabled(true);
            checkBox_A3_X->setEnabled(true);
            checkBox_A3_Y->setEnabled(true);
            checkBox_A3_Y->setChecked(true);
            Button_Clear_A3->setEnabled(true);
            break;
        case 3:
            class_port_APPA_4->set_com_port(str_r);

            str_APPA4_SN="APPA 4 SN: ";
            str_APPA4_SN.append(class_port_APPA_4->get_sn());
            lineEdit_A4->setText(QString::fromStdString(str_APPA4_SN));

            lineEdit_A4->setEnabled(true);
            checkBox_A4_X->setEnabled(true);
            checkBox_A4_Y->setEnabled(true);
            checkBox_A4_Y->setChecked(true);
            Button_Clear_A4->setEnabled(true);

            break;
        }

    }

    file.flush();
    file.close();


    QFile file2(QString::fromStdString(m_name2));
    file2.open(QIODevice::ReadOnly | QIODevice::Text);
    QString str_r2;

    for (int rr=0; rr<=4; rr++)
    {
        str_r2 = file2.readLine();
        str_r2.remove("\n");
        if (str_r2 == "end") break;

        class_port_Lock_in_1->set_com_port(str_r2);
        lineEdit_L1->setText(tr("Lock-in on"));
        lineEdit_L2->setText(tr("Lock-in on"));
        lineEdit_L3->setText(tr("Lock-in on"));
        lineEdit_L4->setText(tr("Lock-in on"));

        lineEdit_L1->setEnabled(true);
        checkBox_L1_X->setEnabled(true);
        checkBox_L1_Y->setEnabled(true);
        Button_Clear_L1->setEnabled(true);
        lineEdit_L2->setEnabled(true);
        checkBox_L2_X->setEnabled(true);
        checkBox_L2_Y->setEnabled(true);
        Button_Clear_L2->setEnabled(true);
        lineEdit_L3->setEnabled(true);
        checkBox_L3_X->setEnabled(true);
        checkBox_L3_Y->setEnabled(true);
        Button_Clear_L3->setEnabled(true);
        lineEdit_L4->setEnabled(true);
        checkBox_L4_X->setEnabled(true);
        checkBox_L4_Y->setEnabled(true);
        Button_Clear_L4->setEnabled(true);

        checkBox_L1_Y->setChecked(true);
        checkBox_L2_Y->setChecked(true);
        checkBox_L3_Y->setChecked(true);
        checkBox_L4_Y->setChecked(true);

    }

    file2.flush();
    file2.close();

    QFile file3(QString::fromStdString(m_name3));
    file3.open(QIODevice::ReadOnly | QIODevice::Text);
    QString str_r3;

    for (int rr=0; rr<=4; rr++)
    {
        str_r3 = file3.readLine();
        str_r3.remove("\n");
        if (str_r3 == "end") break;

        class_port_keithley_1->set_com_port(str_r3);
        lineEdit_K1->setText(tr("Keithley on"));
        lineEdit_K2->setText(tr("Keithley on"));

        lineEdit_K1->setEnabled(true);
        checkBox_K1_X->setEnabled(true);
        checkBox_K1_Y->setEnabled(true);
        Button_Clear_K1->setEnabled(true);
        lineEdit_K2->setEnabled(true);
        checkBox_K2_X->setEnabled(true);
        checkBox_K2_Y->setEnabled(true);
        Button_Clear_K2->setEnabled(true);

        checkBox_K1_Y->setChecked(true);
        checkBox_K2_Y->setChecked(true);
    }

    file3.flush();
    file3.close();

}

void MainWindow::closeSerialPort()
{
    /*
    if (serial->isOpen())
        serial->close();*/
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About APPA"),
                       tr("The <b>APPA</b> ..." ));
}

void MainWindow::writeData()
{

    if (1==number_of_point[0] or 0==number_of_point_X){
    result_appa[0] = class_port_APPA_1->m_read();

    lineEdit_A1->setText( QString("APPA 1: %1").arg(result_appa[0]));
    if (0==number_of_point_X) result_X=result_appa[0];
    }else lineEdit_A1->setText( QString("APPA 1: off"));

    if (1==number_of_point[1] or 1==number_of_point_X){
    result_appa[1] = class_port_APPA_2->m_read();
    lineEdit_A2->setText( QString("APPA 2: %1").arg(result_appa[1]));
    if (1==number_of_point_X) result_X=result_appa[1];
    }else lineEdit_A2->setText( QString("APPA 2: off"));

    if (1==number_of_point[2] or 2==number_of_point_X){
    result_appa[2] = class_port_APPA_3->m_read();
    lineEdit_A3->setText( QString("APPA 3: %1").arg(result_appa[2]));
    if (2==number_of_point_X) result_X=result_appa[2];
    }else lineEdit_A3->setText( QString("APPA 3: off"));

    if (1==number_of_point[3] or 3==number_of_point_X){
    result_appa[3] = class_port_APPA_4->m_read();
    lineEdit_A4->setText( QString("APPA 4: %1").arg(result_appa[3]));
    if (3==number_of_point_X) result_X=result_appa[3];
    }else lineEdit_A4->setText( QString("APPA 4: off"));

    //Keithley

    if (
                (1==number_of_point[4] or 4==number_of_point_X)
                or
                (1==number_of_point[5] or 5==number_of_point_X)
       )
    {
        class_port_keithley_1->m_read();

        result_keithley[0] = class_port_keithley_1->get_result(0);
        lineEdit_K1->setText( QString("keithley 1: %1").arg(result_keithley[0]));

        result_keithley[1] = class_port_keithley_1->get_result(1);
        lineEdit_K2->setText( QString("keithley 2: %1").arg(result_keithley[1]));

        if (4==number_of_point_X) result_X=result_keithley[0];
        if (5==number_of_point_X) result_X=result_keithley[1];

    }

    //lock-in

    if ((
                (1==number_of_point[8] or 8==number_of_point_X)
                or
                (1==number_of_point[9] or 9==number_of_point_X)
                ) or (
                (1==number_of_point[10] or 10==number_of_point_X)
                or
                (1==number_of_point[11] or 11==number_of_point_X)
        ))
    {
        class_port_Lock_in_1->m_read();
        checkBox_L_1000->setEnabled(true);

        result_lock_in[0] = class_port_Lock_in_1->get_result(0);
        lineEdit_L1->setText( QString("Lock-in 1: %1").arg(result_lock_in[0]));

        result_lock_in[1] = class_port_Lock_in_1->get_result(1);
        lineEdit_L2->setText( QString("Lock-in 2: %1").arg(result_lock_in[1]));

        result_lock_in[2] = class_port_Lock_in_1->get_result(2);
        lineEdit_L3->setText( QString("Lock-in 3: %1").arg(result_lock_in[2]));

        result_lock_in[3] = class_port_Lock_in_1->get_result(3);
        lineEdit_L4->setText( QString("Lock-in 4: %1").arg(result_lock_in[3]));

        if (8==number_of_point_X) result_X=result_lock_in[0];
        if (9==number_of_point_X) result_X=result_lock_in[1];
        if (10==number_of_point_X) result_X=result_lock_in[2];
        if (11==number_of_point_X) result_X=result_lock_in[3];
    }

    //
    result_X=class_temp_1->get_temp(QString::number(result_X,'f',3));

    if (20 != number_of_point_X) d_plot->get_x_result(result_X);else  d_plot->get_x_result(0);

    if (1==number_of_point[0])  d_plot->get_all_results(result_appa[0],0);
    if (1==number_of_point[1])  d_plot->get_all_results(result_appa[1],1);
    if (1==number_of_point[2])  d_plot->get_all_results(result_appa[2],2);
    if (1==number_of_point[3])  d_plot->get_all_results(result_appa[3],3);

    if (1==number_of_point[4])  d_plot->get_all_results(result_keithley[0],4);
    if (1==number_of_point[5])  d_plot->get_all_results(result_keithley[1],5);

    if (1==number_of_point[8])  d_plot->get_all_results((checkBox_L_1000->isChecked() ? result_lock_in[0]*1000 :result_lock_in[0]),8);
    if (1==number_of_point[9])  d_plot->get_all_results((checkBox_L_1000->isChecked() ? result_lock_in[1]*1000 :result_lock_in[1]),9);
    if (1==number_of_point[10])  d_plot->get_all_results(result_lock_in[2],10);
    if (1==number_of_point[11])  d_plot->get_all_results(result_lock_in[3],11);




    W_File->write_to_file(result_X,result_appa[0],result_appa[1],result_appa[2],result_appa[3],result_keithley[0],result_keithley[1],0,0,result_lock_in[0],result_lock_in[1],result_lock_in[2],result_lock_in[3]);
}

void MainWindow::Temp()
{
    float Temp_x_float = lineEdit_Temp_X->text().toFloat();
    QString Temp_X= QString::number(Temp_x_float,'f',3);
    float Temp_T;
    Temp_T=class_temp_1->get_temp(Temp_X);
    lineEdit_Temp_T->setText( QString("%1").arg(Temp_T));
}

void MainWindow::ScrollArea_Setting_K()
{
    dialog_K1 = new dialog_K;
    dialog_K1->show();
}

void MainWindow::Now_Replot()
{
    QString x_min= lineEdit_Plot_x_min->text();
    QString x_max = lineEdit_Plot_x_max->text();
    QString y_min = lineEdit_Plot_y_min->text();
    QString y_max = lineEdit_Plot_y_max->text();
    QStringList list_x_min = x_min.split(':');
    QStringList list_x_max = x_max.split(':');
    QStringList list_y_min = y_min.split(':');
    QStringList list_y_max = y_max.split(':');
    list_x_min.prepend(":");
    list_x_max.prepend(":");
    list_y_min.prepend(":");
    list_y_max.prepend(":");

    d_plot->now_replot(
                list_x_min[list_x_min.size()-1].toFloat(),
                list_x_max[list_x_max.size()-1].toFloat(),
                list_y_min[list_y_min.size()-1].toFloat(),
                list_y_max[list_x_max.size()-1].toFloat()
                );
}

void MainWindow::save_points()
{
    switch (int_save_points) {
    case 0: lineEdit1->setText( QString("1 point: %1").arg(result_X));break;
    case 1: lineEdit2->setText( QString("2 point: %1").arg(result_X));break;
    case 2: lineEdit3->setText( QString("3 point: %1").arg(result_X));break;
    }
    int_save_points++;
    if (int_save_points==3) int_save_points=0;
}

void MainWindow::Open_F1()
{
    class_open_F1->open_file();
    class_open_F1->show();
}

void MainWindow::Open_F2()
{
    class_open_F2->open_file();
    class_open_F2->show();
}

void MainWindow::get_file_name_F1()
{
    class_open_F1->hide();

    int F_number = class_open_F1->get_number_of_bool();
    QString F_name = QString::fromStdString(class_open_F1->get_file_name());
    QStringList list_F_name;
    list_F_name = F_name.split('/');
    QFile file(F_name);
    QString str_file;
    QStringList list_file;

    lineEdit_F1->setText(list_F_name[(list_F_name.size()-1)]);

    file.open(QIODevice::ReadOnly | QIODevice::Text);
    while(1)
    {
        str_file= file.readLine();
        str_file.remove("\n");
        list_file = str_file.split('\t');
        if (0==list_file[0]) break;

        d_plot->appendPoint_F1(list_file[0].toFloat(),list_file[F_number].toFloat());
    }
    file.flush();
    file.close();
}

void MainWindow::get_file_name_F2()
{
    class_open_F2->hide();

    int F_number = class_open_F2->get_number_of_bool();
    QString F_name = QString::fromStdString(class_open_F2->get_file_name());
    QStringList list_F_name;
    list_F_name = F_name.split('/');
    QFile file(F_name);
    QString str_file;
    QStringList list_file;

    lineEdit_F2->setText(list_F_name[(list_F_name.size()-1)]);

    file.open(QIODevice::ReadOnly | QIODevice::Text);
    while(1)
    {
        str_file= file.readLine();
        str_file.remove("\n");
        list_file = str_file.split('\t');
        if (0==list_file[0]) break;

        d_plot->appendPoint_F2(list_file[0].toFloat(),list_file[F_number].toFloat());
    }

    file.flush();
    file.close();
}

void MainWindow::appendPoints( bool on )
{
    if ( on )
    {
        d_plot->append( d_timerCount->value(), 1000
                        //d_randomCount->value()
                        );
        W_File->create_new_file();
        hBox_A->setEnabled(false);
        hBox_K->setEnabled(false);
        hBox_L->setEnabled(false);
    }
    else
    {
        d_plot->stop();
        hBox_A->setEnabled(true);
        hBox_K->setEnabled(true);
        hBox_L->setEnabled(true);
    }

}

void MainWindow::showRunning( bool running )
{
    d_timerCount->setEnabled( !running );
    d_startAction->setChecked( running );
    d_startAction->setText( running ? "Stop" : "Start" );
    d_symbolType->setEnabled(running ? false : true );
}

void MainWindow::showElapsed( int ms )
{
    QString text;
    text.setNum( ms );
    text += " ms";

    statusBar()->showMessage( text );
}

void MainWindow::initWhatsThis()
{
    const char *Zooming =
        "Zooming is enabled until the selected area gets "
        "too small for the significance on the axes.\n\n"
        "You can zoom in using the left mouse button.\n"
        "The middle mouse is used for the panning.\n"
        "The right mouse button is used to go back to the previous zoomed area.\n"
        "The right mouse button + Ctrl are used to unzoom completely.";

    //const char *text2 = "Number of points.";

    const char *Delay =
        "Delay between two points.";

    const char *Start =
        "Start.\n\n"
        "";

    const char *Clear_all = "Remove all points.";
    const char *Replot = "Replot.";


    d_plot->setWhatsThis( Zooming );
    //d_randomCount->setWhatsThis( text2 );
    d_timerCount->setWhatsThis( Delay );
    d_startAction->setWhatsThis( Start );
    d_clearAction->setWhatsThis( Clear_all );
    Button_replot->setWhatsThis( Replot );
}

