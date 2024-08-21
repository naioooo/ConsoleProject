#pragma once
#include <iostream>
#include <cstdio>

#include <vector>
#include <unordered_map>
#include <string>
#include <queue>

#include <algorithm>
#include <functional>
#include <memory>
#include <random>

#include <cmath>
#include <limits>
#include <chrono>

#include <windows.h>
#include <conio.h>
#include <stdio.h>

using namespace std;

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

#define MAX_WIDTH 60
#define MAX_HEIGHT 20

#define CH_OBSTACLE '@'
#define CH_MONSTER1 '#'
#define CH_MONSTER2 '!'
#define CH_MONSTER3 '^'
#define CH_BOSS1 '('
#define CH_BOSS2 '~'
#define CH_BOSS3 ')'
#define CH_PLAYER 'O'
#define CH_BULLET '*'
#define CH_FIREBALL 'o'
#define CH_HPUP '+'
#define CH_ATTACKUP 'A'
#define CH_MONEY '$'
#define CH_SPEEDUP 'S'

enum class NodeState
{
	SUCCESS,
	FAILURE,
	RUNNING
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
	BLACK,  	
	DARKBLUE,	
	DARKGREEN,	
	DARKSKYBLUE,
	DARKRED,  	
	DARKPURPLE,	
	DARKYELLOW,	
	GRAY,		
	DARKGRAY,	
	BLUE,		
	GREEN,		
	SKYBLUE,	
	RED,		
	PURPLE,		
	YELLOW,		
	WHITE		
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
	float gCost; // gCost: ���������� �� �������� ���� �Ÿ�
	float hCost; // hCost: �� ��忡�� ��ǥ������ ���� �Ÿ�
	shared_ptr<Node> parent;

	// fCost ���
	float fCost() const; 

	// ������ ���� �� ������
	bool operator>(const Node& other) const
	{
		return fCost() > other.fCost();
	}
};

// �ؽ� �Լ� ���� (unordered_map ����� ����)
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

void GoToXY(int x, int y);
void GoToXY(Point p);
void GoToXY(COORD coord);

void TextColor(int colorNum);

float Distance(Point& a, Point& b);
float Heuristic(Point a, Point b);
int DetermineDirection(Point a, Point b);

void SetConsole();