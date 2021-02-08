#pragma once
#include "character.h"

class Enemy : public Character{
	int hp;
	float xlimit = 0;
	float ylimit = 0;
	float counter=0.0f;
	float incr;

	float done=0.0f;
	float done1 = 0.0f;

public:

	int getHp() { return hp; };
	void setHp(int h) { hp = h;};

	float get_xlimit() { return xlimit; };
	void set_xlimit(float v) { xlimit = v; };

	float get_ylimit() { return ylimit; };
	void set_ylimit(float v) { ylimit = v; };

	void update() override;

	Enemy();
	~Enemy();
};
