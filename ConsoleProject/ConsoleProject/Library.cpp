#pragma once
#include "Library.h"

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void gotoxy(Point p)
{
    COORD coord;
    coord.X = p.x;
    coord.Y = p.y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void gotoxy(COORD coord)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

bool tick(DWORD& startTime)
{
    DWORD currentTime = GetTickCount64();
    DWORD elapsedTime = currentTime - startTime;

    if (elapsedTime >= 100)
    {
        startTime = currentTime;
        return true;
    }

    return false;
}

void setconsole()
{
    system("title shooting game");
    system("mode con:cols=120 lines=28");

    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = 0;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole, &ConsoleCursor);

}
