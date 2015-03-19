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

#ifndef HITIT_BUTTON_HPP
#define HITIT_BUTTON_HPP

////////////////////////////////////////////////
// HitIt internal headers
#include "GUIElement.hpp"
#include "SoundPlayer.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Graphics/Text.hpp"
////////////////////////////////////////////////

class Button : public GUIElement
{
    public:
        typedef std::function<void()> Callback;

        /**
        * \brief Constructor
        *
        * \param text Text to display
        * \param soundBuffer SFML SoundBuffer object that holds the sound to be played
        * when deselected
        * \param callback Function to execute when activated
        */
        Button(const sf::Text& text, const sf::SoundBuffer& soundBuffer, Callback callback);

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
		 * \brief Get bounding rectangle of node
		 *
		 * \return bounding rectangle of node
		 */
        virtual sf::FloatRect getBoundingRect() const;

    private:
        /**
         * \brief Draw this node.
         *
         * \param target SFML RenderTarget object to draw this node to
         * \param states SFML RenderStates object to transform draw with
         */
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

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


    private:
        sf::Text	    mText;          ///< Text to display
        SoundPlayer     mSoundPlayer;   ///< Sound to play when deselected and activated
        Callback	    mCallback;      ///< Function to execute when activated
};

/************************************************
 * \class Button
 *
 * Selectable and activatable GUI element
 * that performs a callback when activated.
 *
************************************************/

#endif // HITIT_BUTTON_HPP
