#include "BachelorThesis.h"
#include <QtWidgets/QApplication>
#include <thread>
#include "src/misc/Console.h"

//memory leak detectio
#include <stdlib.h>
#include <crtdbg.h>

#define _CRTDBG_MAP_ALLOC 
#define _CRTDBG_MAP_ALLOC_NEW

#ifdef _DEBUG   
#ifndef DBG_NEW      
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )      
#define new DBG_NEW   
#endif
#endif  // _DEBUG

int main(int argc, char *argv[])
{
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	_CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_DEBUG );

	QApplication a(argc, argv);

	Console::createConsole();

	BachelorThesis w;
	w.show();

	return a.exec();
}
