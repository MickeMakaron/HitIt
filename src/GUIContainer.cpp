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
// C++ Standard Library
#include <cassert>
#include <limits>
////////////////////////////////////////////////

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
: mSelection(mElements.end())
{
    mBackground.setFillColor(sf::Color::Transparent);

    insert(elements);
}

////////////////////////////////////////////////

void GUIContainer::update()
{
    for(ElementPtr& element : mElements)
        element->update();
}

////////////////////////////////////////////////

void GUIContainer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(mBackground, states);
    for(const ElementPtr& element : mElements)
        target.draw(*element, states);
}

////////////////////////////////////////////////

void GUIContainer::handleEvent(const sf::Event& event)
{
    if(!mElements.empty() && !(*mSelection)->isActive())
    {
        if(event.type == sf::Event::KeyPressed)
        {
            if(!mElements.empty())
                switch(event.key.code)
                {
                    case sf::Keyboard::Return:
                        activate();
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
    }
    else
        (*mSelection)->handleEvent(event);
}

void GUIContainer::activate()
{
    if(!mElements.empty() && (*mSelection)->isActivatable())
        (*mSelection)->toggleActivation();
}

////////////////////////////////////////////////

void GUIContainer::selectNext()
{
    if(!mElements.empty())
    {
        if(mSelection != mElements.end())
            (*mSelection)->toggleSelection();

        int iteration = 1;
        do
        {
            mSelection++;
            if(mSelection == mElements.end())
                mSelection = mElements.begin();

            iteration++;
        } while(!(*mSelection)->isSelectable() && iteration < mElements.size());

        (*mSelection)->toggleSelection();
    }
}



////////////////////////////////////////////////

void GUIContainer::selectPrevious()
{
    if(!mElements.empty())
    {
        if(mSelection != mElements.end())
            (*mSelection)->toggleSelection();

        int iteration = 1;
        do
        {
            if(mSelection == mElements.begin())
            {
                mSelection = mElements.end();
                mSelection--;
            }
            else
                mSelection--;

            iteration++;
        } while(!(*mSelection)->isSelectable() && iteration < mElements.size());


        (*mSelection)->toggleSelection();
    }
}

////////////////////////////////////////////////

void GUIContainer::insert(GUIElement* element)
{
    mElements.push_back(ElementPtr(element));

    if(mSelection != mElements.end())
        (*mSelection)->toggleSelection();

    mSelection = mElements.end();
    selectNext();
    updateSize();
}

////////////////////////////////////////////////

void GUIContainer::insert(std::list<GUIElement*> elements)
{
    if(!elements.empty())
    {
        for(GUIElement* element : elements)
            mElements.push_back(ElementPtr(element));

        if(mSelection != mElements.end())
            (*mSelection)->toggleSelection();

        mSelection = mElements.end();
        selectNext();
        updateSize();
    }

}

void GUIContainer::updateSize()
{
    sf::Vector2f min(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
    sf::Vector2f max(std::numeric_limits<float>::min(), std::numeric_limits<float>::min());

    for(ElementPtr& element : mElements)
    {
        sf::FloatRect bounds = element->getBoundingRect();


        min.x = std::min(min.x, bounds.left);
        min.y = std::min(min.y, bounds.top);

        max.x = std::max(max.x, bounds.left + bounds.width);
        max.y = std::max(max.y, bounds.top + bounds.height);
    }

    sf::Vector2f pos = min;
    sf::Vector2f size = max - min;
    mBounds = sf::FloatRect(pos, size);
    setOrigin(size / 2.f);
    mBackground.setSize(size * 1.1f);
    mBackground.setPosition(pos - size * 0.05f);
}


sf::FloatRect GUIContainer::getGlobalBounds() const
{
    return getTransform().transformRect(mBounds);
}


void GUIContainer::setBackground(sf::Color fillColor, sf::Color outlineColor, float outlineThickness)
{
    mBackground.setFillColor(fillColor);
    mBackground.setOutlineColor(outlineColor);
    mBackground.setOutlineThickness(outlineThickness);
}
