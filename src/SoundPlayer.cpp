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
// HitIt internal headers
#include "SoundPlayer.hpp"
////////////////////////////////////////////////


SoundPlayer::SoundPlayer(double frequency, unsigned int sampleRate)
{
    sf::Int16 sample[sampleRate];

    const double AMPLITUDE = 1000;
    const double TWO_PI = 6.283185307179586476925286766559;
    const double INCREMENT = frequency / sampleRate;

    double x = 0;
    for(unsigned int i = 0; i < sampleRate; i++)
    {
        sample[i] = AMPLITUDE * sin(x * TWO_PI);
        x += INCREMENT;
    }

    if(!mBuffer.loadFromSamples(sample, sampleRate, 1, sampleRate))
        std::runtime_error("SoundPlayer::SoundPlayer - Failed to load sample.");

    mSound.setBuffer(mBuffer);
    mSound.setLoop(true);
}


void SoundPlayer::play()
{
    mSound.play();
}

