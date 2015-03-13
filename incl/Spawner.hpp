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

#ifndef HITIT_SPAWNER_HPP
#define HITIT_SPAWNER_HPP

////////////////////////////////////////////////
// C++ Standard Library
#include <list>
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Graphics/Rect.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "Midi.hpp"
class AudioSampler;
class SceneNode;
class VertexArrayNode;
////////////////////////////////////////////////

class Spawner
{
    public:
        Spawner(std::string midiFilePath, AudioSampler& sampler, sf::FloatRect spawnArea, SceneNode* layer);

        void update();

        std::list<SceneNode*> spawn();

        bool isEmpty() const;

        float getNoteWidth() const;

        float getBusiestPosition() const;

    private:
        AudioSampler&           mSampler;
        const sf::FloatRect     M_SPAWN_AREA;
        VertexArrayNode*        mObstacles;
        std::list<Midi::Note>   mSpawnQueue;
        float                   mScrollSpeed;
        float                   mTime;
        float                   mMinNoteX;
        float                   mNoteWidth;

};


/************************************************
 * \class Spawner
 *
 * Spawn note obstacles at designated times.
 *
************************************************/

#endif // HITIT_SPAWNER_HPP
