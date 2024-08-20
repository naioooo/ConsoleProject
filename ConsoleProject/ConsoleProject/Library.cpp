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
    // 기울기 계산
    float dx = b.x - a.x;
    float dy = b.y - a.y;

    // 기울기가 0인 경우를 처리 (x1 == x2)
    if (dx == 0) 
    {
        return (dy > 0) ? 90.0f : 270.0f;  // 수직선의 경우
    }

    // 기울기를 사용하여 각도 계산
    float slope = dy / dx;
    float angleRad = std::atan(slope);

    // 라디안을 도 단위로 변환
    float angleDeg = angleRad * (180.0f / 3.14159f);

    // 각도가 음수인 경우 360도로 보정
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