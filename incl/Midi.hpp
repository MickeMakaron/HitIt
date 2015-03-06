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

#ifndef HITIT_MIDI_HPP
#define HITIT_MIDI_HPP

////////////////////////////////////////////////
// C++ Standard Library
#include <cstring>
#include <list>
////////////////////////////////////////////////

////////////////////////////////////////////////
// Midifile library
#include "MidiFile.h"
////////////////////////////////////////////////


class Midi
{
    public:
        Midi(const std::string& filePath);

        struct Note
        {
            float time;
        };

        std::list<Note> getNotes();


    private:
        MidiFile mFile;
};

/**
 * \class Midi
 *
 */

#endif // HITIT_MIDI_HPP
