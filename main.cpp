#include "BachelorThesis.h"
#include <QtWidgets/QApplication>
#include <thread>
#include "src/misc/Console.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	Console::createConsole();

	BachelorThesis w;
	w.show();

	return a.exec();
}
