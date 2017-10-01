#include <qwt_plot.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_curve.h>
#include <qwt_symbol.h>
#include <qwt_plot_directpainter.h>
#include <qwt_painter.h>
#include "incrementalplot.h"
#include <qpaintengine.h>

class CurveData: public QwtArraySeriesData<QPointF>
{
public:
    CurveData()
    {
    }

    virtual QRectF boundingRect() const
    {
        if ( d_boundingRect.width() < 0.0 )
            d_boundingRect = qwtBoundingRect( *this );

        return d_boundingRect;
    }

    inline void append( const QPointF &point )
    {

        d_samples += point;
    }

    void clear()
    {
        d_samples.clear();
        d_samples.squeeze();
        d_boundingRect = QRectF( 0.0, 0.0, -1.0, -1.0 );
    }
};

IncrementalPlot::IncrementalPlot( QWidget *parent ):
    QwtPlot( parent )//,d_curve( NULL )
{
    d_directPainter = new QwtPlotDirectPainter( this );

    if ( QwtPainter::isX11GraphicsSystem() )
    {
#if QT_VERSION < 0x050000
        canvas()->setAttribute( Qt::WA_PaintOutsidePaintEvent, true );
#endif
        canvas()->setAttribute( Qt::WA_PaintOnScreen, true );
    }

    d_curve = new QwtPlotCurve( "Test Curve" );
    d_curve->setData( new CurveData() );

    for(int i = 0; i < CurvCnt; i++ )
    {
        d_curves[i] = new QwtPlotCurve( "Test Curve 1-10" );
        d_curves[i]->setData( new CurveData() );
    }

    showSymbols( true );

    d_curve->attach( this );
    for(int i = 0; i < CurvCnt; i++ )
    {
        d_curves[i]->attach( this );
    }

    setAutoReplot( false );
}

IncrementalPlot::~IncrementalPlot()
{
    delete d_curve;
    for(int i = 0; i < CurvCnt; i++ )
    {
        delete d_curves[i];
    }
}

void IncrementalPlot::appendPoint( const QPointF &point )
{
    CurveData *data = static_cast<CurveData *>( d_curve->data() );
    data->append( point );

    const bool doClip = !canvas()->testAttribute( Qt::WA_PaintOnScreen );
    if ( doClip )
    {
        /*
           Depending on the platform setting a clip might be an important
           performance issue. F.e. for Qt Embedded this reduces the
           part of the backing store that has to be copied out - maybe
           to an unaccelerated frame buffer device.
         */
        const QwtScaleMap xMap = canvasMap( d_curve->xAxis() );
        const QwtScaleMap yMap = canvasMap( d_curve->yAxis() );

        QRegion clipRegion;

        const QSize symbolSize = d_curve->symbol()->size();
        QRect r( 0, 0, symbolSize.width() + 2, symbolSize.height() + 2 );



        const QPointF center =
            QwtScaleMap::transform( xMap, yMap, point );
        r.moveCenter( center.toPoint() );
        clipRegion += r;

        d_directPainter->setClipRegion( clipRegion );
    }

    d_directPainter->drawSeries( d_curve,
        data->size() - 1, data->size() - 1 );
}

void IncrementalPlot::clearPoints()
{
    CurveData *data = static_cast<CurveData *>( d_curve->data() );
    data->clear();

    replot();
}

void IncrementalPlot::appendPoint0( const QPointF &point )
{
    CurveData *data = static_cast<CurveData *>( d_curves[0]->data() );
    data->append( point );

    const bool doClip = !canvas()->testAttribute( Qt::WA_PaintOnScreen );
    if ( doClip )
    {
        /*
           Depending on the platform setting a clip might be an important
           performance issue. F.e. for Qt Embedded this reduces the
           part of the backing store that has to be copied out - maybe
           to an unaccelerated frame buffer device.
         */
        const QwtScaleMap xMap = canvasMap( d_curves[0]->xAxis() );
        const QwtScaleMap yMap = canvasMap( d_curves[0]->yAxis() );

        QRegion clipRegion;

        const QSize symbolSize = d_curves[0]->symbol()->size();
        QRect r( 0, 0, symbolSize.width() + 2, symbolSize.height() + 2 );



        const QPointF center =
            QwtScaleMap::transform( xMap, yMap, point );
        r.moveCenter( center.toPoint() );
        clipRegion += r;

        d_directPainter->setClipRegion( clipRegion );
    }

    d_directPainter->drawSeries( d_curves[0],
        data->size() - 1, data->size() - 1 );
}

