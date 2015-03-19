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
// STD - C++ Standard Library
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
        /**
         * \brief Constructor
         *
         * \param filePath Path to MIDI file
         */
        Midi(const std::string& filePath);

        /**
         * \struct Note
         *
         * Wrapper for note data, i.e. tone, duration and starting time.
         */
        struct Note
        {
            unsigned int    tone;       ///< Tone of note
            float           duration;   ///< Duration of note
            float           time;       ///< Starting time of note
        };

        /**
         * \brief Get notes extracted from MIDI file
         *
         * \return List of note data extracted from designated MIDI file
         */
        std::list<Note> getNotes();

    private:
        MidiFile    mFile; ///< MidiFile object containing MIDI data
};

/************************************************
 * \class Midi
 *
 * Interface to MidiFile library, which in turn
 * is an interface to MIDI files.
 *
************************************************/

#endif // HITIT_MIDI_HPP
