#include "BachelorThesis.h"
#include <QtWidgets/QApplication>

#include "Console.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	Console::createConsole();
	BachelorThesis w;
	w.show();
	return a.exec();
}
