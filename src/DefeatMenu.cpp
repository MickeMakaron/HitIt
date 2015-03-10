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
#include "DefeatMenu.hpp"
#include "MainMenu.hpp"
#include "GameState.hpp"
#include "Button.hpp"
////////////////////////////////////////////////


DefeatMenu::DefeatMenu(StateStack& stack, sf::RenderTarget& target)
: MenuState(stack, target)
{
    setElements(getButtons());

    sf::Color background = sf::Color::Black;
    background.a = 200;
    setBackground(background);
}

bool DefeatMenu::handleEvent(const sf::Event& event)
{
    MenuState::handleEvent(event);
    return false;
}

std::list<GUIElement*> DefeatMenu::getButtons()
{
    namespace Tex = ResourceID::Texture;
    namespace Font = ResourceID::Font;
    sf::Vector2f pos = mTarget.getView().getSize() / 2.f;
    pos.x -= Assets::get(Tex::Button).getSize().x / 2.f;

    Button* tryAgain = new Button
    (
        Assets::get(Tex::Button),
        sf::Text("Try again", Assets::get(Font::OldGateLaneNF)),
        mSoundPlayer,
        [this](){requestStackClear(); requestStackPush(new GameState(getStack(), mTarget));}
    );

    Button* tryAnother = new Button
    (
        Assets::get(Tex::Button),
        sf::Text("Try another track", Assets::get(Font::OldGateLaneNF)),
        mSoundPlayer,
        [this](){requestStackClear(); requestStackPush(new MainMenu(getStack(), mTarget));}
    );
    Button* mainMenu = new Button
    (
        Assets::get(Tex::Button),
        sf::Text("Go to main menu", Assets::get(Font::OldGateLaneNF)),
        mSoundPlayer,
        [this](){requestStackClear(); requestStackPush(new MainMenu(getStack(), mTarget));}
    );

    tryAgain->setPosition(pos);
    pos.y += 50.f;

    tryAnother->setPosition(pos);
    pos.y += 50.f;

    mainMenu->setPosition(pos);
    return
    {
        tryAgain,
        tryAnother,
        mainMenu,
    };
}
