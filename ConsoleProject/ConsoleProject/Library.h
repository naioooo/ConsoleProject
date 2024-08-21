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

#define MAX_WIDTH 60
#define MAX_HEIGHT 20

#define CH_OBSTACLE '@'
#define CH_MONSTER1 '#'
#define CH_MONSTER2 '!'
#define CH_MONSTER3 '^'
#define CH_PLAYER 'O'
#define CH_BULLET '*'
#define CH_fireBall 'o'
#define CH_HPUP '+'
#define CH_ATTACKUP 'A'
#define CH_MONEY '$'
#define CH_BOSS1 '('
#define CH_BOSS2 '~'
#define CH_BOSS3 ')'

enum class NodeState
{
	Success,
	Failure,
	Running
};

enum State
{
	WANDER,
	CHASE,
	ATTACK
};

enum DIR
{
	LEFT = 1,
	RIGHT,
	UP,
	DOWN,
	LEFTUP,
	RIGHTUP,
	LEFTDOWN,
	RIGHTDOWN
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
		return (int)x == (int)other.x && (int)y == (int)other.y;
	}

	bool operator!=(const Point& other) const
	{
		return (int)x != (int)other.x || (int)y != (int)other.y;;
	}

	bool operator<(const Point& other) const 
{
		return (int)x < (int)other.x || ((int)x == (int)other.x && (int)y < (int)other.y);
	}
};

struct Node
{
	Point position;
	float gCost, hCost; // gCost: 시작점에서 이 노드까지의 실제 거리, hCost: 이 노드에서 목표까지의 추정 거리
	Node* parent;

	// fCost 계산
	float fCost() const; 

	// 정렬을 위한 비교 연산자
	bool operator>(const Node& other) const
	{
		return fCost() > other.fCost();
	}
};

// 해시 함수 정의 (unordered_map 사용을 위해)
namespace std
{
	template <>
	struct hash<Point> 
	{
		size_t operator()(const Point& p) const
		{
			return hash<int>()(p.x) ^ (hash<int>()(p.y) << 1);
		}
	};
}

void gotoxy(int x, int y);
void gotoxy(Point p);
void gotoxy(COORD coord);

bool tick(float& startTime, float& elapsedTime);

void textcolor(int colorNum);

float distance(Point& a, Point& b);
float Heuristic(Point a, Point b);

void setconsole();

float CalculateAngle(Point a, Point b);
int DetermineDirection(Point a, Point b);