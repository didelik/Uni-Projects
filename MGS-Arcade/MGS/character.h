#pragma once
#include "gameobject.h"

class Character : public GameObject, public Collidable {

protected:

	float pos_x = 0, pos_y = 0;
	int direction = 0;
	float size = 170;
	float speed = 0;
	bool isActive = false;

	std::string action;
	std::string hasGun = "";

	std::string ident= "_1";
	bool check=false;
	float time_increment=0;
	std::string path;
	int magazine = 0;
	float CD = 0.0f;
	float takenDamage;

	bool inv = false;
	bool spe = false;

	std::string type;
	float orig_y = 0;

public:

	std::string getType() { return type; };
	void setType(std::string t) { type = t; setPath(std::string(ENEMY_PATH) + getType() + "\\"); if (getType() == "Robot") { setSize(200); } };

	float getPos_x() { return pos_x; };
	void setPos_x(float x) { pos_x = x; };

	float getPos_y() { return pos_y; };
	void setPos_y(float y) { pos_y = y; };

	int getDirection() { return direction; };
	void setDirection(int dir) { direction = dir; };

	int getSize() { return size; };
	void setSize(float sz) { size = sz; };

	float getSpeed() { return speed; };
	void setSpeed(float s) { speed = s; };

	bool getActive() { return isActive; };
	void setActive(bool b) { isActive = b; };

	std::string getAction() { return action; };
	void setAction(std::string a) { action = a; setPath(std::string(PLAYER_PATH) + hasGun + getAction() + "_"); };

	bool getCheck() { return check; };
	void setCheck(bool c) { check = c; };

	float getIncr() { return time_increment; };
	void setIncr(float i) { time_increment = i; };

	std::string getPath() { return path; };
	void setPath(std::string p) { path = p; };

	std::string getIdent() { return ident; };
	void setIdent(std::string s) { ident = s; };

	int getMagazine() { return magazine; };
	void setMagazine(int m) { magazine = m; };

	float getCD() { return CD; };
	void setCD(float cd) { CD = cd; };

	float getTakenDamage() { return takenDamage; };
	void setTakenDamage(float td) { takenDamage = td; };

	bool getInv() { return inv; };
	void setInv(bool b) { inv = b; };

	bool getSpe() { return spe; };
	void setSpe(bool b) { spe = b; };

	float get_orig_y() { return orig_y; };
	void set_orig_y(float v) { orig_y = v; };

	void flipImage();

	void config();

	Disk getUpperHull() const override;
	Disk getLowerHull() const override;
	Disk getHeadHull() const override;

	void update() override {};
	void draw() override;
	void init() override {};
};
