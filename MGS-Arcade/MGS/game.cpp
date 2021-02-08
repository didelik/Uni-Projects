#include "game.h"
#include <iostream>

void Game::spawnItems(float x, float y) { // Spawn item
	srand(graphics::getGlobalTime());
	int rand_value = 1 + rand() % 100;

	if (rand_value > 0 && rand_value <= 60) {

		item = new Item(x, y + 30);

		if (rand_value > 0 && rand_value <= 15) {
			item->setType("ammo");
			item->setValue(15);
		}
		else if (rand_value > 15 && rand_value <= 25) {
			item->setType("med");
			item->setValue(1);
		}
		else if (rand_value > 25 && rand_value <= 30) {
			item->setType("cap");
			item->setValue(10);
		}
		else if (rand_value > 30 && rand_value <= 40) {
			item->setType("strength");
		}
		else if (rand_value > 40 && rand_value <= 50) {
			item->setType("speed");
		}
		else {
			item->setType("invisibility");
		}
		items.push_back(item);
	}

}

void Game::updateItems() { // Item Update
	if (use_time > 0.0f) {
		ui->setTimer((use_time + 26000.00) - graphics::getGlobalTime());
	}

	if (ui->getTimer() < 0 && use_time != 0.0f) {
		use_time = 0.0f;
		resetEffects();
		graphics::playMusic(std::string(SOUND_PATH) + "Zanzibar Breeze.mp3", 0.3f, true);
	}

	for (size_t i = 0; i < items.size(); ++i) {
		if (items.at(i)->getActive() == false) {
			items.erase(items.begin() + i);
		}
		else {
			items.at(i)->update();
		}
	}
}

void Game::drawItems() { // Draw Items
	for (size_t i = 0; i < items.size(); ++i) {
		items.at(i)->draw();
	}
}

void Game::resetEffects() { // Remove Effect
	if (old == true) {
		graphics::stopMusic(0);
	}

	player->setStr(false);
	player->setSpe(false);
	player->setInv(false);
	player->setFrenzy(false);
	ui->setEffect(0);
}

void Game::useItem() { // Shoot projectile or use potion
	graphics::MouseState mouse;
	graphics::getMouseState(mouse);

	if ((mouse.button_left_pressed && player->getCurrentWeapon() == 2 && player->getFrenzy() == false)
		|| (player->getFrenzy() && graphics::getKeyState(graphics::SCANCODE_SPACE))) {
		if (graphics::getGlobalTime() > player->getCD() && player->getMagazine() > 0) {
			projectile = new Projectile(player->getPos_x(), player->getPos_y(), player->getDirection(), player->getStr());
			projectile->setType("player");
			projectiles.push_back(projectile);

			if (player->getFrenzy()) {
				player->setCD(graphics::getGlobalTime() + 150.0f);
				player->setStr(false);
				player->setInv(false);
				player->setSpeed(false);
			}
			else {
				player->setCD(graphics::getGlobalTime() + 300.0f);
			}
			player->setMagazine(player->getMagazine() - 1);
		}

		else if (player->getMagazine() == 0) {
			graphics::playSound(std::string(SOUND_PATH) + "no_bullets.mp3", 0.4f, false);
		}
	}
	else if (graphics::getKeyState(graphics::SCANCODE_E) && player->getCurrentItem() == 1 && ui->getHasStr() == true) {
		resetEffects();

		ui->setEffect(1);
		ui->setHasStr(false);

		player->setStr(true);

		graphics::playSound(std::string(SOUND_PATH) + "potion_drink.mp3", 0.4f, false);
		graphics::playMusic(std::string(SOUND_PATH) + "strength_theme.mp3", 0.3f, false);

		use_time = graphics::getGlobalTime();
	}
	else if (graphics::getKeyState(graphics::SCANCODE_E) && player->getCurrentItem() == 2 && ui->getHasSpe() == true) {
		resetEffects();

		ui->setEffect(2);
		ui->setHasSpe(false);

		player->setSpe(true);

		graphics::playSound(std::string(SOUND_PATH) + "potion_drink.mp3", 0.4f, false);
		graphics::playMusic(std::string(SOUND_PATH) + "speed_theme.mp3", 0.3f, false);

		use_time = graphics::getGlobalTime();
	}
	else if (graphics::getKeyState(graphics::SCANCODE_E) && player->getCurrentItem() == 3 && ui->getHasInv() == true) {
		resetEffects();

		ui->setEffect(3);
		ui->setHasInv(false);

		player->setInv(true);

		graphics::playSound(std::string(SOUND_PATH) + "potion_drink.mp3", 0.4f, false);
		graphics::playMusic(std::string(SOUND_PATH) + "inv_theme.mp3", 0.3f, false);

		use_time = graphics::getGlobalTime();
	}
}

