#pragma once
#include <iostream>
#include <fstream>
#include "config.h"
#include <regex>

class GameMechs {

	float bg_x = CANVAS_WIDTH / 2;
	float mbg_x = CANVAS_WIDTH / 2;
	float sbg_x = CANVAS_WIDTH / 2;
	std::vector<std::string> attempts;
	std::vector<int> scores;

public:
	void loadImages();
	void drawPause();
	void drawOver();
	void drawWon();
	void drawBackround();
	void updateBackround();
};

