//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
//                                                                        //
// This program is free software: you can redistribute it and/or modify   //
// it under the terms of the GNU General Public License as published by   //
// the Free Software Foundation, either version 3 of the License, or      //
// (at your option) any later version.                                    //
//                                                                        //
// This program is distributed in the hope that it will be useful,        //
// but WITHOUT ANY WARRANTY; without even the implied warranty of         //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
// GNU General Public License for more details.                           //
//                                                                        //
// You should have received a copy of the GNU General Public License      //
// along with this program.  If not, see <http://www.gnu.org/licenses/>.  //
//========================================================================//

#include "dasherShot.hpp"

DasherShot::DasherShot(const sf::Texture & mainTxtr, const sf::Texture & glowTxtr, float x, float y, float dir) :
	Effect{x, y}
{
	spriteSheet.setTexture(mainTxtr);
	spriteSheet.setOrigin(6, 6);
	glowSprite.setTexture(glowTxtr);
	glowSprite.setOrigin(22.5, 22.5);
	int diff = pow(-1,std::abs(static_cast<int>(global::RNG())) % 2) + std::abs(static_cast<int>(global::RNG())) % 6 - 3;
	direction = (dir + diff) * (3.14 / 180);	 // I added 270 previously to get the sprite to face in the right direction, so subract it
	initialVelocity = 5.8 + (0.8 * (std::abs(static_cast<int>(global::RNG())) % 3));
	timeout = 0;
	driftSel = std::abs(static_cast<int>(global::RNG())) % 2;
}

void DasherShot::update(sf::Time & elapsedTime) {
	scale = initialVelocity * Easing::easeOut<2>(timeout, static_cast<int64_t>(830000));
	position.x += scale * (elapsedTime.asMicroseconds() * 0.00005f) * (cos(direction));
	position.y += scale * (elapsedTime.asMicroseconds() * 0.00005f) * (sin(direction));
	hitBox.setPosition(position);
	glowSprite.setPosition(position.x, position.y + 18);
	timer += elapsedTime.asMilliseconds();
	timeout += elapsedTime.asMicroseconds();
	// Alternate between frames
	if (timer > 70) {
		frameIndex ^= 0x01;
		timer -= 70;
	}
	if (driftSel) {
		direction += 0.004 * elapsedTime.asMicroseconds() * 0.00005;
	} else {
		direction -= 0.004 * elapsedTime.asMicroseconds() * 0.00005;
	}
	if (timeout > 750000) {
		setKillFlag();
	}
	spriteSheet.setPosition(position.x, position.y);
}

const sf::Sprite & DasherShot::getSprite() {
	return spriteSheet[frameIndex];
}

const sf::Sprite & DasherShot::getGlow() const {
	return glowSprite;
}

void DasherShot::speedFactor(float factor) {
	scale = factor;
}

const DasherShot::HBox & DasherShot::getHitBox() const {
	return hitBox;
}
