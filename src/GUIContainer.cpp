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
// SFML - Simple and Fast Media Library
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Window/Event.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "GUIContainer.hpp"
////////////////////////////////////////////////


GUIContainer::GUIContainer(std::list<GUIElement*> elements)
{
    for(GUIElement* element : elements)
        insert(element);

    mSelection = mElements.begin();
    (*mSelection)->select();
}

////////////////////////////////////////////////

void GUIContainer::update()
{
    for(ElementPtr& element : mElements)
        element->update();
}

////////////////////////////////////////////////

void GUIContainer::draw(sf::RenderTarget& target) const
{
    for(const ElementPtr& element : mElements)
        target.draw(*element);
}

////////////////////////////////////////////////

void GUIContainer::handleEvent(const sf::Event& event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        switch(event.key.code)
        {
            case sf::Keyboard::Return:
                if(!mElements.empty())
                    (*mSelection)->activate();
                break;

            case sf::Keyboard::Down:
                selectNext();
                break;

            case sf::Keyboard::Up:
                selectPrevious();
                break;

            default:
                break;
        }


    }

    for(ElementPtr& element : mElements)
        element->handleEvent(event);
}

////////////////////////////////////////////////

void GUIContainer::selectNext()
{
    (*mSelection)->deselect();

    mSelection++;
    if(mSelection == mElements.end())
        mSelection = mElements.begin();

    (*mSelection)->select();
}

////////////////////////////////////////////////

void GUIContainer::selectPrevious()
{
    (*mSelection)->deselect();

    if(mSelection == mElements.begin())
    {
        mSelection = mElements.end();
        mSelection--;
    }
    else
        mSelection--;

    (*mSelection)->select();
}

////////////////////////////////////////////////

void GUIContainer::insert(GUIElement* element)
{
    mElements.push_back(ElementPtr(element));
}
