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

#ifndef HITIT_STATE_HPP
#define HITIT_STATE_HPP

////////////////////////////////////////////////
// HitIt internal headers
class StateStack;
////////////////////////////////////////////////

////////////////////////////////////////////////
// STD - C++ Standard Library
#include <memory>
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
namespace sf
{
    class Event;
}
////////////////////////////////////////////////

class State
{
	public:
		typedef std::unique_ptr<State> Ptr;

    public:
        /**
         * \brief Constructor
         *
         * \param stack Stack to insert state into at construction
         */
        State(StateStack& stack);

        /**
         * \brief Destructor
         */
        virtual ~State();

        /**
         * \brief Draw state
         */
        virtual void draw() = 0;

        /**
         * \brief Update state
         *
         * \return Indicate whether the state stack
         * should continue updating further states
         * (true) or not (false)
         */
        virtual bool update() = 0;

        /**
         * \brief Handle input events
         *
         * \param event event to handle
         *
         * \return Indicate whether the state stack
         * should allow further states to handle events
         * (true) or not (false)
         */
        virtual bool handleEvent(const sf::Event& event) = 0;

    protected:
        /**
         * \brief Push state to stack
         */
        void requestStackPush(State* state);

        /**
         * \brief Pop state from stack
         */
        void requestStackPop();

        /**
         * \brief Clear stack
         */
        void requestStackClear();

        /**
         * \brief Get stack
         *
         * \return reference to the stack this state belongs to
         */
         StateStack& getStack();

    private:
        StateStack& mStack; ///< State stack this state belongs to
};

/************************************************
 * \class State
 *
 * Program state with drawing, updating and
 * event handling functions.
 *
************************************************/

#endif // HITIT_STATE_HPP
