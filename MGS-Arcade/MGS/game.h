#pragma once
#include "enemy.h"
#include "player.h"
#include "ui.h"
#include "projectile.h"
#include "gameMechs.h"

class Game : public GameMechs {
	int cur_choice = 1;
	float menuCD = 0.0f;

	bool paused = false;
	float pauseCD = 0.0f;
	bool over = false;
	bool won = false;
	bool game_initialized = false;
	bool view_controls = false;

	Ui* ui = nullptr;

	Player* player = nullptr;
	float punchCD = 0.0f;

	float countdown=0.0f;

	bool naked = true;
	bool old = true;
	bool old_dead = false;

	Enemy* enemy = nullptr;
	std::vector<Enemy*> enemies;

	Projectile* projectile = nullptr;
	std::vector<Projectile*> projectiles;

	Item* item = nullptr;
	std::vector<Item*> items;

	float use_time = 0;

	int collision = 0;

	std::string nickname;

public:

	void spawnItems(float x, float y);
	void updateItems();
	void drawItems();
	void resetEffects();

	void useItem();
	bool checkFire(Enemy* enemy);
	void drawProjectiles();
	void updateProjectiles();

	int checkCollisionHelp(Disk disk, Character* ch);
	void checkCollision();

	void spawnEnemies();
	void drawEnemies();
	void updateEnemies();

	void resetAssets();

	void drawGameplay();
	void updateGameplay();

	void drawMenu();
	void updateMenu();

	void draw();
	void update();
	void init();

	Game();
	~Game();
};
