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

////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "Spawner.hpp"
#include "TIME_PER_FRAME.hpp"
#include "SceneNode.hpp"
////////////////////////////////////////////////

Spawner::Spawner(const std::string& midiFilePath)
: mTime(0.f)
{
    Midi midi(midiFilePath);
    mSpawnQueue = midi.getNotes();
    mSpawnQueue.sort([](const Midi::Note& a, const Midi::Note& b){return a.time < b.time;});
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
        newNodes.push_back(new SceneNode());
    }

    return newNodes;
}
