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

class HighScore
{
    public:
        /**
         * \brief Constructor
         */
        HighScore();

        /**
         * \brief Destructor
         */
        ~HighScore();

        /**
         * \struct Score
         *
         * Public wrapper for track name, player name and score data
         * in an easily managable format
         */
        struct Score
        {
            std::string     trackName;  ///< Name of MIDI track
            std::string     name;       ///< Name of player
            unsigned int    score;      ///< Score of player
        };

        /**
         * \brief Insert entry into file
         *
         * Entry is only inserted if it actually is a
         * new record.
         *
         * \param trackName Name of MIDI track
         * \param playerName Name of player
         * \param score Score of player
         */
        void insert(std::string trackName, std::string playerName, unsigned int score);

        /**
         * \brief Get score list by MIDI track name
         *
         * \param trackName Name of MIDI track
         *
         * \return List of current highscores on that MIDI track
         */
        std::list<Score> getByTrack(std::string trackName) const;

        /**
         * \brief Get score list by player name
         *
         * \param playerName Name of player
         *
         * \return List of current highscores of that player
         */
        std::list<Score> getByPlayer(std::string playerName) const;

        /**
         * \brief Insert a score into a score list and get resulting iterator
         *
         * Note that this function does not insert the score
         * into the scores file. It is just a convenient way to
         * find out where a score will be placed if it were to be inserted
         * into a score list.
         *
         * \param scores Score list to insert into
         * \param score Score to insert
         *
         * \param Iterator to inserted score
         */
        std::list<Score>::iterator insertRecord(std::list<Score>& scores, Score score) const;

        /**
         * \brief Is the score a new record?
         *
         * Note that this function does not check against
         * the scores file.
         *
         * \param scores Score list to check against
         * \param score Score to evaluate
         *
         * \return True if score is new record, else false
         */
        bool isNewRecord(std::list<Score> scores, unsigned int score) const;

    private:
        static const unsigned int M_STRING_LENGTH = 80; ///< Maximum length of player and track names

        /**
         * \struct Entry
         *
         * Wrapper for track name, player name and score data for
         * writing to file in binary.
         */
        struct Entry
        {
            char            trackName[M_STRING_LENGTH]; ///< Name of MIDI track
            char            name[M_STRING_LENGTH];      ///< Name of player
            unsigned int    score;                      ///< Score of player
        };

        /**
         * \brief Create scores file if not already exists
         */
        void createFile();

        /**
         * \brief Load highscores from file to memory
         */
        void readFile();

        /**
         * \brief Write highscores in memory to file
         */
        void writeToFile();

        /**
         * \brief Get scores by predicate
         *
         * \param predicate Predicate function to get scores by
         *
         * \return List of scores that fulfill predicate
         */
        std::list<Score> get(std::function<bool(const Entry&)> predicate) const;

        /**
         * \brief Erase entry from file
         *
         * Entry is not immediately erased from file.
         * It is rather erased from memory. But since HighScore
         * writes memory to file on destruction this function
         * practically does just that.
         */
        void erase(std::string trackName, std::string playerName);

        /**
         * \brief Get base name from file path
         *
         * \param filePath File path to parse
         *
         * \return Base name of file path, i.e. the file name only
         */
        std::string getBaseName(std::string filePath) const;

    private:
        static const unsigned int M_NUM_ENTRIES_PER_TRACK = 5;  ///< Maximum number of score entries per MIDI track
        const std::string   M_SCORES_FILE_PATH = "scores.bin";  ///< File name of scores file
        std::vector<Entry>  mEntries;                           ///< Data of scores file loaded into memory
};

/************************************************
 * \class HighScore
 *
 * Manages highscore loading and insertion to
 * the scores file.
 *
************************************************/

#endif // HITIT_HIGHSCORE_HPP
