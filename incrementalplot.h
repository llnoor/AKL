#ifndef _INCREMENTALPLOT_H_
#define _INCREMENTALPLOT_H_ 1

#include <qwt_plot.h>
#define CurvCnt 14

class QwtPlotCurve;
class QwtPlotDirectPainter;


class IncrementalPlot : public QwtPlot
{
    Q_OBJECT

public:
    IncrementalPlot( QWidget *parent = NULL );
    virtual ~IncrementalPlot();

    void appendPoint( const QPointF & );
    void clearPoints();
    void appendPoint0( const QPointF & );
    void clearPoints0();
    void appendPoint1( const QPointF & );
    void clearPoints1();
    void appendPoint2( const QPointF & );
    void clearPoints2();
    void appendPoint3( const QPointF & );
    void clearPoints3();
    void appendPoint4( const QPointF & );
    void clearPoints4();
    void appendPoint5( const QPointF & );
    void clearPoints5();
    void appendPoint6( const QPointF & );
    void clearPoints6();
    void appendPoint7( const QPointF & );
    void clearPoints7();
    void appendPoint8( const QPointF & );
    void clearPoints8();
    void appendPoint9( const QPointF & );
    void clearPoints9();
    void appendPoint10( const QPointF & );
    void clearPoints10();
    void appendPoint11( const QPointF & );
    void clearPoints11();
    void appendPoint12( const QPointF & );
    void clearPoints12();
    void appendPoint13( const QPointF & );
    void clearPoints13();


public Q_SLOTS:
    void showSymbols( bool );

private:
    //const int CurvCnt;
    QwtPlotCurve *d_curve;
    QwtPlotCurve *d_curves[CurvCnt];
    QwtPlotDirectPainter *d_directPainter;
};

#endif // _INCREMENTALPLOT_H_
