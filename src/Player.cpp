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
#include "SFML/Window/Event.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "Player.hpp"
#include "TIME_PER_FRAME.hpp"
#include "Assets.hpp"
////////////////////////////////////////////////


Player::Player(const sf::Texture& texture, float width, int hp, sf::Vector2f position)
: RectangleNode(texture)
, mHp(hp)
, mMovementSpeed(300.f)
, mIsImmortal(false)
, mImmortalCounter(0.f)
, mDamagedSound(Assets::get(ResourceID::Sound::PlayerDamaged))
, mStepSound(Assets::get(ResourceID::Sound::PlayerStep))
, mMoveCounter(0.f)
, mStepSize(width)
{
    mStepSound.setVolume(70.f);
    setSize(width - 2.f, width);
    setPosition(position);
}

void Player::updateCurrent()
{
    if(mIsImmortal)
    {
        mImmortalCounter += TIME_PER_FRAME::seconds();
        if(mImmortalCounter >= mImmortalTime)
            mIsImmortal = false;
    }

    using namespace sf;
    if(Keyboard::isKeyPressed(Keyboard::Up))
        mDirection.y = -1.f;
    else if(Keyboard::isKeyPressed(Keyboard::Down))
        mDirection.y = 1.f;

    bool isLeftPressed = Keyboard::isKeyPressed(Keyboard::Left);
    bool isRightPressed = Keyboard::isKeyPressed(Keyboard::Right);
    if(isLeftPressed || isRightPressed)
    {
        mMoveCounter += TIME_PER_FRAME::seconds();
        if(mMoveCounter >= mMoveCooldown)
        {
            mMoveCounter = 0.f;

            if(isLeftPressed)
                mDirection.x = -1.f;
            else if(isRightPressed)
                mDirection.x = 1.f;
        }
    }

    if(mDirection.x)
        mStepSound.play();

    mPreviousPosition = getWorldPosition();
    move(mDirection.x * mStepSize, mDirection.y * mMovementSpeed * TIME_PER_FRAME::seconds());
    mDirection.x = mDirection.y = 0.f;
}


void Player::handleEventCurrent(const sf::Event& event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        switch(event.key.code)
        {
            case sf::Keyboard::Left:
                mMoveCounter = 0.f;
                mDirection.x = -1.f;
                break;
            case sf::Keyboard::Right:
                mMoveCounter = 0.f;
                mDirection.x = 1.f;
                break;
            default:
                break;
        }
    }
}

void Player::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(mIsImmortal)
    {
        // Lol at this fix, but time is running out :P
        bool doDraw = false;
        if(mImmortalCounter < 0.2f)
            doDraw = false;
        else if(mImmortalCounter < 0.3f)
            doDraw = true;
        else if(mImmortalCounter < 0.4f)
            doDraw = false;
        else if(mImmortalCounter < 0.5f)
            doDraw = true;
        else if(mImmortalCounter < 0.6)
            doDraw = false;
        else
            doDraw = true;

        if(doDraw)
            RectangleNode::drawCurrent(target, states);
    }
    else
        RectangleNode::drawCurrent(target, states);


}

bool  Player::isDestroyed() const
{
    return mHp <= 0;
}

void Player::damage()
{
    if(!mIsImmortal)
    {
        mHp -= 1;
        mIsImmortal = true;
        mImmortalCounter = 0.f;

        mDamagedSound.play();
    }
}

void Player::destroy()
{
    mHp = 0;
}

void Player::accelerate(float a)
{
    mMovementSpeed += a;
}

int Player::getHp() const
{
    return mHp;
}

bool Player::isDamaged() const
{
    return mIsImmortal;
}

sf::Vector2f Player::getPreviousPosition() const
{
    return mPreviousPosition;
}
