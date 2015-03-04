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
#include "MenuState.hpp"
#include "GameState.hpp"
////////////////////////////////////////////////


MenuState::MenuState(StateStack& stack, sf::RenderWindow& window)
: State(stack)
, mWindow(window)
{
    namespace ID = ResourceID::Texture;
    mTextures.setAssets
    ({
        TextureList::Asset(ID::MenuStateBg, "textures/menustate_bg_placeholder.png"),
    });

    mTextures.load();

    mBackground.setTexture(Assets::get(ID::MenuStateBg));
}

////////////////////////////////////////////////

void MenuState::draw()
{
    mWindow.draw(mBackground);
}

////////////////////////////////////////////////

bool MenuState::update()
{
	return true;
}

////////////////////////////////////////////////

bool MenuState::handleEvent(const sf::Event& event)
{
	// Escape pressed, trigger the pause screen
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    {
        requestStackPop();
		requestStackPush(new GameState(getStack(), mWindow));
    }

	return true;
}