void IncrementalPlot::clearPoints0()
{
    CurveData *data = static_cast<CurveData *>( d_curves[0]->data() );
    data->clear();

    replot();
}

void IncrementalPlot::appendPoint1( const QPointF &point )
{
    CurveData *data = static_cast<CurveData *>( d_curves[1]->data() );
    data->append( point );

    const bool doClip = !canvas()->testAttribute( Qt::WA_PaintOnScreen );
    if ( doClip )
    {
        /*
           Depending on the platform setting a clip might be an important
           performance issue. F.e. for Qt Embedded this reduces the
           part of the backing store that has to be copied out - maybe
           to an unaccelerated frame buffer device.
         */
        const QwtScaleMap xMap = canvasMap( d_curves[1]->xAxis() );
        const QwtScaleMap yMap = canvasMap( d_curves[1]->yAxis() );

        QRegion clipRegion;

        const QSize symbolSize = d_curves[1]->symbol()->size();
        QRect r( 0, 0, symbolSize.width() + 2, symbolSize.height() + 2 );



        const QPointF center =
            QwtScaleMap::transform( xMap, yMap, point );
        r.moveCenter( center.toPoint() );
        clipRegion += r;

        d_directPainter->setClipRegion( clipRegion );
    }

    d_directPainter->drawSeries( d_curves[1],
        data->size() - 1, data->size() - 1 );
}

void IncrementalPlot::clearPoints1()
{
    CurveData *data = static_cast<CurveData *>( d_curves[1]->data() );
    data->clear();

    replot();
}

void IncrementalPlot::appendPoint2( const QPointF &point )
{
    CurveData *data = static_cast<CurveData *>( d_curves[2]->data() );
    data->append( point );

    const bool doClip = !canvas()->testAttribute( Qt::WA_PaintOnScreen );
    if ( doClip )
    {
        /*
           Depending on the platform setting a clip might be an important
           performance issue. F.e. for Qt Embedded this reduces the
           part of the backing store that has to be copied out - maybe
           to an unaccelerated frame buffer device.
         */
        const QwtScaleMap xMap = canvasMap( d_curves[2]->xAxis() );
        const QwtScaleMap yMap = canvasMap( d_curves[2]->yAxis() );

        QRegion clipRegion;

        const QSize symbolSize = d_curves[2]->symbol()->size();
        QRect r( 0, 0, symbolSize.width() + 2, symbolSize.height() + 2 );



        const QPointF center =
            QwtScaleMap::transform( xMap, yMap, point );
        r.moveCenter( center.toPoint() );
        clipRegion += r;

        d_directPainter->setClipRegion( clipRegion );
    }

    d_directPainter->drawSeries( d_curves[2],
        data->size() - 1, data->size() - 1 );
}

void IncrementalPlot::clearPoints2()
{
    CurveData *data = static_cast<CurveData *>( d_curves[2]->data() );
    data->clear();

    replot();
}

void IncrementalPlot::appendPoint3( const QPointF &point )
{
    CurveData *data = static_cast<CurveData *>( d_curves[3]->data() );
    data->append( point );

    const bool doClip = !canvas()->testAttribute( Qt::WA_PaintOnScreen );
    if ( doClip )
    {
        /*
           Depending on the platform setting a clip might be an important
           performance issue. F.e. for Qt Embedded this reduces the
           part of the backing store that has to be copied out - maybe
           to an unaccelerated frame buffer device.
         */
        const QwtScaleMap xMap = canvasMap( d_curves[3]->xAxis() );
        const QwtScaleMap yMap = canvasMap( d_curves[3]->yAxis() );

        QRegion clipRegion;

        const QSize symbolSize = d_curves[3]->symbol()->size();
        QRect r( 0, 0, symbolSize.width() + 2, symbolSize.height() + 2 );



        const QPointF center =
            QwtScaleMap::transform( xMap, yMap, point );
        r.moveCenter( center.toPoint() );
        clipRegion += r;

        d_directPainter->setClipRegion( clipRegion );
    }

    d_directPainter->drawSeries( d_curves[3],
        data->size() - 1, data->size() - 1 );
}

void IncrementalPlot::clearPoints3()
{
    CurveData *data = static_cast<CurveData *>( d_curves[3]->data() );
    data->clear();

    replot();
}

