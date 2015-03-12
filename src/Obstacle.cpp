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
#include "SFML/Graphics/VertexArray.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "Obstacle.hpp"
#include "TIME_PER_FRAME.hpp"
////////////////////////////////////////////////


Obstacle::Obstacle(SoundPlayer& buffer, float speed, float playLine, sf::Vector2f size, float deathLine, unsigned int iVertexArray, sf::VertexArray& array, int category)
: SceneNode(category)
, mShape(size)
, mSoundPlayer(buffer)
, mSpeed(speed)
, mPlayLine(playLine)
, mDeathLine(deathLine)
, mState(Waiting)
, mIVertexArray(iVertexArray)
, mArray(array)
{
}


bool Obstacle::isMarkedForRemoval() const
{
    return mState == Dead;
}

void Obstacle::updateCurrent()
{
    switch(mState)
    {
        case Waiting:
            if(getWorldPosition().y + getBoundingRect().height >= mPlayLine)
            {
                mState = Playing;
                mSoundPlayer.play();
                mArray[mIVertexArray + 2].color = mArray[mIVertexArray + 3].color = sf::Color(150, 150, 150);
            }
            else
                break;
        case Playing:
            if(getWorldPosition().y >= mPlayLine)
            {
                mState = Silent;
                mSoundPlayer.stop();
                mArray[mIVertexArray + 2].color = mArray[mIVertexArray + 3].color = sf::Color::Black;
            }
            else
                break;
        case Silent:
            if(getWorldPosition().y >= mDeathLine)
                mState = Dead;
            else
                break;
        default:
            break;
    }

/*
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
*/

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
