//
//  FontController.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/21/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//
//  This class is responsible for creating text and shapes and drawing them to the screen.
//  The userInterface class has similar functionality, but it is more concerned with images
//  and post-processing effects.
//

#pragma once
#ifndef fontController_hpp
#define fontController_hpp

#include "SFML/Graphics.hpp"
#include "resourceHandler.hpp"

class FontController {
private:
	sf::Texture texture;
	sf::View fontView;
	sf::Text waypointText, titleText, deathText, scoreText, healthNumText;
	sf::Text resumeText, settingsText, quitText;
	char maxHealth;
	int score;
	float windowCenterX, windowCenterY;
	sf::Clock wpTextDisplayTimer, healthDisplayTimer, scoreDisplayTimer;
	sf::ConvexShape heart;
	sf::CircleShape coin;
	
public:
	enum class Text {
		resumeText, settingsText, quitText, healthNumText, scoreText, waypointText, heart, coin
	};
	FontController(sf::View, float, float);
	void update(sf::RenderWindow &, float, float);
	void setWaypointText(int);
	void setZoneText(char);
	void print(sf::RenderWindow &);
	void setTextAlpha(uint8_t, Text);
	void setTextOffset(float, float, Text);
	void updateHealth(char);
	void updateMaxHealth(char, char);
	void drawTitle(unsigned char, sf::RenderWindow&);
	void drawDeathText(unsigned char, sf::RenderWindow&);
	char getMaxHealth() const;
	sf::Text * getTitle();
	sf::Text * getDeathText();
	void reset();
	void resetWPText();
	void resetHPText();
	void resetSCText();
	void updateScore(int);
	int getScore();
};
#endif /* FontController_hpp */
