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

#ifndef HITIT_AUDIOSAMPLER_HPP
#define HITIT_AUDIOSAMPLER_HPP

////////////////////////////////////////////////
// C++ Standard Library
#include <vector>
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Audio/SoundBuffer.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "SoundPlayer.hpp"
////////////////////////////////////////////////

class AudioSampler
{
    public:
        AudioSampler(unsigned int sampleRate = 44100, double volume = 2000);
        ~AudioSampler();


        sf::SoundBuffer& getBuffer(unsigned int iTone);
        SoundPlayer& getSoundPlayer(unsigned int iTone);
    private:
        void createSamples(sf::Int16*& samples, unsigned int tone, unsigned int& numSamples, unsigned int sampleRate, double volume) const;

    private:
        const double BOTTOM_C = 57.;
        const double TWO_PI = 6.283185307179586476925286766559;
        std::vector<sf::SoundBuffer> mBuffers;
        std::vector<SoundPlayer>     mSoundPlayers;
};


/************************************************
 * \class AudioSampler
 *
 * Create raw audio samples for all tones.
 *
************************************************/

#endif // HITIT_AUDIOSAMPLER_HPP
