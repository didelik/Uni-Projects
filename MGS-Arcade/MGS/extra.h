#pragma once
#include "config.h"

void printText(std::string str, float posx, float posy, int size) {
	graphics::Brush brScore;
	brScore.outline_opacity = 0.0f;

	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '0') {
			brScore.texture = std::string(TEXT_PATH) + "0.png";
		}
		else if (str[i] == '1') {
			brScore.texture = std::string(TEXT_PATH) + "1.png";
		}
		else if (str[i] == '2') {
			brScore.texture = std::string(TEXT_PATH) + "2.png";
		}
		else if (str[i] == '3') {
			brScore.texture = std::string(TEXT_PATH) + "3.png";
		}
		else if (str[i] == '4') {
			brScore.texture = std::string(TEXT_PATH) + "4.png";
		}
		else if (str[i] == '5') {
			brScore.texture = std::string(TEXT_PATH) + "5.png";
		}
		else if (str[i] == '6') {
			brScore.texture = std::string(TEXT_PATH) + "6.png";
		}
		else if (str[i] == '7') {
			brScore.texture = std::string(TEXT_PATH) + "7.png";
		}
		else if (str[i] == '8') {
			brScore.texture = std::string(TEXT_PATH) + "8.png";
		}
		else if (str[i] == '9') {
			brScore.texture = std::string(TEXT_PATH) + "9.png";
		}
		graphics::drawRect(posx, posy, size, size, brScore);
		posx += 50;
	}

}
