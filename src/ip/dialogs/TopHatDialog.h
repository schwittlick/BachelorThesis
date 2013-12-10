#ifndef TOPHATDIALOG_H
#define TOPHATDIALOG_H

#include <QDialog>
#include "ui_TopHatDialog.h"

class TopHatDialog : public QDialog
{
	Q_OBJECT

public:
	TopHatDialog(QWidget *parent = 0);
	~TopHatDialog();

signals:
	void kernelSizeChanged( int _k );
	void iterationsChanged( int _it );

private:
	Ui::TopHatDialog ui;
};

#endif // TOPHATDIALOG_H