void IncrementalPlot::appendPoint4( const QPointF &point )
{
    CurveData *data = static_cast<CurveData *>( d_curves[4]->data() );
    data->append( point );

    const bool doClip = !canvas()->testAttribute( Qt::WA_PaintOnScreen );
    if ( doClip )
    {
        /*
           Depending on the platform setting a clip might be an important
           performance issue. F.e. for Qt Embedded this reduces the
           part of the backing store that has to be copied out - maybe
           to an unaccelerated frame buffer device.
         */
        const QwtScaleMap xMap = canvasMap( d_curves[4]->xAxis() );
        const QwtScaleMap yMap = canvasMap( d_curves[4]->yAxis() );

        QRegion clipRegion;

        const QSize symbolSize = d_curves[4]->symbol()->size();
        QRect r( 0, 0, symbolSize.width() + 2, symbolSize.height() + 2 );



        const QPointF center =
            QwtScaleMap::transform( xMap, yMap, point );
        r.moveCenter( center.toPoint() );
        clipRegion += r;

        d_directPainter->setClipRegion( clipRegion );
    }

    d_directPainter->drawSeries( d_curves[4],
        data->size() - 1, data->size() - 1 );
}

void IncrementalPlot::clearPoints4()
{
    CurveData *data = static_cast<CurveData *>( d_curves[4]->data() );
    data->clear();

    replot();
}

void IncrementalPlot::appendPoint5( const QPointF &point )
{
    CurveData *data = static_cast<CurveData *>( d_curves[5]->data() );
    data->append( point );

    const bool doClip = !canvas()->testAttribute( Qt::WA_PaintOnScreen );
    if ( doClip )
    {
        /*
           Depending on the platform setting a clip might be an important
           performance issue. F.e. for Qt Embedded this reduces the
           part of the backing store that has to be copied out - maybe
           to an unaccelerated frame buffer device.
         */
        const QwtScaleMap xMap = canvasMap( d_curves[5]->xAxis() );
        const QwtScaleMap yMap = canvasMap( d_curves[5]->yAxis() );

        QRegion clipRegion;

        const QSize symbolSize = d_curves[5]->symbol()->size();
        QRect r( 0, 0, symbolSize.width() + 2, symbolSize.height() + 2 );



        const QPointF center =
            QwtScaleMap::transform( xMap, yMap, point );
        r.moveCenter( center.toPoint() );
        clipRegion += r;

        d_directPainter->setClipRegion( clipRegion );
    }

    d_directPainter->drawSeries( d_curves[5],
        data->size() - 1, data->size() - 1 );
}

void IncrementalPlot::clearPoints5()
{
    CurveData *data = static_cast<CurveData *>( d_curves[5]->data() );
    data->clear();

    replot();
}

void IncrementalPlot::appendPoint6( const QPointF &point )
{
    CurveData *data = static_cast<CurveData *>( d_curves[6]->data() );
    data->append( point );

    const bool doClip = !canvas()->testAttribute( Qt::WA_PaintOnScreen );
    if ( doClip )
    {
        /*
           Depending on the platform setting a clip might be an important
           performance issue. F.e. for Qt Embedded this reduces the
           part of the backing store that has to be copied out - maybe
           to an unaccelerated frame buffer device.
         */
        const QwtScaleMap xMap = canvasMap( d_curves[6]->xAxis() );
        const QwtScaleMap yMap = canvasMap( d_curves[6]->yAxis() );

        QRegion clipRegion;

        const QSize symbolSize = d_curves[6]->symbol()->size();
        QRect r( 0, 0, symbolSize.width() + 2, symbolSize.height() + 2 );



        const QPointF center =
            QwtScaleMap::transform( xMap, yMap, point );
        r.moveCenter( center.toPoint() );
        clipRegion += r;

        d_directPainter->setClipRegion( clipRegion );
    }

    d_directPainter->drawSeries( d_curves[6],
        data->size() - 1, data->size() - 1 );
}

void IncrementalPlot::clearPoints6()
{
    CurveData *data = static_cast<CurveData *>( d_curves[6]->data() );
    data->clear();

    replot();
}

