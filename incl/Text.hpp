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

#ifndef HITIT_TEXT_HPP
#define HITIT_TEXT_HPP

////////////////////////////////////////////////
// HitIt internal headers
#include "GUIElement.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Graphics/Text.hpp"
////////////////////////////////////////////////

class Text : public GUIElement
{
    public:
        /**
         * \brief Constructor
         *
         * \param text SFML text object to display
         */
        Text(sf::Text text);

		/**
		 * \brief Get bounding rectangle of node
		 *
		 * \return bounding rectangle of node
		 */
        virtual sf::FloatRect getBoundingRect() const;

        /**
         * \brief Set string to display
         *
         * \param text String to display
         */
        void setText(std::string text);

    private:
        /**
         * \brief Draw this node.
         *
         * \param target SFML RenderTarget object to draw this node to.
         * \param states SFML RenderStates object to transform draw with
         */
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::Text	    mText;
};

/************************************************
 * \class Text
 *
 * Simple text element in GUIs.
 *
************************************************/

#endif // HITIT_TEXT_HPP
