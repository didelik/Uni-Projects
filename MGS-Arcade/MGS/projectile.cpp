#include "projectile.h"

void Projectile::update() {

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

	if ((getPos_x() > CANVAS_WIDTH + 50 || getPos_y() > CANVAS_HEIGHT + 50 || getPos_x() < -50 || getPos_y() < -50)) {
		setActive(false);
	}
}

void Projectile::draw() {
	graphics::Brush brush;

	brush.outline_opacity = 0.0f;
	brush.texture = std::string(ICON_PATH) + "Basic_Bullet.png";

	if (getDirection() == 1) {
		graphics::setOrientation(-90.0f);
	}
	else if (getDirection() == 2) {
		graphics::setOrientation(90.0f);
	}
	else if (getDirection() == 4) {
		graphics::setOrientation(180.0f);
	}


	if (str) {
		brush.fill_color[0] = 1.0f;
		brush.fill_color[1] = 0.0f;
		brush.fill_color[2] = 0.0f;
	}

	graphics::drawRect(getPos_x(), getPos_y(), 30, 30, brush);

	brush.fill_color[0] = 0.0f;
	brush.fill_color[1] = 0.0f;
	brush.fill_color[2] = 0.0f;
	graphics::drawRect(getPos_x(), getPos_y()+70, 30, 30, brush);

	graphics::resetPose();

}

void Projectile::init() {
}

Projectile::Projectile(float x,float y, int dir, bool st) {
	setActive(true);
	setSpeed(0.8f);

	str = st;

	setDirection(dir);

	if (getDirection() == 1) {
		setPos_x(x+5);
		setPos_y(y-70);
	}
	else if(getDirection() == 2) {
		setPos_x(x-5);
		setPos_y(y);
	}
	else if(getDirection() == 3) {
		setPos_x(x - 20);
		setPos_y(y - 30);
	}
	else if (getDirection() == 4) {
		setPos_x(x + 20);
		setPos_y(y - 30);
	}

	graphics::playSound(std::string(SOUND_PATH) + "gunshot.mp3", 0.4f, false);
}

Projectile::~Projectile() {
}
