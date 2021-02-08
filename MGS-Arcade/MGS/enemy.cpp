#include "enemy.h"

void Enemy::update() {
	graphics::Brush br;

	if (graphics::getGlobalTime() < takenDamage + 500.0) {
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 0.0f;
		br.fill_color[2] = 0.0f;

		graphics::drawText(getPos_x() - 15, getPos_y() - 70, 25, "HP : " + std::to_string(getHp()), br);
	}

	if (getType() == "Old_Man") {
		if (getPos_x() < CANVAS_WIDTH - 200) {
			setSpeed(0.01f);
		}
		setPos_x(getPos_x() - getSpeed() * graphics::getDeltaTime());
		setDirection(3);
	}
	else if (getType() == "Naked_Soldier") {
		if (getPos_y() > CANVAS_HEIGHT - 100 && done == 0.0f) {
			setPos_y(getPos_y() - getSpeed() * graphics::getDeltaTime());
			setDirection(1);
		}
		else if (getPos_y() < CANVAS_HEIGHT - 100 && done == 0.0f) {
			done = graphics::getGlobalTime() + 700.0f;
		}

		else if (graphics::getGlobalTime() < done + 1500.0f && graphics::getGlobalTime() < done) {
			graphics::drawText(getPos_x() - 15, getPos_y() - 100, 40, "I need To warn the Doctor.", br);
			setDirection(2);
		}

		else if (graphics::getGlobalTime() > done) {
			setSpeed(0.18f);
			setPos_y(getPos_y() + getSpeed() * graphics::getDeltaTime());
		}
	}

	else {
		if (counter == 0) {
			if (getPos_x() > get_xlimit()) {
				setPos_x(getPos_x() - getSpeed() * graphics::getDeltaTime());
				setDirection(3);
			}
			else {
				counter = graphics::getGlobalTime();
			}
		}
		else {
			if (graphics::getGlobalTime() < counter + incr) {
				if (getDirection() == 1) {
					setPos_y(getPos_y() - getSpeed() * graphics::getDeltaTime());
				}
				else if (getDirection() == 2) {
					setPos_y(getPos_y() + getSpeed() * graphics::getDeltaTime());
				}
				else if (getDirection() == 3) {
					setPos_x(getPos_x() - getSpeed() * graphics::getDeltaTime());
				}
				else if (getDirection() == 4) {
					setPos_x(getPos_x() + getSpeed() * graphics::getDeltaTime());
				}
			}
			else {
				counter += incr;
				setDirection(1 + rand() / (RAND_MAX / (4 - 1 + 1) + 1));
			}
		}
	}

	config();
	draw();
}

Enemy::Enemy() {
	setPos_x(CANVAS_WIDTH + 200);
	setPos_y(170 + (CANVAS_HEIGHT - 170) * rand() / (float)RAND_MAX);
	set_orig_y(getPos_y());

	set_xlimit((CANVAS_WIDTH - CANVAS_WIDTH / 4) + rand() / (float)(RAND_MAX / ((CANVAS_WIDTH - CANVAS_WIDTH / 5) - (CANVAS_WIDTH - CANVAS_WIDTH / 4) + 1) + 1));
	incr = (1500.0f) + rand() / (RAND_MAX / ((2500.0f) - (1500.0f) + 1) + 1);

	setDirection(5);
	setSpeed(0.09f);

	setHp(100);
	setActive(true);

	setCheck(false);
	setIncr(300.f);
	setMagazine(5);
}

Enemy::~Enemy() {
}
