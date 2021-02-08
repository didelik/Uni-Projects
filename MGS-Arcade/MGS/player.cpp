#include "player.h"
#include <iostream>

Disk Player::getPunchHull() { // Gets Player collision hull
	Disk disk;
	if (getDirection() == 1) {
		disk.cx = pos_x + 3;
		disk.cy = pos_y - 62;
	} 
	else if(getDirection() == 2) {
		disk.cx = pos_x - 10;
		disk.cy = pos_y - 13;
	}
	else if (getDirection() == 3) {
		disk.cx = pos_x - 23;
		disk.cy = pos_y - 45;
	}
	else {
		disk.cx = pos_x + 23;
		disk.cy = pos_y - 45;
	}
	disk.radius = 10;
	return disk;
}

void Player::update() { // Player update
	
	graphics::MouseState mouse;
	graphics::getMouseState(mouse);

	if (getSpe()) { // Speed Power up
		setSpeed(0.4f);
	}
	else { // Normal Speed
		setSpeed(0.2f);
	}

	if (graphics::getGlobalTime() < lastpunch) { // Control locked
		setAction("punch");
		setIdent("");
	}
	else if (graphics::getGlobalTime() > lastpunch + 100.0f) { // Control unlocked

		if (mouse.button_left_pressed && getCurrentWeapon() == 1) { // Punch
			lastpunch = graphics::getGlobalTime() + 300.0f;
		}

		if (graphics::getKeyState(graphics::SCANCODE_W) || graphics::getKeyState(graphics::SCANCODE_UP)) { // Walk Up
			setAction("walk");
			setIdent("1_");

			setPos_y(getPos_y() - getSpeed() * graphics::getDeltaTime());
			setDirection(1);
		}
		else if (graphics::getKeyState(graphics::SCANCODE_S) || graphics::getKeyState(graphics::SCANCODE_DOWN)) { // Walk Down
			setAction("walk");
			setIdent("1_");

			setPos_y(getPos_y() + getSpeed() * graphics::getDeltaTime());
			setDirection(2);
		}
		else if (graphics::getKeyState(graphics::SCANCODE_A) || graphics::getKeyState(graphics::SCANCODE_LEFT)) { // Walk Left
			setAction("walk");
			setIdent("1_");

			setPos_x(getPos_x() - getSpeed() * graphics::getDeltaTime());
			setDirection(3);
		}
		else if (graphics::getKeyState(graphics::SCANCODE_D) || graphics::getKeyState(graphics::SCANCODE_RIGHT)) { // Walk Right
			setAction("walk");
			setIdent("1_");

			setPos_x(getPos_x() + getSpeed() * graphics::getDeltaTime());
			setDirection(4);
		}
		else {  // Static
			setAction("static");
			setIdent("");
		}

		if (graphics::getKeyState(graphics::SCANCODE_R) && graphics::getGlobalTime() > getCD() && getMagazine() < 10) { // Reload weapon
			if (getAmmo() > 0) {
				graphics::playSound(std::string(SOUND_PATH) + "reload.mp3", 0.4f, false);

				int delta = std::min(10 - getMagazine(), getAmmo());
				setMagazine(getMagazine() + delta);

				setAmmo(getAmmo() - delta);
				setCD(graphics::getGlobalTime() + 500.0f);
			}
		}

		if (graphics::getKeyState(graphics::SCANCODE_LSHIFT) && graphics::getGlobalTime() > swCD) { // Switch weapon
			graphics::playSound(std::string(SOUND_PATH) + "option_beep.mp3", 0.4f, false);

			if (getCurrentWeapon() == 1) {
				setCurrentWeapon(2);
				hasGun = "gun_";
			}
			else {
				setCurrentWeapon(1);
				hasGun = "";
			}

			swCD = graphics::getGlobalTime() + 200.0f;
		}

		if (graphics::getKeyState(graphics::SCANCODE_TAB) && graphics::getGlobalTime() > itCD) { // Switch item
			graphics::playSound(std::string(SOUND_PATH) + "option_beep.mp3", 0.4f, false);

			if (getCurrentItem() == 3) {
				setCurrentItem(1);
			}
			else {
				setCurrentItem(getCurrentItem() + 1);
			}

			itCD = graphics::getGlobalTime() + 200.0f;
		}
		 
		if (frenzy) { // Frenzy power up
			if (graphics::getKeyState(graphics::SCANCODE_SPACE)) {
				if (hasGun == "") {
					hasGun = "gun_";
					setCurrentWeapon(2);
				}
				else {
					hasGun = "";
					setCurrentWeapon(1);
				}
			}
		}
	}
	config();
	draw();
}

	Player::Player() { // Player constructor
		setType("player");
		setPos_x(CANVAS_WIDTH / 2);
		setPos_y(CANVAS_HEIGHT / 2);

		setDirection(2);
		ident = "";


		setSpeed(0.2f);

		setCheck(false);
		setIncr(300.f);

		setMagazine(10);
		setAmmo(20);
		setCapacity(20);
	}

	Player::~Player() { // Player deconstructor
	}


