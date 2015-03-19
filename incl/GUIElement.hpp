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

#ifndef HITIT_GUIELEMENT_HPP
#define HITIT_GUIELEMENT_HPP

////////////////////////////////////////////////
// HitIt internal headers
#include "SceneNode.hpp"
////////////////////////////////////////////////

class GUIElement : public SceneNode
{
    public:
        /**
         * \brief Constructor
         */
        GUIElement();

        /**
         * \brief Destructor
         */
        virtual ~GUIElement();

        /**
         * \brief Indicate whether element is selectable or not
         *
         * \return True if selectable, else false
         */
        virtual bool isSelectable() const;

        /**
         * \brief Indicate whether element is selected or not
         *
         * \return True if selected, else false
         */
        bool isSelected() const;

        /**
         * \brief Toggle selection
         *
         * If currently selected, it deselects.
         * If not currently selected, select.
         */
        void toggleSelection();

        /**
         * \brief Indicate whether element can be activated or not
         *
         * \return True if activatable, else false
         */
        virtual bool isActivatable() const;

        /**
         * \brief Indicate whether element is active or not
         *
         * \return True if active, else false
         */
        bool isActive() const;

        /**
         * \brief Toggle activation
         *
         * If currently activated, it deactivates.
         * If not currently activated, it activates.
         */
        void toggleActivation();

    private:
        /**
         * \brief Select element
         */
        virtual void select();

        /**
         * \brief Deselect element
         */
        virtual void deselect();

        /**
         * \brief Activate element
         */
        virtual void activate();

        /**
         * \brief Deactivate element
         */
        virtual void deactivate();

    private:
        bool mIsSelected;   ///< Is the element currently selected?
        bool mIsActive;     ///< Is the element currently active?
};

/************************************************
 * \class GUIElement
 *
 * A graphical user interface element for menus.
 *
************************************************/

#endif // HITIT_GUIELEMENT_HPP
