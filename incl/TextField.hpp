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

#ifndef HITIT_TEXTFIELD_HPP
#define HITIT_TEXTFIELD_HPP

////////////////////////////////////////////////
// HitIt internal headers
#include "GUIElement.hpp"
#include "SoundPlayer.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// STD - C++ Standard Library
#include <limits>
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
////////////////////////////////////////////////

class TextField : public GUIElement
{
    public:
        /**
         * \brief Constructor
         *
         * \param text SFML Text object to display
         * \param soundBuffer SFML SoundBuffer object that contains selection sound
         * \param maxLength Maximum length of string in text field
         */
        TextField(sf::Text text, const sf::SoundBuffer& soundBuffer, unsigned int maxLength = std::numeric_limits<unsigned int>::max());

		/**
		 * \brief Get bounding rectangle of node
		 *
		 * \return bounding rectangle of node
		 */
        virtual sf::FloatRect getBoundingRect() const;

        /**
         * \brief Indicate whether element can be activated or not
         *
         * \return True if activatable, else false
         */
        virtual bool isActivatable() const;

        /**
         * \brief Indicate whether element is selectable or not
         *
         * \return True if selectable, else false
         */
        virtual bool isSelectable() const;

        /**
         * \brief Get current string
         *
         * \return Current string of text field
         */
        std::string getString() const;

    private:
        /**
         * \brief Draw this node.
         *
         * \param target SFML RenderTarget object to draw this node to
         * \param states SFML RenderStates object to transform draw with
         */
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

		/**
		 * \brief Handle device input for this node
		 *
		 * \param event event to handle
		 */
        virtual void handleEventCurrent(const sf::Event& event);

        /**
         * \brief Select element
         */
        virtual void select();

        /**
         * \brief Deselect element
         */
        virtual void deselect();

        /**
         * \brief Activate element
         */
        virtual void activate();

        /**
         * \brief Deactivate element
         */
        virtual void deactivate();

        /**
         * \brief Erase character at end
         */
        void erase();

        /**
         * \brief Insert character at end
         *
         * \param character Character to insert
         */
        void insert(char character);

    private:
       sf::Text             mText;              ///< SFML Text object to display
       SoundPlayer          mSoundPlayer;       ///< Sound to play when selected or activated
       sf::RectangleShape   mInsertionCursor;   ///< Insertion cursor to display at end of text field when active
       unsigned int         mMaxLength;         ///< Max length of string in text field
};

/************************************************
 * \class StateStack
 *
 * Text field element in GUIs for capturing and
 * displaying user text input.
 *
************************************************/

#endif // HITIT_TEXTFIELD_HPP
