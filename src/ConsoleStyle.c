#include <stdio.h>
#include <Windows.h>
#include "flush.h"


void FullScreen()  // full screen
{
    HWND hwnd = GetForegroundWindow();
    int cx = GetSystemMetrics(SM_CXSCREEN);
    int cy = GetSystemMetrics(SM_CYSCREEN);

    LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);

    SetWindowLong(
        hwnd,
        GWL_STYLE,
        (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);

    SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy, 0);
}


void SetFontColor(int color)  // Set command line font color
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


void GoToXY(int x, int y)  // Specify the output location of printf
{
    COORD c = {
        .X = x,
        .Y = y
    };

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
   
}


void IsSleep(int m, int isSleep)
{
    if (isSleep)
    {
        Sleep(m);
    }
}


COORD _DrawBoard(int j, int i, int width, int height, int isAnimation)  // Draw a board
{
    int lastLine = i + height - 1;
    int lastCol = j + width - 1;
    int firstJ = j;
    int firstI = i;
    for (; i <= lastLine; i++) {

        j = firstJ;
        for (; j <= lastCol; j++) {
 
            GoToXY(j, i);
            if (i == firstI || i == lastLine) {
                printf_s("-");
                IsSleep(15, isAnimation);
            }
            else if (j == firstJ || j == lastCol) {
                printf_s("|");
                IsSleep(15, isAnimation);
            }
        }
    }

    COORD coord = {
        .X = j,
        .Y = i
    };
    return coord;
}


COORD _DrawLogo(int x, int y, int logoColor, int isAnimation)  // Print logo
{
    SetFontColor(logoColor);

    GoToXY(x, y);
    printf_s("  #####                                        #     #                                  #####                                                                \n");
    IsSleep(80, isAnimation);
    GoToXY(x, ++y);
    printf_s(" #     # #####    ##   #####   ####  ######    ##   ##   ##   ##### #####  # #    #    #     #   ##   #       ####  #    # #        ##   #####  ####  #####  \n");
    IsSleep(80, isAnimation);
    GoToXY(x, ++y);
    printf_s(" #       #    #  #  #  #    # #      #         # # # #  #  #    #   #    # #  #  #     #        #  #  #      #    # #    # #       #  #    #   #    # #    # \n");
    IsSleep(80, isAnimation);
    GoToXY(x, ++y);
    printf_s("  #####  #    # #    # #    #  ####  #####     #  #  # #    #   #   #    # #   ##      #       #    # #      #      #    # #      #    #   #   #    # #    # \n");
    IsSleep(80, isAnimation);
    GoToXY(x, ++y);
    printf_s("       # #####  ###### #####       # #         #     # ######   #   #####  #   ##      #       ###### #      #      #    # #      ######   #   #    # #####  \n");
    IsSleep(80, isAnimation);
    GoToXY(x, ++y);
    printf_s(" #     # #      #    # #   #  #    # #         #     # #    #   #   #   #  #  #  #     #     # #    # #      #    # #    # #      #    #   #   #    # #   #  \n");
    IsSleep(80, isAnimation);
    GoToXY(x, ++y);
    printf_s("  #####  #      #    # #    #  ####  ######    #     # #    #   #   #    # # #    #     #####  #    # ######  ####   ####  ###### #    #   #    ####  #    # \n");
    IsSleep(80, isAnimation);
    GoToXY(x, ++y);
    printf_s("                                                                                                                                                             \n");

    COORD coord = {
        .X = x,
        .Y = y
    };

    return coord;  // Return the current cursor position
}


