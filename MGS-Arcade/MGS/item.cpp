#include "item.h"

Disk Item::getCollisionHull() const {
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = 7;
	return disk;
}


void Item::update() {
	setPos_x(getPos_x()- 0.01 * graphics::getDeltaTime());

	if (getType() == "basic_bullet") {
		setSize((50 - 20) + (getPos_y() * 20) / (CANVAS_HEIGHT / 2));
	}
	else {
		setSize((60 - 20) + (getPos_y() * 20) / (CANVAS_HEIGHT / 2));
	}
	draw();
}

void Item::draw() {
	graphics::Brush brush;
	brush.outline_opacity = 0.0f;

	brush.texture = ICON_PATH + getType() + ".png";

	graphics::drawRect(getPos_x(), getPos_y(), getSize(), getSize(), brush);
}

void Item::init() {}

Item::Item(float x, float y) {
	setPos_x(x);
	setPos_y(y);

	setActive(true);
}

Item::Item() {}

Item::~Item() {}
