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
#include "SFML/Window/Keyboard.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "Player.hpp"
#include "TIME_PER_FRAME.hpp"
////////////////////////////////////////////////


Player::Player(const sf::Texture& texture, int hp, sf::Vector2f position)
: SpriteNode(texture)
, mHp(hp)
, mMovementSpeed(200.f)
, mDiagonalMovementSpeed(sqrtf(0.5f * mMovementSpeed * 0.5f * mMovementSpeed * 2))
{
    setPosition(position);
}

void Player::updateCurrent()
{
    using namespace sf;

    Vector2f direction(0.f, 0.f);
    if(Keyboard::isKeyPressed(Keyboard::Left))
        direction.x = -1.f;
    else if(Keyboard::isKeyPressed(Keyboard::Right))
        direction.x = 1.f;

    if(Keyboard::isKeyPressed(Keyboard::Up))
        direction.y = -1.f;
    else if(Keyboard::isKeyPressed(Keyboard::Down))
        direction.y = 1.f;

    float velocity = direction.x && direction.y ? mDiagonalMovementSpeed : mMovementSpeed;
    move(direction * velocity * TIME_PER_FRAME::seconds());
}

void Player::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    SpriteNode::drawCurrent(target, states);
    drawBoundingRect(target, states);
}

bool  Player::isDestroyed() const
{
    return mHp <= 0;
}

void Player::damage()
{
    mHp -= 1;
}

void Player::destroy()
{
    mHp = 0;
}

void Player::accelerate(float a)
{
    mMovementSpeed += a;
}
