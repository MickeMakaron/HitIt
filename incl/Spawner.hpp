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
#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/Graphics/RenderStates.hpp"
namespace sf
{
    class RenderTarget;
}
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "Midi.hpp"
#include "AudioSampler.hpp"
class SceneNode;
class Obstacle;
////////////////////////////////////////////////

class Spawner
{
    public:
        Spawner(std::string midiFilePath, sf::FloatRect spawnArea);

        void update();
        void draw(sf::RenderTarget& target) const;

        std::list<SceneNode*> fetchNewNodes();

        bool isEmpty() const;

        /**
         * \brief Pause spawner.
         *
         * Force pauses all sound players.
         */
        void pause();

        /**
         * \brief Resume spawner
         *.
         * Resumes sound players.
         */
        void resume();

        void removeWrecks();

        void setVolume(float volume);

        float getNoteWidth() const;

        float getBusiestPosition() const;

    private:
        std::list<Midi::Note>   mSpawnQueue;
        float                   mTime;
        const sf::FloatRect     mSpawnArea;
        float                   mScrollSpeed;
        AudioSampler            mSampler;
        float                   mMinNoteX;
        float                   mNoteWidth;
        sf::VertexArray         mObstacles;
        sf::RenderStates        mObstaclesState;
        std::list<Obstacle*>    mObstacleNodes;
        float                   mBusiestPosition;
        sf::Vector2f            mTextureCoords[4];
};


/************************************************
 * \class Spawner
 *
 * Spawn note obstacles at designated times.
 *
************************************************/

#endif // HITIT_SPAWNER_HPP
