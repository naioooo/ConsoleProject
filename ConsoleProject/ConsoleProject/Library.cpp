#pragma once
#include "Library.h"

void GoToXY(int x, int y)
{
    COORD coord{};
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void GoToXY(Point p)
{
    COORD coord{};
    coord.X = p.x;
    coord.Y = p.y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void GoToXY(COORD coord)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void TextColor(int colorNum)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}

float Distance(Point& a, Point& b)
{
    return sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

float Heuristic(Point a, Point b)
{
    return abs(a.x - b.x) + abs(a.y - b.y);
}

void SetConsole()
{
    system("title shooting game");
    system("mode con:cols=130 lines=30");

    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor{};
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = 0;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

float Node::fCost() const
{
    return gCost + hCost; 
}

int DetermineDirection(Point a, Point b)
 {
    // x와 y의 차이 계산
    float dx = b.x - a.x;
    float dy = b.y - a.y;

    // 수직 차이와 수평 차이의 절대값 비교
    float abs_dx = std::fabs(dx);
    float abs_dy = std::fabs(dy);

    // 수직 차이와 수평 차이 비교하여 방향 결정
    if (abs_dx > abs_dy) {
        if (dx > 0) 
        {
            return RIGHT;
        }
        else 
        {
            return LEFT;
        }
    }
    else {
        if (dy > 0)
        {
            return DOWN;
        }
        else
        {
            return UP;
        }
    }
}