#pragma once
#include "gameobject.h"

class Item : public GameObject {

	float pos_x = 0, pos_y = 0;
	float size = 60;
	std::string type;
	int value = 0;
	bool isActive = false;

public:

	float getPos_x() { return pos_x; }
	void setPos_x(float x) { pos_x = x; }

	float getPos_y() { return pos_y; }
	void setPos_y(float y) { pos_y = y; }

	int getSize() { return size; };
	void setSize(float sz) { size = sz; };

	std::string getType() { return type; };
	void setType(std::string t) { type = t; if (getType() == "basic_bullet") { setSize(50); } };

	int getValue() { return value; };
	void setValue(int v) { value = v; };

	bool getActive() { return isActive; };
	void setActive(bool b) { isActive = b; };

	Disk getCollisionHull() const;

	void update() override;
	void draw() override;
	void init() override;

	Item(float x, float y);
	Item();
	~Item();
};