#ifndef IMAGEDISPLAYLABEL_H
#define IMAGEDISPLAYLABEL_H

#include <QLabel>
#include "ui_imagedisplaylabel.h"
#include "ROI.h"
#include "QRubberBand"
#include "QPoint"
#include "QRect"
#include < iostream >


class ImageDisplayLabel : public QLabel
{
	Q_OBJECT

public:
	ImageDisplayLabel(QWidget *parent = 0);
	~ImageDisplayLabel();

	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

	QRect getRoi( void );

private:
	Ui::ImageDisplayLabel ui;

	QRubberBand * rubberBand;
	QPoint origin;
};

#endif // IMAGEDISPLAYLABEL_H
