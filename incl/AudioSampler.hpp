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
// HitIt internal headers
#include "SoundPlayer.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// STD - C++ Standard Library
#include <vector>
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Audio/SoundBuffer.hpp"
////////////////////////////////////////////////

class AudioSampler
{
    public:
        /**
         * \brief Constructor
         *
         * \param sampleRate Sample rate to produce sound buffers at
         * \param volume Amplitude of soundwaves
         */
        AudioSampler(unsigned int sampleRate = 44100, double volume = 2000);

        /**
         * \brief Destructor
         */
        ~AudioSampler();

        /**
         * \brief Get buffer by tone
         *
         * \param iTone Tone starting from C0
         *
         * \return Reference to SFML SoundBuffer object containing tone samples
         */
        sf::SoundBuffer& getBuffer(unsigned int iTone);

        /**
         * \brief Get sound player by tone
         *
         * \param iTone Tone starting from C0
         *
         * \return Reference to SoundPlayer object able to play the given tone
         */
        SoundPlayer& getSoundPlayer(unsigned int iTone);

        /**
         * \brief Pause all sound players
         *
         * Ignores any session count.
         *
         */
        void pause();

        /**
         * \brief Resume all sound players
         */
        void resume();

        /**
         * \brief Set volume of all sound players
         */
        void setVolume(float volume);

    private:
        /**
         * \brief Create raw audio samples for a specific tone
         *
         * \param samples Raw audio data to return
         * \param tone Tone to generate audio data of
         * \param numSamples Number of samples that are required (depends on wavelength)
         * \param sampleRate Sample rate to produce data with
         * \param volume Amplitude of sound waves
         */
        void createSamples(sf::Int16*& samples, unsigned int tone, unsigned int& numSamples, unsigned int sampleRate, double volume) const;

    private:
        const double BOTTOM_C = 57.;                            ///< C0, 4 octaves below "middle C"
        const double TWO_PI = 6.283185307179586476925286766559; ///< Caching PI * 2 for performance
        std::vector<sf::SoundBuffer> mBuffers;                  ///< Array of sound buffers
        std::vector<SoundPlayer>     mSoundPlayers;             ///< Array of sound players
};

/************************************************
 * \class AudioSampler
 *
 * Create raw audio samples for all tones ranging from
 * frequency 16.35 (C0, 4 octaves below "middle C") to
 * frequency 11839.82 (way too high).
 *
************************************************/

#endif // HITIT_AUDIOSAMPLER_HPP
