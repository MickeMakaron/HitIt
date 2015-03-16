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

#ifndef HITIT_SCOREDISPLAY_HPP
#define HITIT_SCOREDISPLAY_HPP

////////////////////////////////////////////////
// STD - C++ Standard Library
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Audio/Sound.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "Text.hpp"
class BonusStrip;
////////////////////////////////////////////////

class ScoreDisplay : public Text
{
    public:
        /**
         * \brief Constructor
         *
         */
        ScoreDisplay(sf::Text text, const SceneNode& player, BonusStrip& bonusStrip);

        /**
         * \brief Update score.
         */
        virtual void updateCurrent();

        unsigned int getScore() const;

    private:
        enum State
        {
            Outside,
            Red,
            Bonus1,
            Bonus2,
        };

        const SceneNode&    mPlayer;
        BonusStrip&         mBonusStrip;
        float               mScore;
        float               mTimeInRedZone;
        State               mState;
        sf::Sound           mBonus1;
        sf::Sound           mBonus2;
};


/************************************************
 * \class ScoreDisplay
 *
 * For displaying the current score in-game.
 *
************************************************/


#endif // HITIT_SCOREDISPLAY_HPP
