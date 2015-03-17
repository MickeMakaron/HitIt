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

#ifndef HITIT_HIGHSCORE_HPP
#define HITIT_HIGHSCORE_HPP



////////////////////////////////////////////////
// STD - C++ Standard Library
#include <string>
#include <vector>
#include <list>
#include <functional>
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library

////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers

////////////////////////////////////////////////


class HighScore
{
    public:
        HighScore();
        ~HighScore();

        struct Score
        {
            std::string     trackName;
            std::string     name;
            unsigned int    score;
        };

        void insert(std::string trackName, std::string playerName, unsigned int score);

        std::list<Score> getByTrack(std::string trackName) const;
        std::list<Score> getByPlayer(std::string playerName) const;

        std::list<Score>::iterator insertRecord(std::list<Score>& scores, Score score) const;
        bool isNewRecord(std::list<Score> scores, unsigned int score) const;

    private:
        static const unsigned int M_STRING_LENGTH = 80;
        struct Entry
        {
            char            trackName[M_STRING_LENGTH];
            char            name[M_STRING_LENGTH];
            unsigned int    score;
        };

        void createFile();
        void readFile();
        void writeToFile();

        std::list<Score> get(std::function<bool(const Entry&)> predicate) const;
        void erase(std::string trackName, std::string playerName);

        std::string getBaseName(std::string filePath) const;

    private:
        static const unsigned int M_NUM_ENTRIES_PER_TRACK = 5;
        const std::string   M_SCORES_FILE_PATH = "scores.bin";
        std::vector<Entry>  mEntries;
};

/************************************************
 * \class HighScore
 *
 *
 *
************************************************/

#endif // HITIT_HIGHSCORE_HPP
