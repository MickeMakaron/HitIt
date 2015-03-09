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

#ifndef HITIT_PLAYER_HPP
#define HITIT_PLAYER_HPP

////////////////////////////////////////////////
// HitIt internal headers
#include "SpriteNode.hpp"
////////////////////////////////////////////////


class Player : public SpriteNode
{
    public:
        /**
         * \brief Constructor
         *
         * \param texture texture to apply to sprite.
         * \param hp hp of player
         * \param position initial position
         */
        Player(const sf::Texture& texture, int hp, sf::Vector2f position = sf::Vector2f(0.f, 0.f));

        /**
         * \brief Damage the player by a fixed amount.
         */
        void damage();

        /**
         * \brief Kill player.
         */
        void destroy();

        /**
         * \brief Check if player is dead.
         */
        bool isDestroyed() const;

        /**
         * \brief Increase movement speed.
         */
        void accelerate(float a);

        /**
         * \brief Get current HP.
         *
         * \return current HP of player node.
         */
         int getHp() const;

    private:
        /**
         * \brief Draw this node.
         *
         * \param target SFML RenderTarget object to draw this node to.
         * \param states SFML RenderStates object ot transform draw with.
         */
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	    /**
	     * \brief Update this node.
	     */
		virtual void updateCurrent();

    private:
        int             mHp;                    ///< Hp of player.
        float           mMovementSpeed;         ///< Movement speed.
        float           mDiagonalMovementSpeed; ///< Movement speed when moving diagonally.
        bool            mIsImmortal;            ///< Indicator whether player is immortal.
        const float     mImmortalTime = 2.f;    ///< Time to remain immortal in seconds.
        float           mImmortalCounter;       ///< Time accumulator for immortality.
        bool            mIsJumping;             ///< Indicator whether player is jumping.
        const float     mJumpingTime = 1.f;      ///< Time airborne in seconds.
        float           mJumpingCounter;        ///< Time accumulator for jumping.

};

#endif // HITIT_PLAYER_HPP