void IncrementalPlot::appendPoint7( const QPointF &point )
{
    CurveData *data = static_cast<CurveData *>( d_curves[7]->data() );
    data->append( point );

    const bool doClip = !canvas()->testAttribute( Qt::WA_PaintOnScreen );
    if ( doClip )
    {
        /*
           Depending on the platform setting a clip might be an important
           performance issue. F.e. for Qt Embedded this reduces the
           part of the backing store that has to be copied out - maybe
           to an unaccelerated frame buffer device.
         */
        const QwtScaleMap xMap = canvasMap( d_curves[7]->xAxis() );
        const QwtScaleMap yMap = canvasMap( d_curves[7]->yAxis() );

        QRegion clipRegion;

        const QSize symbolSize = d_curves[7]->symbol()->size();
        QRect r( 0, 0, symbolSize.width() + 2, symbolSize.height() + 2 );



        const QPointF center =
            QwtScaleMap::transform( xMap, yMap, point );
        r.moveCenter( center.toPoint() );
        clipRegion += r;

        d_directPainter->setClipRegion( clipRegion );
    }

    d_directPainter->drawSeries( d_curves[7],
        data->size() - 1, data->size() - 1 );
}

void IncrementalPlot::clearPoints7()
{
    CurveData *data = static_cast<CurveData *>( d_curves[7]->data() );
    data->clear();

    replot();
}

void IncrementalPlot::appendPoint8( const QPointF &point )
{
    CurveData *data = static_cast<CurveData *>( d_curves[8]->data() );
    data->append( point );

    const bool doClip = !canvas()->testAttribute( Qt::WA_PaintOnScreen );
    if ( doClip )
    {
        /*
           Depending on the platform setting a clip might be an important
           performance issue. F.e. for Qt Embedded this reduces the
           part of the backing store that has to be copied out - maybe
           to an unaccelerated frame buffer device.
         */
        const QwtScaleMap xMap = canvasMap( d_curves[8]->xAxis() );
        const QwtScaleMap yMap = canvasMap( d_curves[8]->yAxis() );

        QRegion clipRegion;

        const QSize symbolSize = d_curves[8]->symbol()->size();
        QRect r( 0, 0, symbolSize.width() + 2, symbolSize.height() + 2 );



        const QPointF center =
            QwtScaleMap::transform( xMap, yMap, point );
        r.moveCenter( center.toPoint() );
        clipRegion += r;

        d_directPainter->setClipRegion( clipRegion );
    }

    d_directPainter->drawSeries( d_curves[8],
        data->size() - 1, data->size() - 1 );
}

void IncrementalPlot::clearPoints8()
{
    CurveData *data = static_cast<CurveData *>( d_curves[8]->data() );
    data->clear();

    replot();
}

void IncrementalPlot::appendPoint9( const QPointF &point )
{
    CurveData *data = static_cast<CurveData *>( d_curves[9]->data() );
    data->append( point );

    const bool doClip = !canvas()->testAttribute( Qt::WA_PaintOnScreen );
    if ( doClip )
    {
        /*
           Depending on the platform setting a clip might be an important
           performance issue. F.e. for Qt Embedded this reduces the
           part of the backing store that has to be copied out - maybe
           to an unaccelerated frame buffer device.
         */
        const QwtScaleMap xMap = canvasMap( d_curves[9]->xAxis() );
        const QwtScaleMap yMap = canvasMap( d_curves[9]->yAxis() );

        QRegion clipRegion;

        const QSize symbolSize = d_curves[9]->symbol()->size();
        QRect r( 0, 0, symbolSize.width() + 2, symbolSize.height() + 2 );



        const QPointF center =
            QwtScaleMap::transform( xMap, yMap, point );
        r.moveCenter( center.toPoint() );
        clipRegion += r;

        d_directPainter->setClipRegion( clipRegion );
    }

    d_directPainter->drawSeries( d_curves[9],
        data->size() - 1, data->size() - 1 );
}

void IncrementalPlot::clearPoints9()
{
    CurveData *data = static_cast<CurveData *>( d_curves[9]->data() );
    data->clear();

    replot();
}

void IncrementalPlot::appendPoint10( const QPointF &point )
{
    CurveData *data = static_cast<CurveData *>( d_curves[10]->data() );
    data->append( point );

    const bool doClip = !canvas()->testAttribute( Qt::WA_PaintOnScreen );
    if ( doClip )
    {
        /*
           Depending on the platform setting a clip might be an important
           performance issue. F.e. for Qt Embedded this reduces the
           part of the backing store that has to be copied out - maybe
           to an unaccelerated frame buffer device.
         */
        const QwtScaleMap xMap = canvasMap( d_curves[10]->xAxis() );
        const QwtScaleMap yMap = canvasMap( d_curves[10]->yAxis() );

        QRegion clipRegion;

        const QSize symbolSize = d_curves[10]->symbol()->size();
        QRect r( 0, 0, symbolSize.width() + 2, symbolSize.height() + 2 );



        const QPointF center =
            QwtScaleMap::transform( xMap, yMap, point );
        r.moveCenter( center.toPoint() );
        clipRegion += r;

        d_directPainter->setClipRegion( clipRegion );
    }

    d_directPainter->drawSeries( d_curves[10],
        data->size() - 1, data->size() - 1 );
}

