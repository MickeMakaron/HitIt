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
#include "PauseMenu.hpp"
#include "Button.hpp"
#include "GameState.hpp"
#include "MainMenu.hpp"
////////////////////////////////////////////////


PauseMenu::PauseMenu(StateStack& stack, sf::RenderWindow& window, GameState& game)
: MenuState(stack, window)
, mGame(game)
{
    setElements(getButtons());
    mGame.pause();

    sf::Color background = sf::Color::Black;
    background.a = 120;
    setBackground(background);
}


bool PauseMenu::handleEvent(const sf::Event& event)
{
    MenuState::handleEvent(event);

	if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    {
        requestStackPop();
        mGame.resume();
    }

    return false;
}


std::list<GUIElement*> PauseMenu::getButtons()
{
    namespace Tex = ResourceID::Texture;
    namespace Font = ResourceID::Font;
    sf::Vector2f pos = mWindow.getView().getSize() / 2.f;
    pos.x -= Assets::get(Tex::Button).getSize().x / 2.f;

    Button* resume = new Button
    (
        Assets::get(Tex::Button),
        sf::Text("Resume", Assets::get(Font::OldGateLaneNF)),
        mSoundPlayer,
        [this](){requestStackPop();}
    );

    Button* exit = new Button
    (
        Assets::get(Tex::Button),
        sf::Text("Exit", Assets::get(Font::OldGateLaneNF)),
        mSoundPlayer,
        [this](){requestStackClear(); requestStackPush(new MainMenu(getStack(), mWindow));}
    );

    resume->setPosition(pos);
    pos.y += 50.f;
    exit->setPosition(pos);
    return
    {
        resume,
        exit,
    };
}
