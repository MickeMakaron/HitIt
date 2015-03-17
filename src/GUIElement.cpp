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
// HitIt internal headers
#include "GUIElement.hpp"
////////////////////////////////////////////////

GUIElement::GUIElement()
: SceneNode()
, mIsSelected(false)
, mIsActive(false)
{

}

////////////////////////////////////////////////

GUIElement::~GUIElement()
{
}

////////////////////////////////////////////////

bool GUIElement::isSelectable() const
{
    // False by default.
    return false;
}

bool GUIElement::isSelected() const
{
    return mIsSelected;
}

////////////////////////////////////////////////

void GUIElement::select()
{
    mIsSelected = true;
}

////////////////////////////////////////////////

void GUIElement::deselect()
{
    mIsSelected = false;
}

////////////////////////////////////////////////

void GUIElement::toggleSelection()
{
    if(mIsSelected)
        deselect();
    else
        select();

    mIsSelected = !mIsSelected;
}

////////////////////////////////////////////////

void GUIElement::update()
{
    // Do nothing by default.
}

////////////////////////////////////////////////

void GUIElement::handleEvent(const sf::Event& event)
{
    // Do nothing by default.
}

////////////////////////////////////////////////

void GUIElement::activate()
{
    // Nothing by default.
}

////////////////////////////////////////////////

void GUIElement::deactivate()
{
    // Nothing by default.
}

////////////////////////////////////////////////

bool GUIElement::isActivatable() const
{
    // False by default.
    return false;
}

////////////////////////////////////////////////

bool GUIElement::isActive() const
{
    return mIsActive;
}

////////////////////////////////////////////////

void GUIElement::toggleActivation()
{
    if(mIsActive)
        deactivate();
    else
        activate();

    mIsActive = !mIsActive;
}
