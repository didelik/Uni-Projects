#include "ui.h"

void Ui::update(int m, int a, int c, float cd) {
	draw(m, a, c, cd);
}

void Ui::drawEffect() {
	graphics::Brush brHC;
	brHC.outline_opacity = 0.0f;
	
	if (getTimer() > 999.999f) {
		if (getEffect() == 1) {
			graphics::drawText(130, CANVAS_HEIGHT - 200, 27, "Instakill Duration :", brHC);
		}
		else if (getEffect() == 2) {
			graphics::drawText(130, CANVAS_HEIGHT - 200, 27, "Speed Duration :", brHC);
		}
		else if (getEffect() == 3) {
			graphics::drawText(130, CANVAS_HEIGHT - 200, 27, "Invisibility Duration :", brHC);
		}
		else if (getEffect() == 4) {
			graphics::drawText(130, CANVAS_HEIGHT - 200, 27, "FRENZY :", brHC);
		}

		std::string val = std::to_string(getTimer());

		if (val.length() == 11) {
			val = "0" + val.substr(0, 1);
		}
		else if (val.length() == 12) {
			val = val.substr(0, 2);
		}

		graphics::drawText(130, CANVAS_HEIGHT - 170, 30, "0:" + val, brHC);
	}
}


void Ui::drawHC() {
	graphics::Brush brHC;
	brHC.outline_opacity = 0.0f;

	if (getHC() > 0) {
		graphics::drawText(CANVAS_WIDTH - 300, 880, 40, "Headshot Multiplier x" + std::to_string(getHC()), brHC);
	}
}

void Ui::drawLives() {
	graphics::Brush brlive1;
	graphics::Brush brlive2;
	graphics::Brush brlive3;

	brlive1.outline_opacity = 0.0f;
	brlive2.outline_opacity = 0.0f;
	brlive3.outline_opacity = 0.0f;

	if (getLives() <= 0) {

		brlive1.texture = std::string(ICON_PATH) + "empty" + adding + ".png";
		brlive2.texture = std::string(ICON_PATH) + "empty" + adding + ".png";
		brlive3.texture = std::string(ICON_PATH) + "empty" + adding + ".png";

		graphics::drawRect(CANVAS_WIDTH - 150, 40, 50, 50, brlive1);
		graphics::drawRect(CANVAS_WIDTH - 100, 40, 50, 50, brlive2);
		graphics::drawRect(CANVAS_WIDTH - 50, 40, 50, 50, brlive3);

	}

	if (getLives() == 1) {
		if ((graphics::getGlobalTime() < dangerIncr) == false) {
			check = !check;
			dangerIncr += 300;
		}

		if (check) {
			adding = "2";
		}
		else {
			adding = "";
		}
		
		brlive1.texture = std::string(ICON_PATH) + "half" + adding + ".png";
		brlive2.texture = std::string(ICON_PATH) + "empty" + adding + ".png";
		brlive3.texture = std::string(ICON_PATH) + "empty" + adding + ".png";

		graphics::drawRect(CANVAS_WIDTH - 150, 40, 50, 50, brlive1);
		graphics::drawRect(CANVAS_WIDTH - 100, 40, 50, 50, brlive2);
		graphics::drawRect(CANVAS_WIDTH - 50, 40, 50, 50, brlive3);
	}
	else {
		if (getLives() == 0) {
			brlive1.texture = std::string(ICON_PATH) + "empty" + ".png";
			brlive2.texture = std::string(ICON_PATH) + "empty" + ".png";
			brlive3.texture = std::string(ICON_PATH) + "empty" + ".png";
		}

		else if (getLives() == 2) {
			brlive1.texture = std::string(ICON_PATH) + "full.png";
			brlive2.texture = std::string(ICON_PATH) + "empty.png";
			brlive3.texture = std::string(ICON_PATH) + "empty.png";
		}

		else if (getLives() > 2 && getLives() < 5) {

			brlive1.texture = std::string(ICON_PATH) + "full.png";
			brlive3.texture = std::string(ICON_PATH) + "empty.png";

			if (getLives() == 4) {
				brlive2.texture = std::string(ICON_PATH) + "full.png";
			}
			else if (getLives() == 3) {
				brlive2.texture = std::string(ICON_PATH) + "half.png";
			}
		}

		else if (getLives() > 4 && getLives() < 7) {
			brlive1.texture = std::string(ICON_PATH) + "full.png";
			brlive2.texture = std::string(ICON_PATH) + "full.png";

			if (getLives() == 5) {
				brlive3.texture = std::string(ICON_PATH) + "half.png";
			}
			else if (getLives() == 6) {
				brlive3.texture = std::string(ICON_PATH) + "full.png";
			}
		}
		graphics::drawRect(CANVAS_WIDTH - 150, 40, 50, 50, brlive1);

		if (getEffect() == 4) {

			brlive1.texture = std::string(ICON_PATH) + "infinity.png";

			graphics::drawText(CANVAS_WIDTH - 105, 47, 40, "x", brlive1);

			graphics::drawRect(CANVAS_WIDTH - 50, 40, 70, 70, brlive1);


		}
		else {
			graphics::drawRect(CANVAS_WIDTH - 100, 40, 50, 50, brlive2);
			graphics::drawRect(CANVAS_WIDTH - 50, 40, 50, 50, brlive3);
		}
	}
}

