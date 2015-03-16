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

#ifndef HITIT_RESOURCEIDENTIFIERS_HPP
#define HITIT_RESOURCEIDENTIFIERS_HPP

namespace ResourceID
{
    namespace Texture
    {
        enum ID
        {
            GameStateBg,
            MenuStateBg,
            LoadingStateBg,
            Player,
            AudienceTerrace,
            Fence,
            WorldBg,
            Button,
            Hp,
            BlackOverlay,
            About,
            IDCount,
        };
    }

    namespace Font
    {
        enum ID
        {
            OldGateLaneNF,
            CircusOrnate,
            Arial,
            IDCount,
        };
    }

    namespace Music
    {
        enum ID
        {
            IDCount,
        };
    }

    namespace Sound
    {
        enum ID
        {
            Button,
            PlayerDamaged,
            PlayerStep,
            PickupPoint,
            Bonus1,
            Bonus2,
            Defeat,
            IDCount,
        };
    }
}

#endif // HITIT_RESOURCEIDENTIFIERS_HPP
