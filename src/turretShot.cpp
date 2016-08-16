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

#include "turretShot.hpp"

TurretShot::TurretShot(const sf::Texture & mainTxtr, const sf::Texture & glowTxtr, float x, float y, float dir) :
	Effect{x, y}
{
	spriteSheet.setTexture(mainTxtr);
	glowSprite.setTexture(glowTxtr);
	spriteSheet.setRotation(dir + 270);
	spriteSheet.setOrigin(4, 6);
	glowSprite.setOrigin(22.5, 22.5);
	direction = dir * 3.14 / 180;
	scale = 2.8;
	animationTimer = 0;
}

void TurretShot::update(sf::Time & elapsedTime) {
	position.x += scale * 1.5 * (elapsedTime.asMicroseconds() * 0.00005f) * (cos(direction));
    position.y += scale * 1.5 * (elapsedTime.asMicroseconds() * 0.00005f) * (sin(direction));
	hitBox.setPosition(position);
	spriteSheet.setPosition(position.x, position.y);
	glowSprite.setPosition(position.x, position.y + 18);
	timer += elapsedTime.asMilliseconds();
	if (timer > 600) {
	    setKillFlag();
	}
	float offset = std::abs(static_cast<int>(global::RNG())) % 20;
	glowSprite.setColor(sf::Color(230 + offset, 230 + offset, 230 + offset, 255));
	animationTimer += elapsedTime.asMilliseconds();
	if (animationTimer > 50) {
		animationTimer -= 50;
		frameIndex ^= 0x01; // Toggle between the two frames
	}
}

const TurretShot::HBox & TurretShot::getHitBox() const {
	return hitBox;
}

const sf::Sprite & TurretShot::getSprite() {
	return spriteSheet[frameIndex];
}

const sf::Sprite & TurretShot::getGlow() {
	return glowSprite;
}

void TurretShot::speedFactor(float factor) {
	scale = factor;
}