void Ui::drawInventory(int m, int a, int c, float cd) {
	graphics::Brush brinv;
	brinv.outline_opacity = 0.0f;

	graphics::Brush backround;
	backround.outline_opacity = 0.0f;
	backround.fill_color[0] = 1.0f;
	backround.fill_color[1] = 0.0f;
	backround.fill_color[2] = 0.0f;
	backround.fill_opacity = 0.7f;

	if (getCurrentWeapon()==1 && getEffect() != 4) {
		brinv.texture = std::string(ICON_PATH) + "melee.png";
	}
	else {
		if (getEffect() == 4) {
			graphics::drawText(180, CANVAS_HEIGHT - 80, 50, "AMMO  ", brinv);
			graphics::drawText(277, CANVAS_HEIGHT - 90, 50, "x", brinv);

			brinv.texture = std::string(ICON_PATH) + "infinity.png";

			graphics::drawRect(370, CANVAS_HEIGHT - 100, 165, 165, brinv);
		}

		else if (m == 0 && a == 0) {
			graphics::drawText(180, CANVAS_HEIGHT - 100, 40, "OUT OF BULLETS", brinv);
			graphics::drawRect(278, CANVAS_HEIGHT - 114, 220, 50, backround);
		}

		else if(m==0 && a > 0){
			graphics::drawText(180, CANVAS_HEIGHT - 100, 40, "PRESS R TO RELOAD", brinv);
			graphics::drawRect(293, CANVAS_HEIGHT - 114, 250, 50, backround);
		}
		
		else if (graphics::getGlobalTime() < cd && m == 10) {
			graphics::drawText(180, CANVAS_HEIGHT - 100, 40, "RELOADING", brinv);
			graphics::drawRect(245, CANVAS_HEIGHT - 114, 150, 50, backround);
		}

		else {
			graphics::drawText(180, CANVAS_HEIGHT - 100, 40, "AMMO : " + std::to_string(m) + " / " + std::to_string(a), brinv);
			graphics::drawText(180, CANVAS_HEIGHT - 50, 40, "CAPACITY : " + std::to_string(c), brinv);

			if (a == c) {
				graphics::drawRect(261, CANVAS_HEIGHT - 60, 190, 50, backround);
			}
		}
		brinv.texture = std::string(ICON_PATH) + "weapon.png";
	}
	graphics::drawRect(90, CANVAS_HEIGHT - 100, 185, 185, brinv);
	
	if (getCurrentItem() == 1) {
		if (getHasStr()) {
			brinv.texture = std::string(ICON_PATH) + "strength_inv.png";
		}
		else {
			brinv.texture = std::string(ICON_PATH) + "strength_inv_missing.png";
		}
	}
	else if (getCurrentItem() == 2) {
		if (getHasSpe()) {
			brinv.texture = std::string(ICON_PATH) + "speed_inv.png";
		}
		else {
			brinv.texture = std::string(ICON_PATH) + "speed_inv_missing.png";
		}
	}
	else if (getCurrentItem() == 3) {
		if (getHasInv()) {
			brinv.texture = std::string(ICON_PATH) + "invisibility_inv.png";
		}
		else {
			brinv.texture = std::string(ICON_PATH) + "Invisibility_inv_missing.png";
		}
	}

	graphics::drawRect(90, CANVAS_HEIGHT - 200, 170, 170, brinv);
}

void Ui::drawScore() {
	graphics::Brush brScore;
	brScore.outline_opacity = 0.0f;

	graphics::drawText(50, 51, 50, "SCORE : " + std::to_string(getScore()), brScore);
}

void Ui::draw(int m, int a, int c, float cd) {
	drawEffect();
	drawHC();

	drawLives();
	drawInventory(m, a, c, cd);
	drawScore();
}

Ui::Ui() {
}

Ui::~Ui() {}