void IncrementalPlot::clearPoints10()
{
    CurveData *data = static_cast<CurveData *>( d_curves[10]->data() );
    data->clear();

    replot();
}

void IncrementalPlot::appendPoint11( const QPointF &point )
{
    CurveData *data = static_cast<CurveData *>( d_curves[11]->data() );
    data->append( point );

    const bool doClip = !canvas()->testAttribute( Qt::WA_PaintOnScreen );
    if ( doClip )
    {
        /*
           Depending on the platform setting a clip might be an important
           performance issue. F.e. for Qt Embedded this reduces the
           part of the backing store that has to be copied out - maybe
           to an unaccelerated frame buffer device.
         */
        const QwtScaleMap xMap = canvasMap( d_curves[11]->xAxis() );
        const QwtScaleMap yMap = canvasMap( d_curves[11]->yAxis() );

        QRegion clipRegion;

        const QSize symbolSize = d_curves[11]->symbol()->size();
        QRect r( 0, 0, symbolSize.width() + 2, symbolSize.height() + 2 );



        const QPointF center =
            QwtScaleMap::transform( xMap, yMap, point );
        r.moveCenter( center.toPoint() );
        clipRegion += r;

        d_directPainter->setClipRegion( clipRegion );
    }

    d_directPainter->drawSeries( d_curves[11],
        data->size() - 1, data->size() - 1 );
}

void IncrementalPlot::clearPoints11()
{
    CurveData *data = static_cast<CurveData *>( d_curves[11]->data() );
    data->clear();

    replot();
}

void IncrementalPlot::appendPoint12( const QPointF &point )
{
    CurveData *data = static_cast<CurveData *>( d_curves[12]->data() );
    data->append( point );

    const bool doClip = !canvas()->testAttribute( Qt::WA_PaintOnScreen );
    if ( doClip )
    {
        /*
           Depending on the platform setting a clip might be an important
           performance issue. F.e. for Qt Embedded this reduces the
           part of the backing store that has to be copied out - maybe
           to an unaccelerated frame buffer device.
         */
        const QwtScaleMap xMap = canvasMap( d_curves[12]->xAxis() );
        const QwtScaleMap yMap = canvasMap( d_curves[12]->yAxis() );

        QRegion clipRegion;

        const QSize symbolSize = d_curves[12]->symbol()->size();
        QRect r( 0, 0, symbolSize.width() + 2, symbolSize.height() + 2 );



        const QPointF center =
            QwtScaleMap::transform( xMap, yMap, point );
        r.moveCenter( center.toPoint() );
        clipRegion += r;

        d_directPainter->setClipRegion( clipRegion );
    }

    d_directPainter->drawSeries( d_curves[12],
        data->size() - 1, data->size() - 1 );
}

void IncrementalPlot::clearPoints12()
{
    CurveData *data = static_cast<CurveData *>( d_curves[12]->data() );
    data->clear();

    replot();
}

void IncrementalPlot::appendPoint13( const QPointF &point )
{
    CurveData *data = static_cast<CurveData *>( d_curves[13]->data() );
    data->append( point );

    const bool doClip = !canvas()->testAttribute( Qt::WA_PaintOnScreen );
    if ( doClip )
    {
        /*
           Depending on the platform setting a clip might be an important
           performance issue. F.e. for Qt Embedded this reduces the
           part of the backing store that has to be copied out - maybe
           to an unaccelerated frame buffer device.
         */
        const QwtScaleMap xMap = canvasMap( d_curves[13]->xAxis() );
        const QwtScaleMap yMap = canvasMap( d_curves[13]->yAxis() );

        QRegion clipRegion;

        const QSize symbolSize = d_curves[13]->symbol()->size();
        QRect r( 0, 0, symbolSize.width() + 2, symbolSize.height() + 2 );



        const QPointF center =
            QwtScaleMap::transform( xMap, yMap, point );
        r.moveCenter( center.toPoint() );
        clipRegion += r;

        d_directPainter->setClipRegion( clipRegion );
    }

    d_directPainter->drawSeries( d_curves[13],
        data->size() - 1, data->size() - 1 );
}

