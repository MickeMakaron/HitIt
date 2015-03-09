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
#include "VictoryMenu.hpp"
#include "GameState.hpp"
#include "MainMenu.hpp"
#include "Button.hpp"
////////////////////////////////////////////////


VictoryMenu::VictoryMenu(StateStack& stack, sf::RenderWindow& window)
: MenuState(stack, window)
{
    setElements(getButtons());

    sf::Color background = sf::Color::Black;
    background.a = 120;
    setBackground(background);
}

bool VictoryMenu::handleEvent(const sf::Event& event)
{
    MenuState::handleEvent(event);
    return false;
}


std::list<GUIElement*> VictoryMenu::getButtons()
{
    namespace Tex = ResourceID::Texture;
    namespace Font = ResourceID::Font;
    sf::Vector2f pos = mWindow.getView().getSize() / 2.f;
    pos.x -= Assets::get(Tex::Button).getSize().x / 2.f;

    Button* playSame = new Button
    (
        Assets::get(Tex::Button),
        sf::Text("Play again", Assets::get(Font::OldGateLaneNF)),
        mSoundPlayer,
        [this](){requestStackClear(); requestStackPush(new GameState(getStack(), mWindow));}
    );

    Button* playOther = new Button
    {
        Assets::get(Tex::Button),
        sf::Text("Play another track", Assets::get(Font::OldGateLaneNF)),
        mSoundPlayer,
        [this](){requestStackClear(); requestStackPush(new MainMenu(getStack(), mWindow));}
    };

    Button* mainMenu = new Button
    (
        Assets::get(Tex::Button),
        sf::Text("Go to main menu", Assets::get(Font::OldGateLaneNF)),
        mSoundPlayer,
        [this](){requestStackClear(); requestStackPush(new MainMenu(getStack(), mWindow));}
    );


    playSame->setPosition(pos);

    pos.y += 50.f;
    playOther->setPosition(pos);

    pos.y += 50.f;
    mainMenu->setPosition(pos);

    return
    {
        playSame,
        playOther,
        mainMenu,
    };
}


