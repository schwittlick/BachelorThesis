#ifndef BLOBDETECTORDIALOG_H
#define BLOBDETECTORDIALOG_H

#include <QDialog>
#include "ui_BlobDetectorDialog.h"

class BlobDetectorDialog : public QDialog
{
	Q_OBJECT

public:
	BlobDetectorDialog(QWidget *parent = 0);
	~BlobDetectorDialog();

private:
	Ui::BlobDetectorDialog ui;
};

#endif // BLOBDETECTORDIALOG_H
