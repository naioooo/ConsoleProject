#pragma once
#include "Object.h"

Object::Object()
{
}

Object::Object(const Point point) : m_point(point), m_alive(true)
{
}

Object::~Object()
{
}

Point Object::GetPoint() const
{
    return m_point;
}

bool Object::GetAlive() const
{
    return m_alive;
}

void Object::SetAlive(bool alive)
{
    m_alive = alive;
}

void Object::SetPoint(Point point)
{
    m_point = point;
}

void Object::InsertBuffer(vector<string>& buffer)
{
    buffer[m_point.y][m_point.x] = CH_OBSTACLE;
}

void Object::Update(float elapsedTime)
{
}

bool Object::CollisionCheck(Point point)
{
    return false;
}
