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
// STD - C++ Standard Library
#include <cassert>
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Graphics/RenderTarget.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "BonusStrip.hpp"
#include "TIME_PER_FRAME.hpp"
#include "VertexArrayNode.hpp"
#include "CollissionCategory.hpp"
#include "RectangleNode.hpp"
////////////////////////////////////////////////


BonusStrip::BonusStrip(const VertexArrayNode& obstacles, sf::Vector2f windowSize, int category)
: VertexArrayNode(sf::Quads)
, M_OBSTACLES(obstacles)
, M_SIZE(windowSize.x / 4.f, windowSize.y)
, M_SCROLL_SPEED(300.f)
, mTimer(0.f)
, mPointsScore(0.f)
{
    initializeStrip();
}

void BonusStrip::initializeStrip()
{
    float middleX = M_SIZE.x * 2.f;
    float quadWidth = M_SIZE.x / 2.f;

    float left = middleX - M_SIZE.x / 2.f;
    float right = middleX + M_SIZE.x / 2.f;
    for(float top = M_SIZE.y * 2.f; top > -M_SCROLL_SPEED * M_UPDATE_INTERVAL * 2.f; top -= 10.f)
    {
        insertQuad(left, left, top, top + 10.f, true);
        insertQuad(middleX, middleX, top, top + 10.f, false);
    }
}

void BonusStrip::updateCurrent()
{
    mTimer += TIME_PER_FRAME::seconds();


    if(mTimer >= M_UPDATE_INTERVAL)
    {
        removeQuad();
        removeQuad();

        float middleX = getBusiestPosition();
        float prevMiddleX = operator[](mQuadIndexQueue.back()).position.x;
        float quadWidth = M_SIZE.x / 2.f;
        float bot = operator[](mQuadIndexQueue.back()).position.y;
        float step =  M_SCROLL_SPEED * mTimer;
        insertQuad(middleX - quadWidth, prevMiddleX - quadWidth, bot - step, bot, true);
        insertQuad(middleX, prevMiddleX, bot - step, bot, false);


        spawnPoint(middleX);
        mTimer = 0.f;
    }

    move(0.f, M_SCROLL_SPEED * TIME_PER_FRAME::seconds());
}

void BonusStrip::removeQuad()
{
    free(mQuadIndexQueue.front());
    mQuadIndexQueue.pop();
}

void BonusStrip::insertQuad(float topLeft, float botLeft, float top, float bot, bool isLeft)
{
    std::vector<sf::Vertex> quad(4);
    float width = M_SIZE.x / 2.f;
    quad[0].position = sf::Vector2f(topLeft, top);
    quad[1].position = sf::Vector2f(topLeft + width, top);
    quad[2].position = sf::Vector2f(botLeft + width, bot);
    quad[3].position = sf::Vector2f(botLeft, bot);

    if(isLeft)
    {
        quad[0].color = quad[3].color = sf::Color::Black;
        quad[1].color = quad[2].color = sf::Color::White;
    }
    else
    {
        quad[0].color = quad[3].color = sf::Color::White;
        quad[1].color = quad[2].color = sf::Color::Black;
    }

    mQuadIndexQueue.push(insert(quad));
}


float BonusStrip::getBusiestPosition() const
{
    float positionSumX = 0.f;
    unsigned int numObstacles = M_OBSTACLES.getSize() / 4;
    for(unsigned int i = 0; i < numObstacles * 4; i += 4)
        positionSumX += M_OBSTACLES[i].position.x;

    return (numObstacles == 0) ? M_SIZE.x * 2.f : positionSumX / numObstacles;
}


float BonusStrip::getDistance(sf::Vector2f p) const
{
    float minSqrd = std::numeric_limits<float>::max();
    for(unsigned int i = 1; i < getSize(); i += 8)
    {
        sf::Vector2f d = p - getWorldTransform().transformPoint(operator[](i).position);
        float dSqrd = d.x * d.x + d.y * d.y;
        if(dSqrd < minSqrd)
            minSqrd = dSqrd;
    }

    for(unsigned int i = 2; i < getSize(); i+= 8)
    {
        sf::Vector2f d = p - getWorldTransform().transformPoint(operator[](i).position);
        float dSqrd = d.x * d.x + d.y * d.y;
        if(dSqrd < minSqrd)
            minSqrd = dSqrd;
    }

    return sqrtf(minSqrd);
}

float BonusStrip::getWidth() const
{
    return M_SIZE.x;
}

void BonusStrip::spawnPoint(float x)
{
    RectangleNode* point = new RectangleNode(sf::Vector2f(20.f, 20.f), CollissionCategory::Point);
    point->setPosition(x, operator[](mQuadIndexQueue.back()).position.y);
    point->setFillColor(sf::Color::Yellow);
    point->setOutlineColor(sf::Color::Black);
    point->setOutlineThickness(1.f);
    attachChild(point);
    mPoints.push_back(point);
}

float BonusStrip::fetchPointsScore()
{
    float score = mPointsScore;
    mPointsScore = 0.f;
    return score;
}

void BonusStrip::gatherPoint(SceneNode* point)
{
    auto it = std::find(mPoints.begin(), mPoints.end(), point);
    if(it != mPoints.end())
        mPoints.erase(it);

    detachChild(*point);
    mPointsScore += 5.f;
}

const std::list<SceneNode*>& BonusStrip::getPoints() const
{
    return mPoints;
}
