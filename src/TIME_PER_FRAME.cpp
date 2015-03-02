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
#include "TIME_PER_FRAME.hpp"
////////////////////////////////////////////////


float TIME_PER_FRAME::mSeconds      = 0.f;
float TIME_PER_FRAME::mMilliSeconds = 0.f;

////////////////////////////////////////////////

void TIME_PER_FRAME::setAsSeconds(float seconds)
{
    mSeconds = seconds;
    mMilliSeconds = mSeconds / 1000.f;
}

////////////////////////////////////////////////

const float& TIME_PER_FRAME::seconds()
{
    return mSeconds;
}
