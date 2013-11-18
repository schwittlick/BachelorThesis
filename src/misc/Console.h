#pragma once

#include <Windows.h>
//#inlcude <stdio.h>
//#include <iostream>
#include "stdio.h"
#include <io.h>
#include <fcntl.h>
#include <string>

class Console
{
public:
	Console(void);
	~Console(void);

	static void createConsole();
	static std::wstring s2ws(const std::string& s);
};