void IncrementalPlot::clearPoints13()
{
    CurveData *data = static_cast<CurveData *>( d_curves[13]->data() );
    data->clear();

    replot();
}

void IncrementalPlot::showSymbols( bool on )
{
    if ( on )
    {
        d_curve->setStyle( QwtPlotCurve::NoCurve );
        d_curve->setSymbol( new QwtSymbol( QwtSymbol::Ellipse,
            QBrush(Qt::white), QPen( Qt::white ), QSize( 8, 8 ) ) );
        d_curves[0]->setStyle( QwtPlotCurve::NoCurve );
        d_curves[0]->setSymbol( new QwtSymbol( QwtSymbol::Ellipse,
            QBrush(Qt::white), QPen( Qt::white ), QSize( 8, 8 ) ) );
        d_curves[1]->setStyle( QwtPlotCurve::NoCurve );
        d_curves[1]->setSymbol( new QwtSymbol( QwtSymbol::Ellipse ,
            QBrush( Qt::gray  ), QPen( Qt::gray ), QSize( 8, 8 ) ) );
        d_curves[2]->setStyle( QwtPlotCurve::NoCurve );
        d_curves[2]->setSymbol( new QwtSymbol( QwtSymbol::Rect ,
            QBrush(Qt::white), QPen( Qt::white ), QSize( 6, 6 ) ) );
        d_curves[3]->setStyle( QwtPlotCurve::NoCurve );
        d_curves[3]->setSymbol( new QwtSymbol( QwtSymbol::Rect ,
            QBrush(Qt::gray), QPen( Qt::gray ), QSize( 6, 6 ) ) );

        d_curves[4]->setStyle( QwtPlotCurve::NoCurve );
        d_curves[4]->setSymbol( new QwtSymbol( QwtSymbol::Ellipse,
            QBrush(Qt::red), QPen( Qt::red ), QSize( 8, 8 ) ) );
        d_curves[5]->setStyle( QwtPlotCurve::NoCurve );
        d_curves[5]->setSymbol( new QwtSymbol( QwtSymbol::Ellipse,
            QBrush(Qt::black), QPen( Qt::black ), QSize( 8, 8 ) ) );
        d_curves[6]->setStyle( QwtPlotCurve::NoCurve );
        d_curves[6]->setSymbol( new QwtSymbol( QwtSymbol::Rect ,
            QBrush(Qt::red), QPen( Qt::red ), QSize( 6, 6 ) ) );
        d_curves[7]->setStyle( QwtPlotCurve::NoCurve );
        d_curves[7]->setSymbol( new QwtSymbol( QwtSymbol::Rect ,
            QBrush(Qt::black), QPen( Qt::black ), QSize( 6, 6 ) ) );

        d_curves[8]->setStyle( QwtPlotCurve::NoCurve );
        d_curves[8]->setSymbol( new QwtSymbol( QwtSymbol::Ellipse,
            QBrush(Qt::green), QPen( Qt::green ), QSize( 8, 8 ) ) );
        d_curves[9]->setStyle( QwtPlotCurve::NoCurve );
        d_curves[9]->setSymbol( new QwtSymbol( QwtSymbol::Ellipse,
            QBrush(Qt::yellow), QPen( Qt::yellow ), QSize( 8, 8 ) ) );
        d_curves[10]->setStyle( QwtPlotCurve::NoCurve );
        d_curves[10]->setSymbol( new QwtSymbol( QwtSymbol::Rect ,
            QBrush(Qt::green), QPen( Qt::green ), QSize( 6, 6 ) ) );
        d_curves[11]->setStyle( QwtPlotCurve::NoCurve );
        d_curves[11]->setSymbol( new QwtSymbol( QwtSymbol::Rect ,
            QBrush(Qt::yellow), QPen( Qt::yellow ), QSize( 6, 6 ) ) );

        d_curves[12]->setStyle( QwtPlotCurve::NoCurve );
        d_curves[12]->setSymbol( new QwtSymbol( QwtSymbol::Ellipse,
            QBrush(Qt::cyan), QPen( Qt::cyan ), QSize( 8, 8 ) ) );
        d_curves[13]->setStyle( QwtPlotCurve::NoCurve );
        d_curves[13]->setSymbol( new QwtSymbol( QwtSymbol::Ellipse,
            QBrush(Qt::magenta), QPen( Qt::magenta), QSize( 8, 8 ) ) );
    }
    else
    {
        d_curve->setStyle( QwtPlotCurve::NoCurve );
        d_curve->setSymbol( new QwtSymbol( QwtSymbol::Ellipse,
            QBrush(Qt::white), QPen( Qt::white ), QSize( 4, 4 ) ) );
        d_curves[0]->setStyle( QwtPlotCurve::NoCurve );
        d_curves[0]->setSymbol( new QwtSymbol( QwtSymbol::Ellipse,
            QBrush(Qt::white), QPen( Qt::white ), QSize( 4, 4 ) ) );
        d_curves[1]->setStyle( QwtPlotCurve::NoCurve );
        d_curves[1]->setSymbol( new QwtSymbol( QwtSymbol::Ellipse,
            QBrush(Qt::gray), QPen( Qt::gray ), QSize( 4, 4 ) ) );
        d_curves[2]->setStyle( QwtPlotCurve::NoCurve );
        d_curves[2]->setSymbol( new QwtSymbol( QwtSymbol::Cross ,
            QBrush(Qt::white), QPen( Qt::white ), QSize( 6, 6 ) ) );
        d_curves[3]->setStyle( QwtPlotCurve::NoCurve );
        d_curves[3]->setSymbol( new QwtSymbol( QwtSymbol::Cross ,
            QBrush(Qt::gray), QPen( Qt::gray ), QSize( 6, 6 ) ) );

        d_curves[4]->setStyle( QwtPlotCurve::NoCurve );
        d_curves[4]->setSymbol( new QwtSymbol( QwtSymbol::Ellipse,
            QBrush(Qt::red), QPen( Qt::red ), QSize( 4, 4 ) ) );
        d_curves[5]->setStyle( QwtPlotCurve::NoCurve );
        d_curves[5]->setSymbol( new QwtSymbol( QwtSymbol::Ellipse,
            QBrush(Qt::black), QPen( Qt::black ), QSize( 4, 4 ) ) );
        d_curves[6]->setStyle( QwtPlotCurve::NoCurve );
        d_curves[6]->setSymbol( new QwtSymbol( QwtSymbol::Cross,
            QBrush(Qt::red), QPen( Qt::red ), QSize( 6, 6 ) ) );
        d_curves[7]->setStyle( QwtPlotCurve::NoCurve );
        d_curves[7]->setSymbol( new QwtSymbol( QwtSymbol::Cross,
            QBrush(Qt::black), QPen( Qt::black ), QSize( 6, 6 ) ) );

        d_curves[8]->setStyle( QwtPlotCurve::NoCurve );
        d_curves[8]->setSymbol( new QwtSymbol( QwtSymbol::Ellipse,
            QBrush(Qt::green), QPen( Qt::green ), QSize( 4, 4 ) ) );
        d_curves[9]->setStyle( QwtPlotCurve::NoCurve );
        d_curves[9]->setSymbol( new QwtSymbol( QwtSymbol::Ellipse,
            QBrush(Qt::yellow), QPen( Qt::yellow ), QSize( 4, 4 ) ) );
        d_curves[10]->setStyle( QwtPlotCurve::NoCurve );
        d_curves[10]->setSymbol( new QwtSymbol( QwtSymbol::Cross,
            QBrush(Qt::green), QPen( Qt::green ), QSize( 6, 6 ) ) );
        d_curves[11]->setStyle( QwtPlotCurve::NoCurve );
        d_curves[11]->setSymbol( new QwtSymbol( QwtSymbol::Cross,
            QBrush(Qt::yellow), QPen( Qt::yellow ), QSize( 6, 6 ) ) );

        d_curves[12]->setStyle( QwtPlotCurve::NoCurve );
        d_curves[12]->setSymbol( new QwtSymbol( QwtSymbol::Triangle,
           QBrush(Qt::cyan), QPen( Qt::cyan ), QSize( 5, 5 ) ) );
        d_curves[13]->setStyle( QwtPlotCurve::NoCurve );
        d_curves[13]->setSymbol( new QwtSymbol( QwtSymbol::Ellipse,
            QBrush(Qt::magenta), QPen( Qt::magenta ), QSize( 4, 4 ) ) );
    }
    replot();
}
