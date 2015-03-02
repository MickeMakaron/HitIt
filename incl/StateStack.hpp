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

#ifndef HITIT_STATESTACK_HPP
#define HITIT_STATESTACK_HPP



////////////////////////////////////////////////
// C++ Standard Library
#include <list>
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/System/NonCopyable.hpp"
namespace sf
{
    class Event;
}
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "State.hpp"
////////////////////////////////////////////////

class StateStack : private sf::NonCopyable
{
    public:
        enum Action
        {
            Push,
            Pop,
            Clear,
        };

    public:
        /**
         * \brief Constructor
         */
        StateStack();

        /**
         * \brief Update states.
         */
        void update();

        /**
         * \brief Draw states.
         */
        void draw();

        /**
         * \brief Handle input events.
         *
         * \param event event to handle.
         */
        void handleEvent(const sf::Event& event);

        /**
         * \brief Push state on top of stack.
         *
         * Note that the state stack will take
         * ownership of the pointer by using
         * unique pointers. This means the
         * state object will be destructed
         * when the state stack object is.
         *
         * \param state State pointer to push.
         */
        void push(State* state);

        /**
         * \brief Pop state on top of stack.
         */
        void pop();

        /**
         * \brief Clear all states from stack.
         */
        void clear();

        /**
         * \brief Check if stack is empty.
         */
        bool isEmpty() const;

    private:
        /**
         * \brief Apply pending pushes, pops or clears.
         */
        void                applyPendingChanges();

    private:
        std::list<State::Ptr>     mStack;       ///< FILO-stack of unique State pointers
        std::list<State::Ptr>     mPushList;    ///< FIFO-list of pending state pushes.
        std::list<Action>         mPendingList; ///< FIFO-list of pending pop and clear requests.
};


/************************************************
 * \class StateStack
 *
 * FILO-stack for program states.
 *
************************************************/

#endif // HITIT_STATESTACK_HPP
