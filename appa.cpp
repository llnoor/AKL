#include <qglobal.h>
#include <qtimer.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_layout.h>
#include <qwt_scale_widget.h>
#include <qwt_scale_draw.h>
#include <qwt_math.h>
#include "scrollzoomer.h"
#include "appa.h"
#include <cmath>
#include "mainwindow.h"

const unsigned int c_rangeMax = 5000;
int x_1=0;
float x_min=-10;
float x_max=300;
float y_min=-10;
float y_max=10;

class Zoomer: public ScrollZoomer
{
public:
    Zoomer( QWidget *canvas ):
        ScrollZoomer( canvas )
    {
#if 0
        setRubberBandPen( QPen( Qt::red, 2, Qt::DotLine ) );
#else
        setRubberBandPen( QPen( Qt::red ) );
#endif
    }

    virtual QwtText trackerTextF( const QPointF &pos ) const
    {
        QColor bg( Qt::white );

        QwtText text = QwtPlotZoomer::trackerTextF( pos );
        text.setBackgroundBrush( QBrush( bg ) );
        return text;
    }

    virtual void rescale()
    {
        QwtScaleWidget *scaleWidget = plot()->axisWidget( yAxis() );
        QwtScaleDraw *sd = scaleWidget->scaleDraw();

        double minExtent = 0.0;
        if ( zoomRectIndex() > 0 )
        {
            // When scrolling in vertical direction
            // the plot is jumping in horizontal direction
            // because of the different widths of the labels
            // So we better use a fixed extent.

            minExtent = sd->spacing() + sd->maxTickLength() + 1;
            minExtent += sd->labelSize(
                scaleWidget->font(), c_rangeMax ).width();
        }

        sd->setMinimumExtent( minExtent );

        ScrollZoomer::rescale();
    }
};

APPA::APPA( QWidget *parent ):
    IncrementalPlot( parent ),
    d_timer( 0 ),
    d_timerCount( 0 )
{
    setFrameStyle( QFrame::NoFrame );
    setLineWidth( 0 );

    plotLayout()->setAlignCanvasToScales( true );

    QwtPlotGrid *grid = new QwtPlotGrid;
    grid->setMajorPen( Qt::gray, 0, Qt::DotLine );
    grid->attach( this );
    //grid->setAxes();

    setCanvasBackground( QColor( 29, 100, 141 ) ); // nice blue

    setAxisScale( xBottom, x_min, x_max );
    setAxisScale( yLeft, y_min, y_max );

    setAxisScale(xTop, x_min, x_max );
    setAxisScale(yRight , y_min, y_max );

    replot();

    for (int i=0; i<CurvCnt; i++)
    number_of_point[i]=0;

    // enable zooming
    //( void ) new Zoomer( canvas() ); //if you use this code, then LeftButton for the zooming, MidButton for zoom out by 1;  RightButton: zoom out to full size
    //or you can use next code for: LeftButton for the zooming; MidButton for the panning; RightButton: zoom out by 1; Ctrl+RighButton: zoom out to full size

    Zoomer* zoomer = new Zoomer( canvas() );
    zoomer->setMousePattern( QwtEventPattern::MouseSelect2,
        Qt::RightButton, Qt::ControlModifier );
    zoomer->setMousePattern( QwtEventPattern::MouseSelect3,
        Qt::RightButton );

    QwtPlotPanner *panner = new QwtPlotPanner( canvas() );
    panner->setMouseButton( Qt::MidButton );
}

QSize APPA::sizeHint() const
{
    return QSize( 540, 400 );
}

void APPA::get_bool(bool new_bool, int new_int)
{
    number_of_point[new_int]=new_bool;
}

void APPA::get_all_results(float result, int new_int)
{
    all_results[new_int]=result;
}

void APPA::get_x_result(float result)
{
    x_result=result;
}

