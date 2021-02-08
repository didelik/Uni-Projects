#include "character.h"
#include <iostream>

void Character::flipImage() {
    if (ident != "") {
        if (check) {
            setIdent("_2");
        }
        else {
            setIdent("_1");
        }
    }
}

void Character::config() {
    setPos_x(getPos_x() - 0.01 * graphics::getDeltaTime());

    if (getType() == "player" && getPos_x() < 0) {
        pos_x = 0;
    }
    else if (getType() == "player" && getPos_x() > CANVAS_WIDTH) {
        pos_x = CANVAS_WIDTH;
    }
    else if (getPos_y() < 150) {
        pos_y = 150;
    }
    else if (getType() == "player" && getPos_y() > CANVAS_HEIGHT) {
        pos_y = CANVAS_HEIGHT;
    }

    if (getType() != "player" && getPos_y() < 170) {
        setDirection(2);
    }

    if (getType() != "player" && (getPos_x() > CANVAS_WIDTH + 150 || getPos_y() > CANVAS_HEIGHT + 150 || getPos_x() < -150) && getPos_y() != get_orig_y()) {
        setActive(false);
    }
    if (getType() == "Robot") {
        setSize((200 - 40) + (getPos_y() * 40) / (CANVAS_HEIGHT / 2));
    }
    else {
        setSize((170 - 40) + (getPos_y() * 40) / (CANVAS_HEIGHT / 2));
    }
}

Disk Character::getUpperHull() const {
    Disk disk;
    disk.cx = pos_x;
    disk.cy = pos_y - 17;
    disk.radius = 26;
    return disk;
}

Disk Character::getLowerHull() const {
    Disk disk;
    disk.cx = pos_x;
    disk.cy = pos_y + 30;
    disk.radius = 26;
    return disk;
}


Disk Character::getHeadHull() const {
    Disk disk;
    disk.cx = pos_x;
    disk.cy = pos_y - 52;
    disk.radius = 15;
    return disk;
}

void Character::draw() {
    graphics::Brush brush;

    if (graphics::getGlobalTime() > time_increment) {
        check = !check;

        if (getSpe()) {
            time_increment += 100;
        }
        else {
            time_increment += 200;
        }
    }

    flipImage();

    brush.outline_opacity = 0.0f;
    if (getInv()) {
        brush.fill_opacity = 0.5f;
    }
    else {
        brush.fill_opacity = 1.0f;
    }

    if (getSpe() && getAction() == "walk") {
        brush.texture = std::string(PLAYER_PATH) + "lines_" + std::to_string(getDirection()) + getIdent() + ".png";
        graphics::drawRect(getPos_x(), getPos_y(), getSize(), getSize(), brush);
        brush.texture = "";
    }

    brush.texture = getPath() + std::to_string(getDirection()) + getIdent() + ".png";

    if (graphics::getGlobalTime() < takenDamage + 200) {
        brush.fill_color[0] = 1.0f;
        brush.fill_color[1] = 0.0f;
        brush.fill_color[2] = 0.0f;
    }

    graphics::drawRect(getPos_x(), getPos_y(), getSize(), getSize(), brush);

    graphics::Brush br;

    br.texture = "";

    br.fill_color[0] = 0.3f;
    br.fill_color[1] = 0.3f;
    br.fill_color[2] = 0.3f;
    br.gradient = false;
    br.fill_opacity = 0.0f;
    br.outline_opacity = 0.0f;

    Disk upper = getUpperHull();
    graphics::drawDisk(upper.cx, upper.cy, upper.radius, br);  //upper body disk


    Disk lower = getLowerHull();
    graphics::drawDisk(lower.cx, lower.cy, lower.radius, br); //lower body disk


    Disk head = getHeadHull();
    graphics::drawDisk(head.cx, head.cy, head.radius, br); //head disk
}