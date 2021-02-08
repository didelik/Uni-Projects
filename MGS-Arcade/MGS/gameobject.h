#pragma once
#include "config.h"

class Collidable {
	virtual Disk getUpperHull() const = 0;
	virtual Disk getLowerHull() const = 0;
	virtual Disk getHeadHull() const = 0;
};

 class GameObject {
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void init() = 0;
};