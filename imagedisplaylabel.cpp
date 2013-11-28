#include "imagedisplaylabel.h"
#include "QPainter"
#include "QPaintEvent"

ImageDisplayLabel::ImageDisplayLabel(QWidget *parent)
	: QLabel(parent)
{
	ui.setupUi(this);
	origin = QPoint();
	origin.setX(0);
	origin.setY(0);
	rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
	QPalette pal;
	pal.setColor( QPalette::Background, QColor( QColor( 0, 0, 0, 0 ) ) );
	//pal.setColor( )
	//pal.setBrush(QPalette::Highlight, QBrush( QColor( 255, 255, 255, 0 ) ) );
	rubberBand->setPalette( pal );
	rubberBand->setGeometry(QRect(QPoint( 100, 100 ), QPoint( 200, 200 ) ).normalized());
}

ImageDisplayLabel::~ImageDisplayLabel()
{
}

void ImageDisplayLabel::mousePressEvent(QMouseEvent *event)
{
	origin = event->pos();
	rubberBand->setGeometry(QRect(origin, QSize()));
	rubberBand->show();
}

void ImageDisplayLabel::mouseReleaseEvent( QMouseEvent *event )
{
	rubberBand->hide();
}

void ImageDisplayLabel::mouseMoveEvent(QMouseEvent *event)
{
	rubberBand->setGeometry(QRect(origin, event->pos()).normalized());
}

QRect ImageDisplayLabel::getRoi( void )
{
	return rubberBand->geometry();
}
