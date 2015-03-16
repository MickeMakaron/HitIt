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
#include "SFML/Graphics/RectangleShape.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "State.hpp"
#include "AssetList.hpp"
#include "GUIContainer.hpp"
#include "SoundPlayer.hpp"
////////////////////////////////////////////////

class MenuState : public State
{
	public:
        /**
         * \brief Constructor
         *
         * \param stack to insert state into at construction.
         * \param target SFML RenderTarget object to draw to.
         */
        MenuState(StateStack& stack, sf::RenderTarget& target, std::list<GUIElement*> elements = std::list<GUIElement*>(0));

        /**
         * \brief Draw state
         */
		virtual void draw();

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

        /**
         * \brief Set background texture.
         *
         * \param texture background texture.
         */
        void setBackground(const sf::Texture& texture);

        /**
         * \brief Set background color.
         *
         * \param color background color.
         */
        void setBackground(sf::Color color);


    private:
        std::list<TextureList::Asset>   getTextures() const;
        std::list<SoundList::Asset>     getSounds() const;

    protected:
        sf::RenderTarget&   mTarget;
        TextureList         mTextures;
        SoundList           mSounds;
        SoundPlayer         mSoundPlayer;
        GUIContainer        mMenu;
        sf::RectangleShape  mBackground;
};

/************************************************
 * \class MenuState
 *
 * Program state for managing the menus.
 *
************************************************/

#endif // HITIT_MENUSTATE_HPP
