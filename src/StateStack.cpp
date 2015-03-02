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
// SFML - Simple and Fast Media Library
#include "SFML/Window/Event.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "StateStack.hpp"
////////////////////////////////////////////////

StateStack::StateStack()
{
}

////////////////////////////////////////////////

void StateStack::update()
{
    /*
     * Update from top of stack to bottom. Stop if a state's update
     * function returns false.
     */
    for(auto it = mStack.rbegin(); it != mStack.rend(); it++)
        if(!(*it)->update())
            break;

    // Only apply changes after all states have been updated.
    applyPendingChanges();
}

////////////////////////////////////////////////

void StateStack::draw()
{
    // Draw all active states from bottom to top
    for(State::Ptr& state : mStack)
        state->draw();
}

////////////////////////////////////////////////

void StateStack::push(State* state)
{
    mPushList.push_back(std::move(State::Ptr(state)));
    mPendingList.push_back(Push);
}

////////////////////////////////////////////////

void StateStack::pop()
{
    mPendingList.push_back(Pop);
}

////////////////////////////////////////////////

void StateStack::clear()
{
    mPendingList.push_back(Clear);
}

////////////////////////////////////////////////

bool StateStack::isEmpty() const
{
    return mStack.empty();
}

////////////////////////////////////////////////

void StateStack::handleEvent(const sf::Event& event)
{
    /*
     * Update from top of stack to bottom. Stop if a state's event
     * handler returns false.
     */
    for(auto it = mStack.rbegin(); it != mStack.rend(); it++)
        if(!(*it)->handleEvent(event))
            break;

    // Only apply changes after all states have handled the events.
    applyPendingChanges();
}

////////////////////////////////////////////////

void StateStack::applyPendingChanges()
{
    for(Action action : mPendingList)
    {
        switch(action)
        {
            case Push:
                mStack.push_back(std::move(mPushList.front()));
                mPushList.pop_front();
                break;

            case Pop:
                mStack.pop_back();
                break;

            case Clear:
                mStack.clear();
                break;
        }
    }

    mPendingList.clear();
}
