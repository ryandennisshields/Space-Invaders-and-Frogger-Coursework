#include "Window.h"

void Window::setWindow(int width, int height) {

	this->width = width;
	this->height = height;

	SMALL_RECT windowSize = { 10, 10, width+20, height+20};
	if (!SetConsoleWindowInfo(hConsole, TRUE, &windowSize))
	{
		cout << "SetConsoleWindowInfo failed with error " << GetLastError() << endl;
	}

	if (!SetConsoleTitle(L"Ryan Shields Games"))
	{
		cout << "SetConsoleTitle failed with error " << GetLastError() << endl;
	}
	
#pragma region hideCursor
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
#pragma endregion

#pragma region changeFont
	CONSOLE_FONT_INFOEX cfi = { sizeof(cfi) };

	HANDLE hcsb = CreateFileA("CONOUT$", GENERIC_WRITE | GENERIC_READ,
		FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	GetCurrentConsoleFontEx(hcsb, FALSE, &cfi);

	cfi.dwFontSize.X *= 2;
	cfi.dwFontSize.Y *= 2;

	SetCurrentConsoleFontEx(hcsb, FALSE, &cfi);
#pragma endregion
}

void Window::setCursorPosition(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