COORD _DrawOperationChoose(
    int x,
    int y,
    int boardWidth,
    int boardHeight,
    int boardColor,
    int fontColor,
    int isAnimation)  // Print choose
{

    SetFontColor(boardColor);
    COORD coord = _DrawBoard(x + 50, y + 10, boardWidth, boardHeight, isAnimation);

    SetFontColor(fontColor);
    int i = coord.X - boardWidth + 3;
    int j = coord.Y - boardHeight + 2;
    
    GoToXY(i, j);
    printf_s("1. Matrix addition          2. Matrix subtraction");
    IsSleep(130, isAnimation);
    GoToXY(i, ++j);
    GoToXY(i, ++j);
    printf_s("3. Matrix multiplication    4. Matrix inverse");
    IsSleep(130, isAnimation);
    GoToXY(i, ++j);
    GoToXY(i, ++j);
    printf_s("5. Matrix transpose         6. Matrix determinant");
    GoToXY(i, ++j);
    GoToXY(i, ++j);
    printf_s("                0. Exit system");
    GoToXY(coord.X, coord.Y);
    
    return coord;
}


COORD _DrawTypeChoose(
    int x,
    int y,
    int boardWidth,
    int boardHeight,
    int boardColor,
    int fontColor,
    int isAnimation)  // Print choose
{

    SetFontColor(boardColor);
    COORD coord = _DrawBoard(x + 50, y + 10, boardWidth, boardHeight, isAnimation);

    SetFontColor(fontColor);
    int i = coord.X - boardWidth + 3;
    int j = coord.Y - boardHeight + 2;

    GoToXY(i, j);
    printf_s("1. Diagonal Matrix          2. Symmetric Matrix");
    IsSleep(130, isAnimation);
    GoToXY(i, ++j);
    GoToXY(i, ++j);
    printf_s("3. Identity Matrix          4. Triangluar Matrix");
    IsSleep(130, isAnimation);
    GoToXY(i, ++j);
    GoToXY(i, ++j);
    printf_s("5. Sparse Matrix            0. Return Menu");
    IsSleep(130, isAnimation);
    GoToXY(coord.X, coord.Y);

    return coord;
}



void Menu(int isTypeChoose, int isAnimation)
{
    /*
    The printed logo is in the center of the screen,
    and the x and y parameters are tested, under a 1920x1680 screen
    */
    COORD logoCoord = _DrawLogo(37, 10, 2, isAnimation);

    int width = 0;
    int height = 0;

    if (!isTypeChoose)
    {
        GoToXY(logoCoord.X + 69, logoCoord.Y + 8);
        SetFontColor(11);  // Set color light blue
        printf_s("Choose Operation");

        width = 55;
        height = 10;
        COORD chooseCoord = _DrawOperationChoose(
            logoCoord.X,
            logoCoord.Y,
            width,
            height,
            14, 2, isAnimation);

        SetFontColor(3);
        int x = chooseCoord.X;
        int y = chooseCoord.Y;
        GoToXY(x, ++y);
        x -= width;
        GoToXY(x, ++y);
        printf_s("Please enter your choose[1 2 3 4 5 6 0]: [ ]");

        SetFontColor(7);
        x += 42;
        GoToXY(x + 40, y + 2);
        printf_s("By CoderChen(Chen Junjie)");
        GoToXY(x + 57, y + 3);
        printf_s("At AHPU");
        GoToXY(x, y);
    }
    else
    {
        GoToXY(logoCoord.X + 68, logoCoord.Y + 8);
        SetFontColor(11);  // Set color light blue
        printf_s("Choose Matrix Type");

        width = 55;
        height = 9;
        COORD chooseCoord = _DrawTypeChoose(logoCoord.X, logoCoord.Y, width, height, 14, 2, isAnimation);

        SetFontColor(3);
        int x = chooseCoord.X;
        int y = chooseCoord.Y;
        GoToXY(x, ++y);
        x -= width;
        GoToXY(x, ++y);
        printf_s("Please enter your choose[1 2 3 4 5 0]: [ ]");
        x += 40;
        GoToXY(x, y);
        SetFontColor(7);
    }
}


void Pause()  // Block the console
{
    printf_s("\033[32m\nPlease Enter to continue...\n\033[0m");
    kbhit();
    flush();
}
