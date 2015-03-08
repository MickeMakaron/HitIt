////////////////////////////////////////////////
// C++ Standard Library
#include <stdexcept>
#include <cmath>
#include <cstring>
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "AudioSampler.hpp"
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

AudioSampler::~AudioSampler()
{
    for(SoundPlayer& player : mSoundPlayers)
        player.stop();

    mSoundPlayers.clear();
    mBuffers.clear();
}

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

sf::SoundBuffer& AudioSampler::getBuffer(unsigned int iTone)
{
    return mBuffers[iTone];
}

SoundPlayer& AudioSampler::getSoundPlayer(unsigned int iTone)
{
    return mSoundPlayers[iTone];
}
