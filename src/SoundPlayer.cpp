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
#include <cmath>
#include <stdexcept>
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Audio/SoundBuffer.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "SoundPlayer.hpp"
////////////////////////////////////////////////


SoundPlayer::SoundPlayer()
: mVolume(100.f)
, mFadeStep(0.f)
, mSessionCount(0)
{

}

SoundPlayer::SoundPlayer(const sf::SoundBuffer& buffer)
: sf::Sound(buffer)
, mVolume(getVolume())
, mFadeStep(0.f)
, mSessionCount(0)
{

}

void SoundPlayer::update(float seconds)
{
    if(mFadeStep != 0.f)
    {
        float fade = mFadeStep * seconds;

        mVolume += fade;

        if(mVolume < 0.f)
        {
            mVolume = 0.f;;
            mFadeStep = 0.f;
        }
        else if(mVolume > 100.f)
        {
            mVolume = 100.f;
            mFadeStep = 0.f;
        }

        setVolume(mVolume);
    }
}


void SoundPlayer::fade(float targetVolume, float seconds)
{
    mFadeStep = (targetVolume - mVolume) / seconds;
}

void SoundPlayer::setVolume(float volume)
{
    mVolume = volume;
    sf::Sound::setVolume(mVolume);
}

void SoundPlayer::play()
{
    if(getLoop())
    {
        if(mSessionCount == 0)
            sf::Sound::play();

        mSessionCount++;
    }
    else
        sf::Sound::play();

}

void SoundPlayer::stop()
{
    if(getLoop())
    {
        if(mSessionCount <= 1)
        {
            sf::Sound::stop();
            mSessionCount = 0;
        }
        else
            mSessionCount--;
    }
    else
        sf::Sound::stop();
}

void SoundPlayer::pause()
{
    if(getStatus() == Status::Playing)
        sf::Sound::pause();
}


void SoundPlayer::resume()
{
    if(getLoop())
    {
        if(mSessionCount > 0)
            sf::Sound::play();
    }
    else
        sf::Sound::play();
}
