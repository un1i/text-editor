#include <iostream>	
#include <string>
#include <Windows.h>
#include "TextUsercom.h"
#include <conio.h>	

using namespace std;


int main(){
	TextLink::init_mem_system();
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	TextUsercom usercom;
	usercom.run();

	return 0;
} 