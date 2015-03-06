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
#include <stdexcept>
#include <iostream>
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "Midi.hpp"
////////////////////////////////////////////////


Midi::Midi(const std::string& filePath)
: mFile()
{
    if(!mFile.read(filePath))
        std::runtime_error("Midi::Midi - Failed to load " + filePath);
}


std::list<Midi::Note> Midi::getNotes()
{
    int tracks = mFile.getTrackCount();
    std::cout << "TPQ: " << mFile.getTicksPerQuarterNote() << endl;
    if (tracks > 1)
    {
      std::cout << "TRACKS: " << tracks << endl;
    }
    int TPQ = mFile.getTicksPerQuarterNote();

    char* notes[12] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

    //mFile.joinTracks();


    for (int track=0; track < tracks; track++)
    {
      if (tracks > 1)
      {
         std::cout << "\nTrack " << track << endl;
      }
    for (int event=0; event < mFile[track].size(); event++)
    {
        if(mFile[track][event][0] == 0x90)
        {
            std::cout << mFile[track][event].tick / TPQ << '\t' << (int)mFile[track][event][0] << '\t' << (int)mFile[track][event][1] << std::endl;
        }

        if(event >= 10)
            int flurp = 0;
      }
    }

    std::list<Note> derp;
    return derp;
}
