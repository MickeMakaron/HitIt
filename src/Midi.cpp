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
    mFile.doTimeInSecondsAnalysis();
    std::list<Note> notes;
    for (int iTrack = 0; iTrack < mFile.getTrackCount(); iTrack++)
    {
        MidiEventList& track = mFile[iTrack];
        track.linkNotePairs();

        for(int iEvent = 0; iEvent < track.size(); iEvent++)
        {
            MidiEvent& event = track[iEvent];

            if(event.isLinked() && event.isNoteOn() && event.getKeyNumber() != -1)
            {
                Note note;
                note.duration = event.getDurationInSeconds();
                note.time = mFile.getTimeInSeconds(event.tick);
                note.tone = event.getKeyNumber();

                notes.push_back(note);
            }
        }
    }

    return notes;
}
