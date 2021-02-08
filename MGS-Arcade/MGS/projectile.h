#pragma once
#include "item.h"

class Projectile : public Item {

	int direction = 0;
	float speed = 0;
	bool str = false;

public:

	int getDirection() { return direction; };
	void setDirection(int dir) { direction = dir; };

	float getSpeed() { return speed; };
	void setSpeed(float s) { speed = s; };

	void update() override;
	void draw() override;
	void init() override;

	Projectile(float x,float y,int dir, bool str);
	~Projectile();
};