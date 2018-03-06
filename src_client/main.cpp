//
// Created by Nagamo_s on 29/09/2017.
//

#include"Core.hpp"

int main(int argc, char** argv)
{
    Core core;

	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, 0);
    core.client();
	return 0;
}
