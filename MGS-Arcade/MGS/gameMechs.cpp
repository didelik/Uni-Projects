#include "gameMechs.h"

void GameMechs::loadImages() {
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "blur.png";
	graphics::drawRect(3*CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
	br.texture = std::string(ASSET_PATH) + "BG_sky.png";
	graphics::drawRect(3 * CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
	br.texture = std::string(ASSET_PATH) + "BG_ground.png";
	graphics::drawRect(3 * CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
	br.texture = std::string(ASSET_PATH) + "BG_mountains.png";
	graphics::drawRect(3 * CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

}

void GameMechs::drawPause() {
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "blur.png";
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
	graphics::drawText(CANVAS_WIDTH / 2 - 300, CANVAS_HEIGHT / 2,50 ,"Game paused. Press <P> to continue" , br);

}

void GameMechs::drawOver() {
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "blur.png";
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
	graphics::drawText(CANVAS_WIDTH / 2 - 300, CANVAS_HEIGHT / 2, 70, "GAME OVER", br);
	graphics::drawText(CANVAS_WIDTH / 2 - 300, CANVAS_HEIGHT / 2 + 50, 50, "Press <SPACE> to continue", br);

}


void GameMechs::drawWon() {
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "blur.png";
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
	graphics::drawText(CANVAS_WIDTH / 2 - 300, CANVAS_HEIGHT / 2, 70, "MISSION ACOMPLISHED", br);
	graphics::drawText(CANVAS_WIDTH / 2 - 300, CANVAS_HEIGHT / 2+50, 50, "Press <SPACE> to continue", br);
}

void GameMechs::updateBackround() { // Update Backround
	bg_x -= 0.01 * graphics::getDeltaTime();
	mbg_x -= 0.005 * graphics::getDeltaTime();
	sbg_x -= 0.002 * graphics::getDeltaTime();

	if (bg_x < -CANVAS_WIDTH / 2) {
		bg_x = CANVAS_WIDTH / 2;
	}

	if (mbg_x < -CANVAS_WIDTH / 2) {
		mbg_x = CANVAS_WIDTH / 2;
	}

	if (sbg_x < -CANVAS_WIDTH / 2) {
		sbg_x = CANVAS_WIDTH / 2;
	}
}

void GameMechs::drawBackround() { // Draw Backround
	graphics::Brush br;
	br.outline_opacity = 0.0f;

	br.texture = std::string(ASSET_PATH) + "BG_sky.png";
	graphics::drawRect(sbg_x, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
	graphics::drawRect(sbg_x + CANVAS_WIDTH, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	br.texture = std::string(ASSET_PATH) + "BG_ground.png";
	graphics::drawRect(bg_x, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
	graphics::drawRect(bg_x + CANVAS_WIDTH, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	br.texture = std::string(ASSET_PATH) + "BG_mountains.png";
	graphics::drawRect(mbg_x, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
	graphics::drawRect(mbg_x + CANVAS_WIDTH, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
}
