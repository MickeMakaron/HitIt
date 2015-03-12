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
#include <list>
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Graphics/RectangleShape.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "Text.hpp"
////////////////////////////////////////////////

class ScoreDisplay : public Text
{
    public:
        /**
         * \brief Constructor
         *
         */
        ScoreDisplay(sf::Text text, const SceneNode& player, const SceneNode& busiestPositionIndicator);

        /**
         * \brief Update score.
         */
        virtual void updateCurrent();

    private:
        enum State
        {
            Outside,
            Red,
            Red5Sec,
            Red10Sec,
        };

        const SceneNode&    mPlayer;
        const SceneNode&    mBusiestPositionIndicator;
        float               mScore;
        float               mTimeInRedZone;
        State               mState;
};


/************************************************
 * \class ScoreDisplay
 *
 * For displaying the current score in-game.
 *
************************************************/


#endif // HITIT_SCOREDISPLAY_HPP
