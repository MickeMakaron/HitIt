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

#ifndef HITIT_COLLISSION_HPP
#define HITIT_COLLISSION_HPP

////////////////////////////////////////////////
// HitIt internal headers
#include "Player.hpp"
////////////////////////////////////////////////


class Collission
{
    public:
        Collission();

        void setPlayer(Player* player);
        void insert(SceneNode* node);
        void update();

    private:
        struct CollissionData
        {
            CollissionData(bool hasCollission = false, sf::Vector2f depth = sf::Vector2f(0.f, 0.f));
            bool            hasCollission;
            sf::Vector2f    depth;
        };

        CollissionData checkCollission(sf::FloatRect a, sf::FloatRect b) const;

    private:
        Player*                 mPlayer;
        std::list<SceneNode*>   mNodes;
};

#endif // HITIT_COLLISSION_HPP
