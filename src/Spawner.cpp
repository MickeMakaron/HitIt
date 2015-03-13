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
// HitIt internal headers
#include "Spawner.hpp"
#include "TIME_PER_FRAME.hpp"
#include "Obstacle.hpp"
#include "CollissionCategory.hpp"
#include "VertexArrayNode.hpp"
#include "AudioSampler.hpp"
////////////////////////////////////////////////

Spawner::Spawner(std::string midiFilePath, AudioSampler& sampler, sf::FloatRect spawnArea, SceneNode* layer)
: mSampler(sampler)
, M_SPAWN_AREA(spawnArea)
, mObstacles(new VertexArrayNode(sf::Quads))
, mScrollSpeed(300.f)
, mTime(0.f)
{
    Midi midi(midiFilePath);
    mSpawnQueue = midi.getNotes();
    mSpawnQueue.sort([](const Midi::Note& a, const Midi::Note& b){return a.time < b.time;});

    auto comparator = [](const Midi::Note& a, const Midi::Note& b){return a.tone < b.tone;};
    Midi::Note maxNote = *std::max_element(mSpawnQueue.begin(), mSpawnQueue.end(), comparator);
    Midi::Note minNote = *std::min_element(mSpawnQueue.begin(), mSpawnQueue.end(), comparator);

    mNoteWidth = M_SPAWN_AREA.width / (maxNote.tone - minNote.tone + 1);
    mMinNote = minNote.tone;

    layer->attachChild(mObstacles);
}


void Spawner::update()
{
    mTime += TIME_PER_FRAME::seconds();
    mObstacles->move(0.f, mScrollSpeed * TIME_PER_FRAME::seconds());
}

std::list<SceneNode*> Spawner::spawn()
{
    std::list<SceneNode*> spawns;
    while(!mSpawnQueue.empty() && mTime >= mSpawnQueue.front().time)
    {
        Midi::Note nextNote = mSpawnQueue.front();
        mSpawnQueue.pop_front();

        Obstacle* obstacle = new Obstacle(mSampler.getSoundPlayer(nextNote.tone), *mObstacles, M_SPAWN_AREA.height / 3.f, M_SPAWN_AREA.height, CollissionCategory::Lethal);
        obstacle->setPosition(M_SPAWN_AREA.left + (nextNote.tone - mMinNote) * mNoteWidth, -(nextNote.duration + mTime) * mScrollSpeed);
        obstacle->setSize(mNoteWidth, nextNote.duration * mScrollSpeed);
        spawns.push_back(obstacle);

        mObstacles->attachChild(obstacle);
    }

    return spawns;
}

bool Spawner::isEmpty() const
{
    return mSpawnQueue.empty();
}

float Spawner::getNoteWidth() const
{
    return mNoteWidth;
}

float Spawner::getBusiestPosition() const
{
    float positionSumX = 0.f;
    unsigned int numObstacles = mObstacles->getSize() / 4;
    for(unsigned int i = 0; i < numObstacles * 4; i += 4)
        positionSumX += mObstacles->operator[](i).position.x;

    return (numObstacles == 0) ? M_SPAWN_AREA.width / 2.f : positionSumX / numObstacles;
}

