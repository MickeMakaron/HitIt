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
// HitIt internal headers
#include "Midi.hpp"
class AudioSampler;
class SceneNode;
class VertexArrayNode;
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Graphics/Rect.hpp"
////////////////////////////////////////////////

class Spawner
{
    public:
        /**
         * \brief Constructor
         *
         * \param midiFilePath File path to MIDI file
         * \param sampler AudioSampler to use for playing notes
         * \param spawnArea Area designated for spawning Obstacle nodes
         * \param layer Scene graph layer to spawn Obstacle nodes into
         */
        Spawner(std::string midiFilePath, AudioSampler& sampler, sf::FloatRect spawnArea, SceneNode* layer);

        /**
         * \brief Update spawner
         */
        void update();

        /**
         * \brief Spawn new nodes
         *
         * Inserts nodes into designated scene graph layer.
         *
         * \return List of pointers to spawned nodes
         */
        std::list<SceneNode*> spawn();

        /**
         * \brief Indicate whether the spawn queue is empty or not
         *
         * \return True if spawn queue is empty, else false
         */
        bool isEmpty() const;

        /**
         * \brief Get calculated note width
         *
         * Note width is calculated in respect to spawn area
         * and tone range of the MIDI track.
         *
         * \return Note width
         */
        float getNoteWidth() const;

        /**
         * \brief Get parent vertex array of Obstacle nodes
         *
         * \return Reference to parent vertex array of Obstacle nodes
         */
        const VertexArrayNode& getObstacles() const;

    private:
        AudioSampler&           mSampler;       ///< AudioSampler to use for playing notes
        const sf::FloatRect     M_SPAWN_AREA;   ///< Area designated for spawning Obstacle nodes
        VertexArrayNode*        mObstacles;     ///< Parent vertex array of Obstacle nodes
        std::list<Midi::Note>   mSpawnQueue;    ///< Queue of notes ordered by their starting time
        float                   mScrollSpeed;   ///< Scrolling speed of game
        float                   mTime;          ///< Time counter
        unsigned int            mMinNote;       ///< Lowest note value
        float                   mNoteWidth;     ///< Note width calculated in respect to spawn area and MIDI track's tone range

};

/************************************************
 * \class Spawner
 *
 * Spawn note obstacles at designated times.
 *
************************************************/

#endif // HITIT_SPAWNER_HPP
