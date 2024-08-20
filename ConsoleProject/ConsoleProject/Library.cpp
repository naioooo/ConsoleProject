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

    if (elapsedTime > 60)
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

float CalculateAngle(Point a, Point b)
{
    // ���� ���
    float dx = b.x - a.x;
    float dy = b.y - a.y;

    // ���Ⱑ 0�� ��츦 ó�� (x1 == x2)
    if (dx == 0) 
    {
        return (dy > 0) ? 90.0f : 270.0f;  // �������� ���
    }

    // ���⸦ ����Ͽ� ���� ���
    float slope = dy / dx;
    float angleRad = std::atan(slope);

    // ������ �� ������ ��ȯ
    float angleDeg = angleRad * (180.0f / 3.14159f);

    // ������ ������ ��� 360���� ����
    if (angleDeg < 0) 
    {
        angleDeg += 360.0f;
    }

    return angleDeg; 
}

float Node::fCost() const
{
    return gCost + hCost; 
}

int DetermineDirection(Point a, Point b)
 {
    // x�� y�� ���� ���
    float dx = b.x - a.x;
    float dy = b.y - a.y;

    // ���� ���̿� ���� ������ ���밪 ��
    float abs_dx = std::fabs(dx);
    float abs_dy = std::fabs(dy);

    // ���� ���̿� ���� ���� ���Ͽ� ���� ����
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