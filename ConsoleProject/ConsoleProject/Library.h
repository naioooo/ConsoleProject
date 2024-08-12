#pragma once
#include <iostream>
#include <vector>
#include <string>

#include <windows.h>
#include <conio.h>
#include <stdio.h>

#include <random>

using namespace std;

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

#define MAX_WIDTH 50
#define MAX_HEIGHT 20

enum DIR
{
	RIGHT = 1,
	LEFT,
	UP,
	DOWN
};

struct Point
{
	int x;
	int y;
};

void gotoxy(int x, int y);
void gotoxy(Point p);
void gotoxy(COORD coord);
bool tick(DWORD& startTime);