void APPA::appendPoint()
{

    Q_EMIT running_writeData( true );

    if (1==number_of_point[0]){IncrementalPlot::appendPoint0( QPointF( x_result, all_results[0] ) );}
    if (1==number_of_point[1]){IncrementalPlot::appendPoint1( QPointF( x_result, all_results[1] ) );}
    if (1==number_of_point[2]){IncrementalPlot::appendPoint2( QPointF( x_result, all_results[2] ) );}
    if (1==number_of_point[3]){IncrementalPlot::appendPoint3( QPointF( x_result, all_results[3] ) );}
    if (1==number_of_point[4]){IncrementalPlot::appendPoint4( QPointF( x_result, all_results[4] ) );}
    if (1==number_of_point[5]){IncrementalPlot::appendPoint5( QPointF( x_result, all_results[5] ) );}
    if (1==number_of_point[6]){IncrementalPlot::appendPoint6( QPointF( x_result, all_results[6] ) );}
    if (1==number_of_point[7]){IncrementalPlot::appendPoint7( QPointF( x_result, all_results[7] ) );}
    if (1==number_of_point[8]){IncrementalPlot::appendPoint8( QPointF( x_result, all_results[8] ) );}
    if (1==number_of_point[9]){IncrementalPlot::appendPoint9( QPointF( x_result, all_results[9] ) );}
    if (1==number_of_point[10]){IncrementalPlot::appendPoint10( QPointF( x_result, all_results[10] ) );}
    if (1==number_of_point[11]){IncrementalPlot::appendPoint11( QPointF( x_result, all_results[11] ) );}
    if (1==number_of_point[12]){IncrementalPlot::appendPoint12( QPointF( x_result, all_results[12] ) );}
    if (1==number_of_point[13]){IncrementalPlot::appendPoint13( QPointF( x_result, all_results[13] ) );}
}

void APPA::now_replot(float new_x_min,float new_x_max, float new_y_min,float new_y_max)
{

    setAxisScale( xBottom, new_x_min, new_x_max );
    setAxisScale( yLeft, new_y_min, new_y_max );

    setAxisScale(xTop, new_x_min, new_x_max );
    setAxisScale(yRight, new_y_min, new_y_max );

    x_min=new_x_min;
    x_max=new_x_max;
    y_min=new_y_min;
    y_max=new_y_max;

    replot();
}

void APPA::appendPoint_F1(float x, float y)
{
    IncrementalPlot::appendPoint12( QPointF( x, y ) );//F1

}

void APPA::appendPoint_F2(float x, float y)
{
    IncrementalPlot::appendPoint13( QPointF( x, y ) );//F1
}

void APPA::append( int timeout, int count )
{
    if ( !d_timer )
    {
        d_timer = new QTimer( this );
        connect( d_timer, SIGNAL( timeout() ), SLOT( appendPoint() ) );
    }

    d_timerCount = count;

    Q_EMIT running( true );
    d_timeStamp.start();

    QwtPlotCanvas *plotCanvas = qobject_cast<QwtPlotCanvas *>( canvas() );
    plotCanvas->setPaintAttribute( QwtPlotCanvas::BackingStore, false );

    d_timer->start( timeout );
}

void APPA::stop()
{
    Q_EMIT elapsed( d_timeStamp.elapsed() );

    if ( d_timer )
    {
        d_timer->stop();
        Q_EMIT running( false );
        Q_EMIT running_writeData( false );
    }

    QwtPlotCanvas *plotCanvas = qobject_cast<QwtPlotCanvas *>( canvas() );
    plotCanvas->setPaintAttribute( QwtPlotCanvas::BackingStore, true );
}

void APPA::clear()
{
    clearPoints();
    clearPoints0();
    clearPoints1();
    clearPoints2();
    clearPoints3();
    clearPoints4();
    clearPoints5();
    clearPoints6();
    clearPoints7();
    clearPoints8();
    clearPoints9();
    clearPoints10();
    clearPoints11();
    //clearPoints12();
    //clearPoints13();
    replot();
}

void APPA::Clear_A1(){clearPoints0();replot();}
void APPA::Clear_A2(){clearPoints1();replot();}
void APPA::Clear_A3(){clearPoints2();replot();}
void APPA::Clear_A4(){clearPoints3();replot();}

void APPA::Clear_K1(){clearPoints4();replot();}
void APPA::Clear_K2(){clearPoints5();replot();}
void APPA::Clear_K3(){clearPoints6();replot();}
void APPA::Clear_K4(){clearPoints7();replot();}

void APPA::Clear_L1(){clearPoints8();replot();}
void APPA::Clear_L2(){clearPoints9();replot();}
void APPA::Clear_L3(){clearPoints10();replot();}
void APPA::Clear_L4(){clearPoints11();replot();}

void APPA::Clear_F1(){clearPoints12();replot();}
void APPA::Clear_F2(){clearPoints13();replot();}




