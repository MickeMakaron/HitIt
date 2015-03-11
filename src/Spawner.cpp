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
#include <cstring>
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Graphics/RenderTarget.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "Spawner.hpp"
#include "TIME_PER_FRAME.hpp"
#include "Obstacle.hpp"
#include "CollissionCategory.hpp"
#include "Midi.hpp"
////////////////////////////////////////////////

Spawner::Spawner(std::string midiFilePath, sf::FloatRect spawnArea)
: mTime(0.f)
, mSpawnArea(spawnArea)
, mSampler()
, mObstacles(sf::Quads)
, mScrollSpeed(500.f)
{
    Midi midi(midiFilePath);
    mSpawnQueue = midi.getNotes();
    mSpawnQueue.sort([](const Midi::Note& a, const Midi::Note& b){return a.time < b.time;});

    auto comparator = [](const Midi::Note& a, const Midi::Note& b){return a.tone < b.tone;};
    Midi::Note maxNote = *std::max_element(mSpawnQueue.begin(), mSpawnQueue.end(), comparator);
    Midi::Note minNote = *std::min_element(mSpawnQueue.begin(), mSpawnQueue.end(), comparator);


    mNoteWidth = mSpawnArea.width / (maxNote.tone - minNote.tone);
    mMinNoteX = minNote.tone * mNoteWidth;
}

void Spawner::draw(sf::RenderTarget& target) const
{
    target.draw(mObstacles, mObstaclesState);
}

void Spawner::update()
{
    mTime += TIME_PER_FRAME::seconds();
    mObstaclesState.transform.translate(0.f, mScrollSpeed * TIME_PER_FRAME::seconds());
}

std::list<SceneNode*> Spawner::fetchNewNodes()
{
    std::list<SceneNode*> newNodes;
    while(!mSpawnQueue.empty() && mTime >= mSpawnQueue.front().time)
    {
        Midi::Note nextNote = mSpawnQueue.front();
        mSpawnQueue.pop_front();

        sf::Vertex points[4];
        float left = mSpawnArea.left + nextNote.tone * mNoteWidth - mMinNoteX;
        float top = -(nextNote.duration + nextNote.time) * mScrollSpeed;
        float right = left + mNoteWidth;
        float bot = top + nextNote.duration * mScrollSpeed;
        points[0].position = sf::Vector2f(left, top);
        points[1].position = sf::Vector2f(right, top);
        points[2].position = sf::Vector2f(right, bot);
        points[3].position = sf::Vector2f(left, bot);

        unsigned int numObstacles = mObstacles.getVertexCount();
        mObstacles.resize(numObstacles + 4);
        for(unsigned int i = 0; i < 4; i++)
        {
            points[i].color = sf::Color::Black;
            mObstacles[numObstacles + i] = points[i];
        }

        Obstacle* obstacle = new Obstacle(/*mSampler.getBuffer(nextNote.tone)*/mSampler.getSoundPlayer(nextNote.tone), mScrollSpeed, nextNote.duration, mNoteWidth, (mSpawnArea.height / mScrollSpeed + nextNote.duration), numObstacles, CollissionCategory::Lethal);
        obstacle->setPosition(mSpawnArea.left + nextNote.tone * mNoteWidth - mMinNoteX, -nextNote.duration * mScrollSpeed);
        newNodes.push_back(obstacle);
        mObstacleNodes.push_back(obstacle);

    }

    return newNodes;
}

void Spawner::removeWrecks()
{
    for(const Obstacle* o : mObstacleNodes)
    {
        unsigned int iVertex = o->getVertexArrayIndex();
        for(unsigned int i = iVertex; i < iVertex + 4; i++)
            mObstacles[i] = sf::Vertex();
    }

    mObstacleNodes.remove_if([](Obstacle* o){return o->isMarkedForRemoval();});

}


bool Spawner::isEmpty() const
{
    return mSpawnQueue.empty();
}


void Spawner::pause()
{
    mSampler.pause();
}

void Spawner::resume()
{
    mSampler.resume();
}

void Spawner::setVolume(float volume)
{
    mSampler.setVolume(volume);
}
