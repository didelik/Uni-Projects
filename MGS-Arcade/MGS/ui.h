#pragma once
#include "character.h"

class Ui {

	int lives = 6;
	int score = 0;
	float dangerIncr = 0;
	bool check = true;
	std::string adding = "";

	int HC = 0;

	int effect = 0;
	float timer = 0.0f;

	int currentWeapon = 1;
	int currentItem = 1;

	bool  hasStr = false;
	bool hasSpe = false;
	bool hasInv = false;

public:
	int getLives() { return lives; };
	void setLives(int l) { lives = l; };

	int getScore() { return score; };
	void setScore(int s) { score = s; };

	int getHC() { return HC; };
	void setHC(int hc) { HC = hc; };

	int getEffect() { return effect; };
	void setEffect(int e) { effect = e; };

	float getTimer() { return timer; };
	void setTimer(float t) { timer = t; };

	bool getHasStr() { return hasStr; };
	void setHasStr(bool b) { hasStr = b; }

	bool getHasSpe() { return hasSpe; };
	void setHasSpe(bool b) { hasSpe = b; }

	bool getHasInv() { return hasInv; };
	void setHasInv(bool b) { hasInv = b; }

	int getCurrentWeapon() { return currentWeapon; };
	void setCurrentWeapon(int c) { currentWeapon = c; };

	int getCurrentItem() { return currentItem; };
	void setCurrentItem(int c) { currentItem = c; };

	void update(int m, int a, int c, float cd);

	void drawEffect();
	void drawHC();
	void drawLives();
	void drawInventory(int m, int a, int c, float cd);
	void drawScore();
	void draw(int m, int a, int c, float cd);

	Ui();
	~Ui();
};
