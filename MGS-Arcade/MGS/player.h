#pragma once
#include "character.h"

class Player : public Character {
	float lastpunch;
	int capacity;
	int ammo;

	int currentWeapon = 1;
	int currentItem = 1;

	bool str = false;
	bool frenzy = false;

	float swCD = 0.0f;
	float itCD = 0.0f;

public:

	int getCapacity() { return capacity; };
	void setCapacity(int c) { capacity = c; };

	int getAmmo() { return ammo; };
	void setAmmo(int a) { ammo = a; };

	int getCurrentWeapon() { return currentWeapon; };
	void setCurrentWeapon(int c) { currentWeapon = c; };

	int getCurrentItem() { return currentItem; };
	void setCurrentItem(int c) { currentItem = c; };

	bool getStr() { return str; };
	void setStr(bool b) { str = b; };

	bool getFrenzy() { return frenzy; };
	void setFrenzy(bool fr) { frenzy = fr; };

	Disk getPunchHull();

	void update() override;

	Player();
	~Player();
};
