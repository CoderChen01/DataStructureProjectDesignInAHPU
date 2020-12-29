#include <Windows.h>

#ifndef CONSOLE_STYLE_H
#define CONSOLE_STYLE_H

void FullScreen();  // full screen
void SetFontColor(int color);  // Set command line font color
void GoToXY(int x, int y);  // Specify the output location of printf
void Menu(int isTypeChoose, int isAnimation);  // Draw a menu
void Pause();  // Block the console
COORD _DrawLogo(int x, int y, int logoColor, int isAnimation);  // Draw a logo

#endif // !CONSOLE_STYLE_H
