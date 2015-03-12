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
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "VertexArrayNode.hpp"
////////////////////////////////////////////////


VertexArrayNode::VertexArrayNode(sf::VertexArray array, int category)
: SceneNode(category)
, mArray(array)
{
}

////////////////////////////////////////////////

void VertexArrayNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mArray, states);
}

////////////////////////////////////////////////

sf::Vector2f VertexArrayNode::getWorldPosition() const
{
    return getWorldTransform().transformPoint(mArray.getBounds().left, mArray.getBounds().top);
}

sf::FloatRect VertexArrayNode::getBoundingRect() const
{
    return getWorldTransform().transformRect(mArray.getBounds());
}
