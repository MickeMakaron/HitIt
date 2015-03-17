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

#ifndef HITIT_GUICONTAINER_HPP
#define HITIT_GUICONTAINER_HPP

////////////////////////////////////////////////
// STD - C++ Standard Library

////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
namespace sf
{
    class RenderTarget;
}
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "GUIElement.hpp"
////////////////////////////////////////////////

class GUIContainer : public sf::Transformable, public sf::Drawable
{
    public:
        typedef std::unique_ptr<GUIElement> ElementPtr;

        /**
         * \brief Constructor
         *
         * \param elements GUI elements to assign to container
         */
        GUIContainer(std::list<GUIElement*> elements);

        /**
         * \brief Update container elements.
         */
        void update();

        /**
         * \brief Draw container to target.
         *
         * \param target SFML RenderTarget object to draw to.
         * \param target SFML RenderStates object to draw with.
         */
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        /**
         * \brief Handle input events.
         *
         * \param event event to handle
         */
        void handleEvent(const sf::Event& event);

        /**
         * \brief Insert element into container.
         *
         * \param element element to insert.
         */
        void insert(GUIElement* element);

        /**
         * \brief Insert GUI elements.
         *
         * \param elements GUI elements.
         */
        void insert(std::list<GUIElement*> elements);

        virtual sf::FloatRect getGlobalBounds() const;


        void setBackground(sf::Color fillColor, sf::Color outlineColor = sf::Color::White, float outlineThickness = 0.f);

    private:
        /**
         * \brief Update size by checking bounds of elements.
         */
         void updateSize();

    private:
        /**
         * \brief Select next element in array.
         */
        void selectNext();

        /**
         * \brief Select previous element in array.
         */
        void selectPrevious();

        void activate();

    private:
        std::list<ElementPtr>           mElements;  ///< GUI elements.
        std::list<ElementPtr>::iterator mSelection; ///< Current selection.
        sf::FloatRect                   mBounds;    ///< Bounding rectangle of all elements.
        sf::RectangleShape              mBackground;
};

/************************************************
 * \class GUIContainer
 *
 * GUI element container.
 *
************************************************/

#endif // HITIT_GUICONTAINER_HPP
