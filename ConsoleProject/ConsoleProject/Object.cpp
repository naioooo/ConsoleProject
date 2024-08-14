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

Point Object::getpoint()
{
    return m_point;
}

bool Object::getalive()
{
    return m_alive;
}

void Object::setalive(bool alive)
{
    m_alive = alive;
}

void Object::insertbuffer(vector<string>& buffer)
{
    buffer[m_point.y][m_point.x] = '#';
}

void Object::update(float elapsedTime)
{
}

bool Object::collision_check(Point point)
{
    return false;
}
