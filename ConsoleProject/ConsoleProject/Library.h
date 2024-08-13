#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <functional>
#include <memory>
#include <unordered_map>
#include <algorithm>

#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <cstdio>
#include <cmath>

#include <random>
#include <limits>


using namespace std;

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

#define MAX_WIDTH 50
#define MAX_HEIGHT 20

enum class NodeState
{
	Success,
	Failure,
	Running
};

enum DIR
{
	LEFT = 1,
	RIGHT,
	UP,
	DOWN
};

enum OBJECT
{
	OBSTACLE,
	MONSTER,
	ITEM,
	PLAYER,
	BULLET
};

enum ColorType 
{
	BLACK,  	//0
	darkBLUE,	//1
	DarkGreen,	//2
	darkSkyBlue,    //3
	DarkRed,  	//4
	DarkPurple,	//5
	DarkYellow,	//6
	GRAY,		//7
	DarkGray,	//8
	BLUE,		//9
	GREEN,		//10
	SkyBlue,	//11
	RED,		//12
	PURPLE,		//13
	YELLOW,		//14
	WHITE		//15
} ;

struct Point
{
	int x;
	int y;
	
	Point() : x(0), y(0) {};
	Point(int x, int y) : x(x), y(y) {};

	bool operator==(const Point& other) const
	{
		return x == other.x && y == other.y;
	}

	bool operator!=(const Point& other) const
	{
		return !(*this == other);
	}

	bool operator<(const Point& other) const 
{
		return x < other.x || (x == other.x && y < other.y);
	}
};

// 해시 함수 정의 (unordered_map 사용을 위해)
namespace std {
	template <>
	struct hash<Point> {
		size_t operator()(const Point& p) const {
			return hash<int>()(p.x) ^ (hash<int>()(p.y) << 1);
		}
	};
}

void gotoxy(int x, int y);
void gotoxy(Point p);
void gotoxy(COORD coord);
bool tick(DWORD& startTime);
void textcolor(int colorNum);


void setconsole();