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
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "Obstacle.hpp"
#include "TIME_PER_FRAME.hpp"
////////////////////////////////////////////////


Obstacle::Obstacle(SoundPlayer& buffer, float speed, float playDuration, float width, float lifeTime, unsigned int iVertexArray, int category)
: SceneNode(category)
, mShape(sf::Vector2f(width, speed * playDuration))
, mSoundPlayer(buffer)
, mSpeed(speed)
, mPlayDuration(playDuration)
, mLifeTime(lifeTime)
, mTime(0.f)
, mIsPaused(false)
, mIVertexArray(iVertexArray)
{
    //mSoundPlayer.setVolume(0.f);
    //mSoundPlayer.fade(100.f, 0.1f);

    mSoundPlayer.play();

    mShape.setFillColor(sf::Color::Black);
}

Obstacle::~Obstacle()
{
}

bool Obstacle::isMarkedForRemoval() const
{
    return mLifeTime <= mTime;
}

void Obstacle::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    //target.draw(mShape, states);
}

void Obstacle::updateCurrent()
{
    if(mSoundPlayer.getStatus() == sf::Sound::Status::Playing)
    {
        mShape.setFillColor(sf::Color::Blue);
    }
    else
        mShape.setFillColor(sf::Color::Black);

    sf::Vector2f pos = 	getWorldTransform() * sf::Vector2f(mShape.getPosition());

    mTime += TIME_PER_FRAME::seconds();


    if(!mIsPaused)//mSoundPlayer.getStatus() == sf::Sound::Status::Playing)
    {
        if(mPlayDuration <= mTime)
        {
            mSoundPlayer.SoundPlayer::stop();
            mIsPaused = true;
        }
        else
        {
            float timeLeft = mPlayDuration - mTime;
            //if(timeLeft < 0.2f)
               //mSoundPlayer.fade(0.f, timeLeft);
        }
    }


    move(0.f, mSpeed * TIME_PER_FRAME::seconds());
}

sf::FloatRect Obstacle::getBoundingRect() const
{
    return getWorldTransform().transformRect(mShape.getGlobalBounds());
}

unsigned int Obstacle::getVertexArrayIndex() const
{
    return mIVertexArray;
}
