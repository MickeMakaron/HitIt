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
#include "SFML/Graphics/RenderWindow.hpp"
////////////////////////////////////////////////


////////////////////////////////////////////////
// HitIt internal headers
#include "GameState.hpp"
#include "MenuState.hpp"
#include "Assets.hpp"
////////////////////////////////////////////////


GameState::GameState(StateStack& stack, sf::RenderWindow& window)
: State(stack)
, mWindow(window)
, mWorld(mWindow)
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


	return true;
}

////////////////////////////////////////////////

bool GameState::handleEvent(const sf::Event& event)
{
    mWorld.handleEvent(event);

	// Escape pressed, trigger the pause screen
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    {
        requestStackPop();
		requestStackPush(new MenuState(getStack(), mWindow));
    }

	return true;
}
