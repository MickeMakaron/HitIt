/****************************************************************
****************************************************************
*
* HitIt - Top-down 2D game where the goal is NOT to hit the music.
* Copyright (C) 2015 Mikael Hernvall (mikael.hernvall@gmail.com)
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
****************************************************************
****************************************************************/

////////////////////////////////////////////////
// HitIt internal headers
#include "HealthBar.hpp"
#include "Player.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Graphics/Texture.hpp"
////////////////////////////////////////////////

HealthBar::HealthBar(const sf::Texture& texture, const Player& player)
: RectangleNode(texture)
, mPlayer(player)
, mNumHitPoints(player.getHp())
{
    updateShape();
}

////////////////////////////////////////////////

void HealthBar::offsetHp(int hp)
{
    mNumHitPoints += hp;
    if(mNumHitPoints < 0)
        mNumHitPoints = 0;

    updateShape();
}

////////////////////////////////////////////////

void HealthBar::updateShape()
{
    sf::Vector2u texSize = mShape.getTexture()->getSize();
    sf::Vector2f size(texSize.x * mNumHitPoints, texSize.y);
    mShape.setSize(size);
    mShape.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
}

////////////////////////////////////////////////

void HealthBar::updateCurrent()
{
    if(mPlayer.getHp() != mNumHitPoints)
        offsetHp(mPlayer.getHp() - mNumHitPoints);
}
