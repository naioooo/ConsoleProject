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

void Object::draw()
{
    cout << "@" << endl;
}

void Object::insertbuffer(vector<string>& buffer)
{
    buffer[m_point.y][m_point.x] = '#';
}
