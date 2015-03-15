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
// STD - C++ Standard Library
#include <sstream>
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "ScoreDisplay.hpp"
#include "TIME_PER_FRAME.hpp"
#include "BonusStrip.hpp"
////////////////////////////////////////////////


ScoreDisplay::ScoreDisplay(sf::Text text, const SceneNode& player, BonusStrip& bonusStrip)
: Text(text)
, mPlayer(player)
, mBonusStrip(bonusStrip)
, mScore(0.f)
, mTimeInRedZone(0.f)
, mState(Outside)
{
    std::stringstream ss;
    ss << "$" << (int)mScore;

    setText(ss.str());

}

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
        mTimeInRedZone += TIME_PER_FRAME::seconds();


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
            if(mTimeInRedZone >= 5.f)
                mState = Red5Sec;
            bonus = "\nBonus x5!";
            break;
        case Red5Sec:
            modifier += 12.f;
            if(mTimeInRedZone >= 10.f)
                mState = Red10Sec;
            bonus = "\nBonus x10!";
            break;
        case Red10Sec:
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