bool Game::checkFire(Enemy* enemy) { // Checks enemy fire
	float ex = enemy->getPos_x();
	float ey = enemy->getPos_y();

	float px = player->getPos_x();
	float py = player->getPos_y();

	if ((px >= ex - 20) && (px <= ex + 20)) {
		if (py <= ey) {
			if (enemy->getDirection() == 1) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			if (enemy->getDirection() == 2) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	else if ((py >= ey - 30) && (py <= ey + 30)) {
		if (px <= ex) {
			if (enemy->getDirection() == 3) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			if (enemy->getDirection() == 4) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	else {
		return false;
	}
}

void Game::updateProjectiles() { // Updates Projectiles

	for (size_t i = 0; i < projectiles.size(); ++i) {

		if ((projectiles.at(i)->getPos_x() > CANVAS_WIDTH + 50 || projectiles.at(i)->getPos_y() > CANVAS_HEIGHT + 50
			|| projectiles.at(i)->getPos_x() < -50 || projectiles.at(i)->getPos_y() < -50) && projectiles.at(i)->getType() == "player") {
			ui->setHC(0);
		}

		if (projectiles.at(i)->getActive() == false) {
			projectiles.erase(projectiles.begin() + i);
		}
		else {
			projectiles.at(i)->update();
		}
	}
}

void Game::drawProjectiles() { // Draw Projectiles
	for (size_t i = 0; i < projectiles.size(); ++i) {
		projectiles.at(i)->draw();
	}
}

int Game::checkCollisionHelp(Disk disk, Character* ch) { // Checks for collision between a Disk and a Character
	Disk disk_l = ch->getLowerHull();

	Disk disk_u = ch->getUpperHull();

	Disk disk_h = ch->getHeadHull();

	float dx_l = disk.cx - disk_l.cx;
	float dy_l = disk.cy - disk_l.cy;

	float dx_u = disk.cx - disk_u.cx;
	float dy_u = disk.cy - disk_u.cy;

	float dx_h = disk.cx - disk_h.cx;
	float dy_h = disk.cy - disk_h.cy;

	if (sqrt(dx_l * dx_l + dy_l * dy_l) < disk.radius + disk_l.radius) {
		return 1;
	}
	else if (sqrt(dx_u * dx_u + dy_u * dy_u) < disk.radius + disk_u.radius) {
		return 2;
	}
	else if (sqrt(dx_h * dx_h + dy_h * dy_h) < disk.radius + disk_h.radius) {
		return 3;
	}
	else {
		return 0;
	}
}

void Game::checkCollision() {
	Disk proj;

	for (size_t i = 0; i < projectiles.size(); ++i) {
		proj = projectiles.at(i)->getCollisionHull();

		if (projectiles.at(i)->getType() == "player") {
			for (size_t j = 0; j < enemies.size(); ++j) {

				collision = checkCollisionHelp(proj, enemies.at(j));

				if (collision == 1) {
					if (!player->getStr()) {
						enemies.at(j)->setHp(enemies.at(j)->getHp() - 35);
					}
					ui->setHC(0);
				}
				else if (collision == 2) {
					if (!player->getStr()) {
						enemies.at(j)->setHp(enemies.at(j)->getHp() - 50);
					}
					ui->setHC(0);
				}
				else if (collision == 3) {
					if (!player->getStr()) {
						enemies.at(j)->setHp(enemies.at(j)->getHp() - 100);
					}
					ui->setHC(ui->getHC() + 1);
				}

				if (collision != 0) {
					graphics::playSound(std::string(SOUND_PATH) + "enemy_hit.mp3", 0.4f, false);

					if (player->getStr()) {
						enemies.at(j)->setHp(0);
					}

					enemies.at(j)->setTakenDamage(graphics::getGlobalTime());
					projectiles.at(i)->setActive(false);

				}
			}
		}
		else {
			collision = checkCollisionHelp(proj, player);
			if (collision != 0) {
				std::string sound = std::to_string(1 + rand() % 2);
				graphics::playSound(std::string(SOUND_PATH) + "player_hit" + sound + ".mp3", 0.4f, false);

				player->setTakenDamage(graphics::getGlobalTime());
				projectiles.at(i)->setActive(false);

				ui->setLives(ui->getLives() - 1);

				if (ui->getLives() == 0) {
					over = true;
					graphics::playMusic(std::string(SOUND_PATH) + "tara.mp3", 0.4f, false);
				}
			}
		}
	}

	if (player->getAction() == "punch" && graphics::getGlobalTime() > punchCD) {
		Disk punch = player->getPunchHull();

		for (size_t j = 0; j < enemies.size(); ++j) {
			collision = checkCollisionHelp(punch, enemies.at(j));

			if (collision != 0) {
				enemies.at(j)->setTakenDamage(graphics::getGlobalTime());
				punchCD = graphics::getGlobalTime() + 400.0f;
				std::string punch = std::to_string(1 + rand() % 2);
				graphics::playSound(std::string(SOUND_PATH) + "whoosh.mp3", 0.3f, false);
				graphics::playSound(std::string(SOUND_PATH) + "punch" + punch + ".mp3", 0.4f, false);

				graphics::playSound(std::string(SOUND_PATH) + "enemy_hit.mp3", 0.4f, false);

				if (player->getStr()) {
					enemies.at(j)->setHp(0);
				}
				else {
					enemies.at(j)->setHp(enemies.at(j)->getHp() - 35);
				}
			}

		}
	}

	for (size_t j = 0; j < items.size(); ++j) {
		Disk item = items.at(j)->getCollisionHull();

		collision = checkCollisionHelp(item, player);

		if (collision == 1) {

			if (items.at(j)->getType() == "ammo") {
				if (player->getAmmo() < player->getCapacity()) {
					player->setAmmo(std::min(player->getAmmo() + items.at(j)->getValue(), player->getCapacity()));
					graphics::playSound(std::string(SOUND_PATH) + "picked_up.mp3", 0.4f, false);
					items.at(j)->setActive(false);
				}
			}
			else if (items.at(j)->getType() == "med") {
				if (ui->getLives() < 6) {
					ui->setLives(ui->getLives() + items.at(j)->getValue());
					graphics::playSound(std::string(SOUND_PATH) + "picked_up.mp3", 0.4f, false);
					items.at(j)->setActive(false);
				}
			}
			else if (items.at(j)->getType() == "cap") {
				if (player->getCapacity() < 70) {
					player->setCapacity(player->getCapacity() + items.at(j)->getValue());
					graphics::playSound(std::string(SOUND_PATH) + "picked_up.mp3", 0.4f, false);
					items.at(j)->setActive(false);
				}
			}
			else if (items.at(j)->getType() == "strength") {
				if (ui->getHasStr() == false) {
					graphics::playSound(std::string(SOUND_PATH) + "picked_up.mp3", 0.4f, false);
					ui->setHasStr(true);

					items.at(j)->setActive(false);
				}
			}
			else if (items.at(j)->getType() == "speed") {
				if (ui->getHasSpe() == false) {
					graphics::playSound(std::string(SOUND_PATH) + "picked_up.mp3", 0.4f, false);
					ui->setHasSpe(true);
					items.at(j)->setActive(false);
				}
			}
			else if (items.at(j)->getType() == "invisibility") {
				if (ui->getHasInv() == false) {
					graphics::playSound(std::string(SOUND_PATH) + "picked_up.mp3", 0.4f, false);
					ui->setHasInv(true);
					items.at(j)->setActive(false);
				}
			}
		}
	}
}

void Game::spawnEnemies() { // Spawn Enemies
	if ((enemies.size() < 5 && old == true) || (ui->getScore() > 150 && old_dead == true && enemies.size() < 25)) {
		enemy = new Enemy();

		if (ui->getScore() > 150 && old) {
			enemy->setType("Old_Man");
			enemy->setPos_x(CANVAS_WIDTH + 100);
			enemy->setPos_y(CANVAS_HEIGHT / 2);
			enemy->setSpeed(0.05f);
			enemy->setHp(30);

			countdown = graphics::getGlobalTime();


			old = false;

			graphics::stopMusic(0);
			graphics::playMusic(std::string(SOUND_PATH) + "Afterimage.mp3", 0.3f, false);
		}

		else if (ui->getScore() > 20 && naked) {
			enemy->setType("Naked_Soldier");
			enemy->setPos_x(2 * CANVAS_WIDTH / 3);
			enemy->setPos_y(CANVAS_HEIGHT + 100);

			naked = false;
		}

		else {
			srand(graphics::getGlobalTime());
			int rand_value = 1 + rand() % 20;

			if (rand_value > 0 && rand_value <= 10) {
				enemy->setType("Green_Soldier");
			}
			else if (rand_value <= 17) {
				enemy->setType("Red_Soldier");
				enemy->setHp(120);
			}
			else {
				enemy->setType("Robot");
				enemy->setHp(150);
			}

			if (enemies.size() != 0) {
				enemy->setIncr(enemies.at(0)->getIncr());
			}
		}

		enemies.push_back(enemy);
	}
}

void Game::updateEnemies() { // Update Enemies
	for (size_t i = 0; i < enemies.size(); ++i) {
		if (enemies.at(i)->getActive() == false) {

			if (enemies.at(i)->getType() == "Old_Man" && enemies.at(i)->getHp() <= 0) {
				old_dead = true;
				player->setFrenzy(true);
				ui->setEffect(4);
				use_time = graphics::getGlobalTime();

				graphics::playSound(std::string(SOUND_PATH) + "earthquake.mp3", 0.7f, false);

				graphics::stopMusic(0);
				graphics::playMusic(std::string(SOUND_PATH) + "An Advance.mp3", 0.3f, true);

			}
			else if (enemies.at(i)->getType() == "Naked_Soldier" && enemies.at(i)->getHp() <= 0) {
				ui->setScore(ui->getScore() + 50);
			}

			enemies.erase(enemies.begin() + i);
		}
		else if (enemies.at(i)->getHp() <= 0) {
			graphics::playSound(std::string(SOUND_PATH) + "pop.mp3", 0.4f, false);
			spawnItems(enemies.at(i)->getPos_x(), enemies.at(i)->getPos_y());


			if (ui->getHC() == 0) {
				ui->setScore(ui->getScore() + 10);
			}
			else {
				ui->setScore(ui->getScore() + (10 * ui->getHC()));
			}

			enemies.at(i)->setActive(false);
		}
		else {
			enemies.at(i)->update();

			if (checkFire(enemies.at(i)) && graphics::getGlobalTime() > enemies.at(i)->getCD() && enemies.at(i)->getMagazine() > 0 && (enemies.at(i)->getType() != "Old_Man" && enemies.at(i)->getType() != "Naked_Soldier") && (player->getInv() == false || enemies.at(i)->getType() == "Robot")) {
				projectile = new Projectile(enemies.at(i)->getPos_x(), enemies.at(i)->getPos_y(), enemies.at(i)->getDirection(), false);
				projectile->setType("enemy");
				projectiles.push_back(projectile);

				enemies.at(i)->setCD(graphics::getGlobalTime() + 1000);
				enemies.at(i)->setMagazine(enemies.at(i)->getMagazine() - 1);
			}

			if (enemies.at(i)->getMagazine() == 0) {

				enemies.at(i)->setMagazine(5);
				enemies.at(i)->setCD(graphics::getGlobalTime() + 1500.0f);
			}
		}
	}
}

void Game::drawEnemies() { // Draw Enemies
	for (size_t i = 0; i < enemies.size(); ++i) {
		enemies.at(i)->draw();
	}
}


void Game::resetAssets() {
	for (size_t i = 0; i < enemies.size(); ++i) {
		enemies.at(i)->setActive(false);
	}
}


void Game::updateGameplay() { // Update Game
	if (over || won) { // Game is Over
		resetAssets();

		if (graphics::getKeyState(graphics::SCANCODE_SPACE)) {

			game_initialized = false;
			over = false;
			graphics::stopMusic(0);
			graphics::playMusic(std::string(SOUND_PATH) + "MGS_MUSIC.mp3", 0.3f, true);

		}
	}
	else if (paused) { // Paused

	}
	else { // Gameplay

		graphics::Brush brCD;

		if (old) {
			graphics::drawText(50, 150, 40, "Capture The Dr.", brCD);
		}

		if (graphics::getGlobalTime() < countdown + 15000 && old_dead == false && !old) {


			graphics::drawText(50, 150, 40, "Waiting for extraction: ", brCD);
			if (((countdown + 15000.0f) - graphics::getGlobalTime()) > 999.999f) {

				std::string val = std::to_string((countdown + 15000.0f) - graphics::getGlobalTime());

				if (val.length() == 11) {
					val = "0" + val.substr(0, 1);
				}
				else if (val.length() == 12) {
					val = val.substr(0, 2);
				}

				graphics::drawText(365, 150, 40, "0:" + val, brCD);
			}

		}
		else if (old_dead) {
			graphics::drawText(50, 150, 40, "Mission failed, you are on your own.. ", brCD);
		}
		else if (graphics::getGlobalTime() > countdown + 10000 && old_dead == false && !old) {
			won = true;
			graphics::playMusic(std::string(SOUND_PATH) + "tara.mp3", 0.4f, false);
		}


		updateBackround();

		if (player->getFrenzy()) {
			ui->setLives(6);
			player->setMagazine(10);
		}

		checkCollision();

		updateItems();

		ui->setCurrentWeapon(player->getCurrentWeapon());
		ui->setCurrentItem(player->getCurrentItem());
		ui->update(player->getMagazine(), player->getAmmo(), player->getCapacity(), player->getCD());

		player->update();
		useItem();

		spawnEnemies();

		updateEnemies();

		updateProjectiles();
	}
	
	if (graphics::getKeyState(graphics::SCANCODE_P) && graphics::getGlobalTime() > pauseCD) { // Get Pause input
		graphics::playSound(std::string(SOUND_PATH) + "click.mp3", 0.4f, false);

		if (paused == true) {
			paused = false;
		}
		else {
			paused = true;
		}
		pauseCD = graphics::getGlobalTime() + 300.0f;
	}
}



void Game::drawGameplay() { // Draw Game

	if (over) {
		drawOver();
	}
	else if (paused) {
		drawPause();
	}
	else if (won) {
		drawWon();
	}
	else {
		drawBackround();

		drawItems();


		drawBackround();

		for (size_t i = 0; i < items.size(); ++i) {
			items.at(i)->draw();
		}

		drawEnemies();

		if (player && ui) {
			player->draw();
			ui->draw(player->getMagazine(), player->getAmmo(), player->getCapacity(), player->getCD());

		}
		drawProjectiles();
	}
}

void Game::updateMenu() { // Update Menu

	if (graphics::getGlobalTime() > menuCD) {
		if (graphics::getKeyState(graphics::SCANCODE_UP) || graphics::getKeyState(graphics::SCANCODE_W)) {
			if (cur_choice > 1) {
				graphics::playSound(std::string(SOUND_PATH) + "option_beep.mp3", 0.4f, false);

				cur_choice -= 1;
				menuCD = graphics::getGlobalTime() + 300.0f;
			}
		}
		if (graphics::getKeyState(graphics::SCANCODE_DOWN) || graphics::getKeyState(graphics::SCANCODE_S)) {
			if (cur_choice < 3) {
				graphics::playSound(std::string(SOUND_PATH) + "option_beep.mp3", 0.4f, false);
				cur_choice += 1;
				menuCD = graphics::getGlobalTime() + 300.0f;
			}
		}

		if (graphics::getKeyState(graphics::SCANCODE_RETURN)) {
			graphics::playSound(std::string(SOUND_PATH) + "click.mp3", 0.4f, false);

			if (cur_choice == 1) {
				graphics::stopMusic(0);
				graphics::playMusic(std::string(SOUND_PATH) + "Zanzibar Breeze.mp3", 0.3f, true);

				game_initialized = true;
				ui = new Ui();
				player = new Player();

				loadImages();
			}
			else if (cur_choice == 2) {
				view_controls = true;
			}
			else {
				exit(0);
			}
		}
		drawMenu();
	}
}


void Game::drawMenu() { // Draw menu
	graphics::Brush br;
	br.outline_opacity = 0.0f;

	br.texture = std::string(ASSET_PATH) + "menu.png";
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
	br.texture = "";
	br.fill_opacity = 0.5f;

	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;

	if (cur_choice == 1) {
		graphics::drawRect(CANVAS_WIDTH / 4.5f + 143, CANVAS_HEIGHT / 3.0f - 14, 210, 50, br);
	}
	else if (cur_choice == 2) {
		graphics::drawRect(CANVAS_WIDTH / 4 + 80, CANVAS_HEIGHT * 1.33 / 3 - 14, 180, 50, br);
	}
	else if (cur_choice == 3) {
		graphics::drawRect(CANVAS_WIDTH / 4 + 80, CANVAS_HEIGHT * 1.66 / 3 - 14, 180, 50, br);
	}

	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	br.fill_opacity = 1.0f;

	graphics::drawText(CANVAS_WIDTH / 4, CANVAS_HEIGHT / 3, 50, "START GAME", br);
	graphics::drawText(CANVAS_WIDTH / 4, CANVAS_HEIGHT * 1.33 / 3, 50, "CONTROLS", br);
	graphics::drawText(CANVAS_WIDTH / 4, CANVAS_HEIGHT * 1.66 / 3, 50, "QUIT GAME", br);
}


// MAIN

void Game::update() {

	if (game_initialized) {
		updateGameplay();
	}
	else if (view_controls) {
		if (graphics::getKeyState(graphics::SCANCODE_SPACE)) {
			graphics::playSound(std::string(SOUND_PATH) + "click.mp3", 0.4f, false);
			view_controls = false;
		}
	}
	else {
		updateMenu();
	}
}

void Game::draw() {

	if (game_initialized) {
		drawGameplay();
	}
	else if (view_controls) {
		graphics::Brush br;
		br.texture = std::string(ASSET_PATH) + "tutorial.png";
		graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

		graphics::drawText(50, 51, 45, "Press <SPACE> to return to the Main Menu", br);
	}
	else {
		drawMenu();
	}
}


void Game::init() {

	graphics::setFont(std::string(ASSET_PATH) + "BitPap.ttf");
	graphics::playMusic(std::string(SOUND_PATH) + "MGS_MUSIC.mp3", 0.3f, true);
}

Game::Game() {
}

Game::~Game() {
	delete player;
	delete ui;
	delete enemy;
	delete projectile;
	delete item;
}

