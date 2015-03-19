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
#include "VertexArrayNode.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// STD - C++ Standard Library
#include <cassert>
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Graphics/RenderTarget.hpp"
////////////////////////////////////////////////

VertexArrayNode::VertexArrayNode(sf::VertexArray array, int category)
: SceneNode(category)
, mArray(array)
{
    updatePrimitiveSize();
}

////////////////////////////////////////////////

VertexArrayNode::VertexArrayNode(sf::PrimitiveType type, int category)
: SceneNode(category)
, mArray(type)
{
    updatePrimitiveSize();
}

////////////////////////////////////////////////

VertexArrayNode::~VertexArrayNode()
{
    clearChildren();
}

////////////////////////////////////////////////

void VertexArrayNode::updatePrimitiveSize()
{
    switch(mArray.getPrimitiveType())
    {
        case sf::PrimitiveType::Points:
        case sf::PrimitiveType::LinesStrip:
        case sf::PrimitiveType::TrianglesStrip:
        case sf::PrimitiveType::TrianglesFan:
            mPrimitiveSize = 1;
            break;

        case sf::PrimitiveType::Lines:
            mPrimitiveSize = 2;
            break;

        case sf::PrimitiveType::Triangles:
            mPrimitiveSize = 3;
            break;

        case sf::PrimitiveType::Quads:
            mPrimitiveSize = 4;
            break;

        default:
            mPrimitiveSize = 0;
            break;
    }
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

////////////////////////////////////////////////

sf::FloatRect VertexArrayNode::getBoundingRect() const
{
    return getWorldTransform().transformRect(mArray.getBounds());
}

////////////////////////////////////////////////

unsigned int VertexArrayNode::insert(std::vector<sf::Vertex> primitive)
{
    // Make sure we are inserting ONE primitive.
    assert(primitive.size() == mPrimitiveSize);


    unsigned int index;
    if(mFreeIndices.empty())
    {
        index = mArray.getVertexCount();
        mArray.resize(index + mPrimitiveSize);
    }
    else
    {
        index = mFreeIndices.front();
        mFreeIndices.pop();
    }

    for(unsigned int i = 0; i < mPrimitiveSize; i++)
        mArray[index + i] = primitive[i];

    return index;
}

////////////////////////////////////////////////

void VertexArrayNode::free(unsigned int index)
{
    // Make sure index is not out of bounds.
    assert(index <= mArray.getVertexCount() - mPrimitiveSize);

    // Make sure the index is at the start of a primitive.
    assert(index % mPrimitiveSize == 0);

    for(unsigned int i = index; i < index + mPrimitiveSize; i++)
        mArray[i] = sf::Vertex();

    mFreeIndices.push(index);
}

////////////////////////////////////////////////

sf::Vertex& VertexArrayNode::operator[](unsigned int index)
{
    return mArray[index];
}

////////////////////////////////////////////////

const sf::Vertex& VertexArrayNode::operator[](unsigned int index) const
{
    return mArray[index];
}

////////////////////////////////////////////////

unsigned int VertexArrayNode::getSize() const
{
    return (mArray.getVertexCount() / mPrimitiveSize) - mFreeIndices.size();
}

////////////////////////////////////////////////

unsigned int VertexArrayNode::getCount() const
{
    return mArray.getVertexCount();
}
