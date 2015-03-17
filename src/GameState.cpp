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
#include "SFML/Graphics/RenderTarget.hpp"
////////////////////////////////////////////////


////////////////////////////////////////////////
// HitIt internal headers
#include "GameState.hpp"
#include "HighScoreMenu.hpp"
#include "PauseMenu.hpp"
#include "DefeatMenu.hpp"
#include "Assets.hpp"
////////////////////////////////////////////////


GameState::GameState(StateStack& stack, sf::RenderTarget& target, std::string midiFile)
: State(stack)
, mTarget(target)
, mWorld(mTarget, midiFile)
, mMidiFile(midiFile)
{
}

////////////////////////////////////////////////

void GameState::draw()
{
    mWorld.draw();
}

////////////////////////////////////////////////

bool GameState::update()
{
    mWorld.update();

    switch(mWorld.getState())
    {
        case World::Running:
            // Do nothing.
            break;

        case World::Victory:
            mWorld.pause();
            requestStackPush(new HighScoreMenu(getStack(), mTarget, mMidiFile, mWorld.getScore()));
            break;

        case World::Defeat:
            mWorld.pause();
            requestStackPush(new DefeatMenu(getStack(), mTarget, mMidiFile));
            break;

        default:
            break;
    }

	return true;
}

////////////////////////////////////////////////

bool GameState::handleEvent(const sf::Event& event)
{
    mWorld.handleEvent(event);

	if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        requestStackPush(new PauseMenu(getStack(), mTarget, *this));//requestStackPush(new VictoryMenu(getStack(), mTarget));//requestStackClear();//requestStackPush(new PauseState(getStack(), mTarget));

	return true;
}


void GameState::pause()
{
    mWorld.pause();
}

void GameState::resume()
{
    mWorld.resume();
}
