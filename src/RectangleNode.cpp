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
#include "RectangleNode.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Graphics/RenderTarget.hpp"
////////////////////////////////////////////////

RectangleNode::RectangleNode(const sf::Vector2f& size, int category)
: SceneNode(category)
, mShape(size)
{
}

////////////////////////////////////////////////

RectangleNode::RectangleNode(const sf::Texture& texture, int category)
: SceneNode(category)
{
    mShape.setTexture(&texture, true);
}

////////////////////////////////////////////////

void RectangleNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mShape, states);
}

////////////////////////////////////////////////

sf::FloatRect RectangleNode::getBoundingRect() const
{
    return getWorldTransform().transformRect(mShape.getGlobalBounds());
}

////////////////////////////////////////////////

void RectangleNode::setSize(float x, float y)
{
    mShape.setSize(sf::Vector2f(x, y));
}

////////////////////////////////////////////////

void RectangleNode::setFillColor(sf::Color color)
{
    mShape.setFillColor(color);
}

////////////////////////////////////////////////

void RectangleNode::setOutlineColor(sf::Color color)
{
    mShape.setOutlineColor(color);
}

////////////////////////////////////////////////

void RectangleNode::setOutlineThickness(float thickness)
{
    mShape.setOutlineThickness(thickness);
}
