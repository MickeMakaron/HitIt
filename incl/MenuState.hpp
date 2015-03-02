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

#ifndef HITIT_MENUSTATE_HPP
#define HITIT_MENUSTATE_HPP

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Graphics/Sprite.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "State.hpp"
////////////////////////////////////////////////

class MenuState : public State
{
	public:
        /**
         * \brief Constructor
         *
         * \param stack to insert state into at construction.
         */
        MenuState(StateStack& stack);

        /**
         * \brief Destructor.
         */
        ~MenuState();

        /**
         * \brief Draw state
         *
         * \param window window to draw to.
         */
		virtual void draw(sf::RenderWindow& window);

        /**
         * \brief Update state
         *
         * \return indicate whether the state stack
         * should continue updating further states
         * (true) or not (false).
         */
		virtual bool update();

        /**
         * \brief Handle input events.
         *
         * \return indicate whether the state stack
         * should allow further states to handle events
         * (true) or not (false).
         */
		virtual bool handleEvent(const sf::Event& event);

    private:
        sf::Sprite mBackground;
};

/************************************************
 * \class MenuState
 *
 * Program state for managing the menus.
 *
************************************************/

#endif // HITIT_MENUSTATE_HPP
