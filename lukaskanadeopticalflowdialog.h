#ifndef LUKASKANADEOPTICALFLOWDIALOG_H
#define LUKASKANADEOPTICALFLOWDIALOG_H

#include <QDialog>
#include "ui_lukaskanadeopticalflowdialog.h"

class LukasKanadeOpticalFLowDialog : public QDialog
{
	Q_OBJECT

public:
	LukasKanadeOpticalFLowDialog(QWidget *parent = 0);
	~LukasKanadeOpticalFLowDialog();

signals:
	void itersValueChanged( int _iters );

private:
	Ui::LukasKanadeOpticalFLowDialog ui;
};

#endif // LUKASKANADEOPTICALFLOWDIALOG_H
