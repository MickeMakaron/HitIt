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
// STD - C++ Standard Library
#include <fstream>
#include <cstring>
#include <algorithm>
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "HighScore.hpp"
////////////////////////////////////////////////


HighScore::HighScore()
{

    createFile();
    readFile();
}

void HighScore::createFile()
{
    std::ofstream newFile(M_SCORES_FILE_PATH, std::ios::out | std::ios::app);
    newFile.close();
}

void HighScore::readFile()
{
    std::ifstream file(M_SCORES_FILE_PATH, std::ios::in | std::ios::binary | std::ios::ate);
    if(file.is_open())
    {
        std::streampos size = file.tellg();
        char* data = new char[size];
        file.seekg(0, std::ios::beg);
        file.read(data, size);
        file.close();

        unsigned int numEntries = size / sizeof(Entry);
        Entry* entries = (Entry*)data;
        mEntries.assign(entries, entries + numEntries);

    }
}

void HighScore::erase(std::string trackName, std::string playerName)
{
    auto found = std::find_if
    (mEntries.begin(), mEntries.end(), [=](const Entry& entry)
    {
        return (trackName == entry.trackName && playerName == entry.name);
    });

    if(found != mEntries.end())
        mEntries.erase(found);
}

std::string HighScore::getBaseName(std::string filePath) const
{
    filePath.erase(0, filePath.find_last_of('/'));
    return filePath;
}

bool HighScore::isNewRecord(std::list<HighScore::Score> scores, unsigned int score) const
{
    if(scores.size() < M_NUM_ENTRIES_PER_TRACK)
        return true;

    scores.sort([](const Score& a, const Score& b){return a.score < b.score;});
    return scores.front().score < score;
}

std::list<HighScore::Score>::iterator HighScore::insertRecord(std::list<HighScore::Score>& scores, HighScore::Score score) const
{
    std::list<HighScore::Score> tmpScores = scores;
    tmpScores.sort([](const Score& a, const Score& b){return a.score < b.score;});
    if(isNewRecord(tmpScores, score.score))
    {
        for(auto it = scores.begin(); it != scores.end(); it++)
        {
            if(it->score < score.score)
            {
                scores.pop_back();
                return scores.insert(it, score);
            }
        }

        return scores.insert(scores.end(), score);
    }
    else
        return scores.end();
}

void HighScore::insert(std::string trackName, std::string playerName, unsigned int score)
{
    trackName = getBaseName(trackName);

    std::list<Score> scores = getByTrack(trackName);

    bool allowInsertion = false;

    if(scores.size() < M_NUM_ENTRIES_PER_TRACK)
        allowInsertion = true;
    else
    {
        scores.sort([](const Score& a, const Score& b){return a.score < b.score;});

        for(auto it = scores.begin(); it != scores.end(); it++)
            if(score > it->score)
            {
                erase(it->trackName, it->name);
                allowInsertion = true;
                break;
            }
    }

    if(allowInsertion)
    {
        trackName.resize(M_STRING_LENGTH);
        playerName.resize(M_STRING_LENGTH);

        Entry entry;
        strcpy(entry.trackName, trackName.data());
        strcpy(entry.name, playerName.data());
        entry.score = score;

        mEntries.push_back(entry);
    }
}

std::list<HighScore::Score> HighScore::get(std::function<bool(const Entry&)> predicate) const
{
    std::list<Score> matches;
    for(const Entry& entry : mEntries)
        if(predicate(entry))
        {
            Score score;

            score.trackName = entry.trackName;
            score.name = entry.name;
            score.score = entry.score;

            matches.push_back(score);
        }

    matches.sort([](const Score& a, const Score& b){return a.score > b.score;});
    return matches;
}

std::list<HighScore::Score> HighScore::getByTrack(std::string trackName) const
{
    trackName = getBaseName(trackName);

    return get
    ([=](const Entry& entry)
    {
       return !strncmp(trackName.data(), entry.trackName, M_STRING_LENGTH);
    });
}

std::list<HighScore::Score> HighScore::getByPlayer(std::string playerName) const
{
    return get
    ([=](const Entry& entry)
    {
        return !strncmp(playerName.data(), entry.name, M_STRING_LENGTH);
    });
}



HighScore::~HighScore()
{
    writeToFile();
}

void HighScore::writeToFile()
{
    std::ofstream entries(M_SCORES_FILE_PATH, std::ios::out | std::ios::binary);
    entries.write((const char*)mEntries.data(), mEntries.size() * sizeof(Entry));
    entries.close();
}
