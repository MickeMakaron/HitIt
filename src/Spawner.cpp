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

////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "Spawner.hpp"
#include "TIME_PER_FRAME.hpp"
#include "Obstacle.hpp"
#include "CollissionCategory.hpp"
#include "Midi.hpp"
////////////////////////////////////////////////

Spawner::Spawner(const std::string& midiFilePath, sf::FloatRect spawnArea)
: mTime(0.f)
, mSpawnArea(spawnArea)
, mSampler()
{
    Midi midi(midiFilePath);
    mSpawnQueue = midi.getNotes();
    mSpawnQueue.sort([](const Midi::Note& a, const Midi::Note& b){return a.time < b.time;});

    auto comparator = [](const Midi::Note& a, const Midi::Note& b){return a.tone < b.tone;};
    Midi::Note maxNote = *std::max_element(mSpawnQueue.begin(), mSpawnQueue.end(), comparator);
    Midi::Note minNote = *std::min_element(mSpawnQueue.begin(), mSpawnQueue.end(), comparator);


    mNoteWidth = mSpawnArea.width / (maxNote.tone - minNote.tone);
    mMinNoteX = minNote.tone * mNoteWidth;

    mScrollSpeed = 500.f;
}

void Spawner::update()
{
    mTime += TIME_PER_FRAME::seconds();
}

std::list<SceneNode*> Spawner::fetchNewNodes()
{
    std::list<SceneNode*> newNodes;
    while(!mSpawnQueue.empty() && mTime >= mSpawnQueue.front().time)
    {
        Midi::Note nextNote = mSpawnQueue.front();
        mSpawnQueue.pop_front();

        Obstacle* obstacle = new Obstacle(/*mSampler.getBuffer(nextNote.tone)*/mSampler.getSoundPlayer(nextNote.tone), mScrollSpeed, nextNote.duration, mNoteWidth, (mSpawnArea.height / mScrollSpeed + nextNote.duration), CollissionCategory::Lethal);
        obstacle->setPosition(mSpawnArea.left + nextNote.tone * mNoteWidth - mMinNoteX, -nextNote.duration * mScrollSpeed);
        newNodes.push_back(obstacle);
    }

    return newNodes;
}


bool Spawner::isEmpty() const
{
    return mSpawnQueue.empty();
}
