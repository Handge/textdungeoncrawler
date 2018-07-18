// Functions

#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include "functions.h"

void draw_textfile(std::string file_name) {
	std::string line;
	std::ifstream myfile(file_name);
	if (myfile.is_open()) {
		while (std::getline(myfile, line)) {
			std::cout << line << '\n';
		}
		myfile.close();
	}
	else {
		std::cout << "Unable to open file" << std::endl;
	}
}

std::string get_input() {
	std::string input;
	std::cout << std::endl;
	std::cout << ">> ";
	std::cin >> input;
	return input;
}

int random_number(int min, int max) {
	int n = max - min + 1;
	int remainder = RAND_MAX % n;
	int x;
	do {
		x = rand();
	} while (x >= RAND_MAX - remainder);
	return min + x % n;
}

void reset_pause() {
	_getch();
}

void pause() {
	std::cout << std::endl;
	std::cout << "Press any key to continue...";
	_getch();
}

// Credit : www.cplusplus.com/articles/4z18T05o/
void clear() {
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	SetConsoleCursorPosition(hStdOut, homeCoords);
}