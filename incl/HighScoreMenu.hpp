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

#ifndef HITIT_HIGHSCOREMENU_HPP
#define HITIT_HIGHSCOREMENU_HPP

////////////////////////////////////////////////
// HitIt internal headers
#include "MenuState.hpp"
#include "HighScore.hpp"
class TextField;
////////////////////////////////////////////////

class HighScoreMenu : public MenuState
{
	public:
        /**
         * \brief Constructor
         *
         * \param stack Stack to insert state into at construction
         * \param target SFML RenderTarget object to draw to
         */
        HighScoreMenu(StateStack& stack, sf::RenderTarget& target, const std::string& midiFile, unsigned int score);

    private:
        /**
         * \brief Create GUI score list and insert into container
         */
        void createList();

        /**
         * \brief Load buttons into GUIContainer
         */
        void loadButtons();

    private:
        std::string             mMidiFile;  ///< Path to MIDI track
        HighScore               mHighScore; ///< HighScore object for fetching highscore data from file
        unsigned int            mScore;     ///< Player score
        TextField*              mTextField; ///< Text field for user input if player made a new record
};

/************************************************
 * \class HighScoreMenu
 *
 * Display highscore list for a MIDI track and
 * allow user to insert its own score accompanied
 * with a name into the highscore data file.
 *
************************************************/

#endif // HITIT_HIGHSCOREMENU_HPP
