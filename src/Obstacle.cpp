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
#include "Obstacle.hpp"
#include "TIME_PER_FRAME.hpp"
#include "SoundPlayer.hpp"
#include "VertexArrayNode.hpp"
////////////////////////////////////////////////


Obstacle::Obstacle(SoundPlayer& buffer, VertexArrayNode& array, float playLine, float deathLine, int category)
: SceneNode(category)
, mSoundPlayer(buffer)
, mArray(array)
, mRect(0.f, 0.f, 0.f, 0.f)
, M_PLAYLINE(playLine)
, M_DEATHLINE(deathLine)
, mState(Waiting)
, mStateFuncs(StateCount, [](){})
{
    std::vector<sf::Vertex> points(4, sf::Vertex(sf::Vector2f(0.f, 0.f), sf::Color::Black));
    points[0].color = points[1].color = sf::Color(70, 70, 70);

    M_VERTEX_ARRAY_INDEX = mArray.insert(points);

    mStateFuncs[Waiting] = [this]()
    {
        if(getWorldPosition().y + getBoundingRect().height >= M_PLAYLINE)
        {
            mState = Playing;
            mSoundPlayer.play();
            mArray[M_VERTEX_ARRAY_INDEX + 2].color = mArray[M_VERTEX_ARRAY_INDEX + 3].color = sf::Color(50, 50, 50);
        }
    };

    mStateFuncs[Playing] = [this]()
    {
        if(getWorldPosition().y >= M_PLAYLINE)
        {
            mState = Silent;
            mSoundPlayer.stop();
            mArray[M_VERTEX_ARRAY_INDEX + 2].color = mArray[M_VERTEX_ARRAY_INDEX + 3].color = sf::Color::Black;
        }
    };

    mStateFuncs[Silent] = [this]()
    {
        if(getWorldPosition().y >= M_DEATHLINE)
            mState = Dead;
    };
}

Obstacle::~Obstacle()
{
    mArray.free(M_VERTEX_ARRAY_INDEX);
}

void Obstacle::setSize(float width, float height)
{
    mRect.width = width;
    mRect.height = height;

    updateVertices();
}

void Obstacle::setPosition(float x, float y)
{
    mRect.left = x;
    mRect.top = y;

    updateVertices();
}

void Obstacle::updateVertices()
{
    float left, right, top, bot;
    left = mRect.left;
    right = left + mRect.width;
    top = mRect.top;
    bot = top + mRect.height;

    mArray[M_VERTEX_ARRAY_INDEX].position       = sf::Vector2f(left, top);
    mArray[M_VERTEX_ARRAY_INDEX + 1].position   = sf::Vector2f(right, top);
    mArray[M_VERTEX_ARRAY_INDEX + 2].position   = sf::Vector2f(right, bot);
    mArray[M_VERTEX_ARRAY_INDEX + 3].position   = sf::Vector2f(left, bot);
}


bool Obstacle::isMarkedForRemoval() const
{
    return mState == Dead;
}

void Obstacle::updateCurrent()
{
    mStateFuncs[mState]();
}

sf::Vector2f Obstacle::getWorldPosition() const
{
    return mArray.getWorldTransform().transformPoint(mRect.left, mRect.top);
}

sf::FloatRect Obstacle::getBoundingRect() const
{
    return mArray.getWorldTransform().transformRect(mRect);
}
