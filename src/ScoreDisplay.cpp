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
#include "ScoreDisplay.hpp"
#include "TIME_PER_FRAME.hpp"
#include "BonusStrip.hpp"
#include "Assets.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// STD - C++ Standard Library
#include <sstream>
////////////////////////////////////////////////

ScoreDisplay::ScoreDisplay(sf::Text text, const SceneNode& player, BonusStrip& bonusStrip)
: Text(text)
, mPlayer(player)
, mBonusStrip(bonusStrip)
, mScore(0.f)
, mTimeInRedZone(0.f)
, mState(Outside)
, mBonus1(Assets::get(ResourceID::Sound::ID::Bonus1))
, mBonus2(Assets::get(ResourceID::Sound::ID::Bonus2))
{
    std::stringstream ss;
    ss << "$" << (int)mScore;

    setText(ss.str());

}

////////////////////////////////////////////////

void ScoreDisplay::updateCurrent()
{
    const sf::FloatRect PLAYER_RECT = mPlayer.getBoundingRect();
    float distanceToIndicator = mBonusStrip.getDistance(sf::Vector2f(PLAYER_RECT.left + PLAYER_RECT.width / 2.f, PLAYER_RECT.top + PLAYER_RECT.height / 2.f));
    bool isInRedZone = distanceToIndicator < mBonusStrip.getWidth() / 2.f;

    if(!isInRedZone)
    {
        mState = Outside;
        mTimeInRedZone = 0.f;
    }
    else
    {

        mTimeInRedZone += TIME_PER_FRAME::seconds();
    }



    std::string bonus;
    float modifier = 0.f;
    switch(mState)
    {
        case Outside:
            if(isInRedZone)
                mState = Red;
            else
                modifier = 100.f / distanceToIndicator;
            break;
        case Red:
            modifier += 6.f;
            if(mTimeInRedZone >= 20.f)
            {
                mState = Bonus1;
                mBonus1.play();
            }

            bonus = "\nBonus x5!";
            break;
        case Bonus1:
            modifier += 12.f;
            if(mTimeInRedZone >= 40.f)
            {
                mState = Bonus2;
                mBonus2.play();
            }
            bonus = "\nBonus x10!";
            break;
        case Bonus2:
            modifier += 24.f;
            bonus = "\nBonus x20!";
            break;
        default:
            break;
    }

    mScore += modifier * (TIME_PER_FRAME::seconds() + mBonusStrip.fetchPointsScore());


    std::stringstream ss;
    ss << "$" << (int)mScore << bonus;
    setText(ss.str());
}

////////////////////////////////////////////////

unsigned int ScoreDisplay::getScore() const
{
    return mScore;
}
