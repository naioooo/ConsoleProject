#pragma once
#include "Object.h"

Object::Object()
{
}

Object::Object(const Point point) : m_point(point)
{
}

Object::~Object()
{
}

Point Object::getpoint()
{
    return m_point;
}

void Object::insertbuffer(vector<string>& buffer)
{
    buffer[m_point.y][m_point.x] = '#';
}

void Object::update()
{
}

bool Object::collision_check(Point point)
{
    return false;
}
