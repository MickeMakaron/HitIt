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

#ifndef HITIT_SOUNDPLAYER_HPP
#define HITIT_SOUNDPLAYER_HPP

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Audio/Sound.hpp"
////////////////////////////////////////////////

class SoundPlayer : public sf::Sound
{
    public:
        SoundPlayer();
        SoundPlayer(const sf::SoundBuffer& buffer);


        void update(float seconds);
        void setVolume(float volume);
        void fade(float targetVolume, float seconds);

        void play();
        void stop();
        void pause();
        void resume();

    private:
        float       mVolume;
        float       mFadeStep;
        unsigned    mSessionCount;
};


/************************************************
 * \class SoundPlayer
 *
 * Play sound by raw audio data.
 *
************************************************/

#endif // HITIT_SOUNDPLAYER_HPP
