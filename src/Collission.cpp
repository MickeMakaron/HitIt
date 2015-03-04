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
#include <cmath>
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "Collission.hpp"
////////////////////////////////////////////////

Collission::Collission()
: mPlayer(nullptr)
{

}

Collission::CollissionData::CollissionData(bool hasCollission, sf::Vector2f depth)
: hasCollission(hasCollission)
, depth(depth)
{
}

void Collission::setPlayer(Player* player)
{
    mPlayer = player;
}

void Collission::insert(SceneNode* node)
{
    mNodes.push_back(node);
}

void Collission::update()
{
    assert(mPlayer != nullptr);

    for(const SceneNode* node : mNodes)
    {
        CollissionData data = checkCollission(mPlayer->getBoundingRect(), node->getBoundingRect());
        if(data.hasCollission)
        {
            if(std::fabs(data.depth.x) > std::fabs(data.depth.y))
                data.depth.x = 0.f;
            else
                data.depth.y = 0.f;
            mPlayer->move(-data.depth);
        }
    }
}

Collission::CollissionData Collission::checkCollission(sf::FloatRect a, sf::FloatRect b) const
{
    sf::Vector2f depth;
    bool xIsect = false;
    bool yIsect = false;

    float aRight, aBottom, bRight, bBottom;
    aRight = a.left + a.width;
    aBottom = a.top + a.height;
    bRight = b.left + b.width;
    bBottom = b.top + b.height;

    if(a.left >= b.left && a.left <= bRight)
        depth.x = a.left - bRight;
    else if(aRight <= bRight && aRight >= b.left)
        depth.x = aRight - b.left;
    else
        return CollissionData();

    if(a.top >= b.top && a.top <= bBottom)
        depth.y = a.top - bBottom;
    else if(aBottom <= bBottom && aBottom >= b.top)
        depth.y = aBottom - b.top;
    else
        return CollissionData();

    return CollissionData(true, depth);
}
