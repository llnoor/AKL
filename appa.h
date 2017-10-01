#ifndef APPA_H
#define APPA_H

#include "incrementalplot.h"
#include <qdatetime.h>
#define CurvCnt 14


class QTimer;

class APPA: public IncrementalPlot
{
    Q_OBJECT

public:
    APPA( QWidget *parent );
    virtual QSize sizeHint() const;

Q_SIGNALS:
    void running( bool );
    void elapsed( int ms );
    void running_writeData( bool );
    void running_readData( bool );


public Q_SLOTS:
    void clear();
    void Clear_A1();
    void Clear_A2();
    void Clear_A3();
    void Clear_A4();
    void Clear_K1();
    void Clear_K2();
    void Clear_K3();
    void Clear_K4();
    void Clear_L1();
    void Clear_L2();
    void Clear_L3();
    void Clear_L4();
    void Clear_F1();
    void Clear_F2();

    void stop();
    void append( int timeout, int count );

    void get_all_results(float , int );
    void get_x_result(float );
    void get_bool(bool , int );
    void appendPoint_F1(float, float);
    void appendPoint_F2(float, float);
    void now_replot(float ,float ,float ,float );

private Q_SLOTS:
    void appendPoint();


private:
    bool appa_Type;
    bool number_of_point[CurvCnt];
    float all_results[CurvCnt];
    float x_result;
    void initCurve();

    QTimer *d_timer;
    int d_timerCount;

    QTime d_timeStamp;
};

#endif // APPA_H
