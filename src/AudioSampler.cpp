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
// HitIt internal headers
#include "AudioSampler.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// C Standard Library
#include <math.h>
////////////////////////////////////////////////

////////////////////////////////////////////////
// STD - C++ Standard Library
#include <stdexcept>
////////////////////////////////////////////////

AudioSampler::AudioSampler(unsigned int sampleRate, double volume)
: mBuffers(BOTTOM_C * 2)
, mSoundPlayers(BOTTOM_C * 2)
{
    for(unsigned int iTone = 0; iTone < mBuffers.size(); iTone++)
    {
        sf::Int16* samples;
        unsigned int numSamples;
        createSamples(samples, iTone, numSamples, sampleRate, volume);

        if(!mBuffers[iTone].loadFromSamples(samples, numSamples, 1, sampleRate))
            std::runtime_error("AudioSampler::AudioSampler - Failed to load samples of tone " + iTone);

        mSoundPlayers[iTone].setBuffer(mBuffers[iTone]);
        mSoundPlayers[iTone].setLoop(true);
        delete[] samples;
    }
}

////////////////////////////////////////////////

AudioSampler::~AudioSampler()
{
    for(SoundPlayer& player : mSoundPlayers)
        player.stop();

    mSoundPlayers.clear();
    mBuffers.clear();
}

////////////////////////////////////////////////

void AudioSampler::createSamples(sf::Int16*& samples, unsigned int tone, unsigned int& numSamples, unsigned int sampleRate, double volume) const
{
    const double FREQUENCY = 440. * pow(2, ((double)(tone - BOTTOM_C))/ 12.);
    const double INCREMENT = TWO_PI * FREQUENCY / sampleRate;
    numSamples = sampleRate / FREQUENCY;

    sf::Int16* derp = new sf::Int16[numSamples];
    double time = 0;
    for(unsigned int i = 0; i < numSamples; i++)
    {
        derp[i] = volume * sin(time);
        time += INCREMENT;
    }

    samples = derp;
}

////////////////////////////////////////////////

sf::SoundBuffer& AudioSampler::getBuffer(unsigned int iTone)
{
    return mBuffers[iTone];
}

////////////////////////////////////////////////

SoundPlayer& AudioSampler::getSoundPlayer(unsigned int iTone)
{
    return mSoundPlayers[iTone];
}

////////////////////////////////////////////////

void AudioSampler::pause()
{
    for(SoundPlayer& player : mSoundPlayers)
        player.pause();
}

////////////////////////////////////////////////

void AudioSampler::resume()
{
    for(SoundPlayer& player : mSoundPlayers)
        player.resume();
}

////////////////////////////////////////////////

void AudioSampler::setVolume(float volume)
{
    for(SoundPlayer& player : mSoundPlayers)
        player.setVolume(volume);
}
