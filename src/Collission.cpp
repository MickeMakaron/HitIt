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
#include "Collission.hpp"
#include "CollissionCategory.hpp"
#include "Player.hpp"
#include "BonusStrip.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// C Standard Library
#include <math.h>
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/System/Vector2.hpp"
////////////////////////////////////////////////

Collission::Collission(Player& player, BonusStrip& bonusStrip)
: mPlayer(player)
, mBonusStrip(bonusStrip)
{
}

////////////////////////////////////////////////

Collission::CollissionData::CollissionData(bool hasCollission, sf::Vector2f depth)
: hasCollission(hasCollission)
, depth(depth)
{
}

////////////////////////////////////////////////

void Collission::insert(SceneNode* node)
{
    mNodes.push_back(node);
}

////////////////////////////////////////////////

void Collission::update()
{
    handleCollissions(mNodes);
    handleCollissions(mBonusStrip.getPoints());
}

////////////////////////////////////////////////

void Collission::handleCollissions(std::list<SceneNode*> nodes)
{
    sf::FloatRect playerRect = mPlayer.getBoundingRect();
    sf::Vector2f maxPlayerPenetration(0.f, 0.f);
    for(SceneNode* node : nodes)
    {
        CollissionData data = checkCollission(playerRect, node->getBoundingRect());
        if(!data.hasCollission)
            data = checkCollission(node->getBoundingRect(), playerRect);
        if(data.hasCollission)
        {
            int category = node->getCategory();
            using namespace CollissionCategory;

            if(category & Collidable)
            {
                sf::Vector2f absDepth(std::fabs(data.depth.x), std::fabs(data.depth.y));

                if(absDepth.x < absDepth.y)
                {
                    if(absDepth.x > std::fabs(maxPlayerPenetration.x))
                        maxPlayerPenetration.x = data.depth.x;
                }
                else if(absDepth.y > std::fabs(maxPlayerPenetration.y))
                    maxPlayerPenetration.y = data.depth.y;
            }

            if(category & Lethal)
                mPlayer.damage();

            if(category & Point)
                mBonusStrip.gatherPoint(node);
        }
    }
}

////////////////////////////////////////////////

Collission::CollissionData Collission::checkCollission(sf::FloatRect a, sf::FloatRect b) const
{
    sf::Vector2f depth;

    float aRight, aBottom, bRight, bBottom;
    aRight = a.left + a.width;
    aBottom = a.top + a.height;
    bRight = b.left + b.width;
    bBottom = b.top + b.height;

    if(a.top >= b.top && a.top <= bBottom)
        depth.y = a.top - bBottom;
    else if(aBottom <= bBottom && aBottom >= b.top)
        depth.y = aBottom - b.top;
    else
        return CollissionData();

    if(a.left >= b.left && a.left <= bRight)
        depth.x = a.left - bRight;
    else if(aRight <= bRight && aRight >= b.left)
        depth.x = aRight - b.left;
    else
        return CollissionData();


    if(depth.x && depth.y)
        return CollissionData(true, depth);
    else
        return CollissionData();
}

////////////////////////////////////////////////

void Collission::removeWrecks()
{
	auto begin = std::remove_if(mNodes.begin(), mNodes.end(), std::mem_fn(&SceneNode::isMarkedForRemoval));
	mNodes.erase(begin, mNodes.end());
}
