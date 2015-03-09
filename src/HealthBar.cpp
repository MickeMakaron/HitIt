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
// SFML - Simple and Fast Media Library
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Texture.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "HealthBar.hpp"
#include "Player.hpp"
////////////////////////////////////////////////


HealthBar::HealthBar(const sf::Texture& texture, const Player& player)
: mPlayer(player)
, mNumHitPoints(player.getHp())
{
    mHitPoints.setTexture(&texture);

    mHitPoints.setSize(sf::Vector2f(0.f, mHitPoints.getTexture()->getSize().y));

    updateShape();
}


void HealthBar::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mHitPoints, states);
}

void HealthBar::offsetHp(int hp)
{
    mNumHitPoints += hp;
    if(mNumHitPoints < 0)
        mNumHitPoints = 0;

    updateShape();
}

void HealthBar::updateShape()
{
    sf::Vector2u texSize = mHitPoints.getTexture()->getSize();
    sf::Vector2f size(texSize.x * mNumHitPoints, texSize.y);
    mHitPoints.setSize(size);
    mHitPoints.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
}

void HealthBar::updateCurrent()
{
    if(mPlayer.getHp() != mNumHitPoints)
        offsetHp(mPlayer.getHp() - mNumHitPoints);
}


sf::FloatRect HealthBar::getBoundingRect() const
{
    return getWorldTransform().transformRect(mHitPoints.getLocalBounds());
}
