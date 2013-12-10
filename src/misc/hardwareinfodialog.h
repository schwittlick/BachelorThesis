#ifndef HARDWAREINFODIALOG_H
#define HARDWAREINFODIALOG_H

#include <iostream>
#include <sstream>
#include <QDialog>
#include "ui_hardwareinfodialog.h"

#include "opencv2/gpu/gpu.hpp"

class HardwareInfoDialog : public QDialog
{
	Q_OBJECT

public:
	HardwareInfoDialog(QWidget *parent = 0);
	~HardwareInfoDialog();

private:
	Ui::HardwareInfoDialog ui;
};

#endif // HARDWAREINFODIALOG_H
