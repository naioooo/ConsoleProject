#pragma once
#include "library.h"

class Scene
{
private:



public:
	Scene();
	~Scene() = default;

	virtual void loop() = 0;
	virtual void draw() = 0;
	virtual void input() = 0;
};

