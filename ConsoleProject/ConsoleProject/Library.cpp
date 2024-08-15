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

bool tick(float& startTime, float& elapsedTime)
{
    float currentTime = GetTickCount64();
    elapsedTime = currentTime - startTime;

    if (elapsedTime >= 60)
    {
        startTime = currentTime;
        return true;
    }

    return false;
}

void textcolor(int colorNum)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}

float distance(Point& a, Point& b)
{
    return sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

float Heuristic(Point a, Point b)
{
    return abs(a.x - b.x) + abs(a.y - b.y);
}

void setconsole()
{
    system("title shooting game");
    system("mode con:cols=130 lines=30");

    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = 0;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}
