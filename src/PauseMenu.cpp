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
#include "PauseMenu.hpp"
#include "Button.hpp"
#include "GameState.hpp"
#include "MainMenu.hpp"
#include "MenuThemeState.hpp"
#include "Text.hpp"
////////////////////////////////////////////////


PauseMenu::PauseMenu(StateStack& stack, sf::RenderTarget& target, GameState& game)
: MenuState(stack, target)
, mGame(game)
{
    sf::Text text;
    text.setFont(Assets::get(ResourceID::Font::OldGateLaneNF));
    text.setCharacterSize(230);
    text.setString("Paused");

    mMenu.insert(new Text(text));
    mMenu.insert(getButtons());
    mMenu.setPosition(target.getView().getSize().x / 2.f, target.getView().getSize().y / 3.f);

    mGame.pause();

    sf::Color background = sf::Color::Black;
    background.a = 120;
    setBackground(background);

    mMenu.setBackground(sf::Color(200, 200, 200, 100), sf::Color(240, 240, 240, 150), 3.f);
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
    sf::Text buttonText;
    buttonText.setCharacterSize(80);
    buttonText.setFont(Assets::get(ResourceID::Font::OldGateLaneNF));

    buttonText.setString("Resume");
    Button* resume = new Button
    (
        buttonText,
        mSoundPlayer,
        [this](){requestStackPop(); mGame.resume();}
    );

    buttonText.setString("Quit to main menu");
    Button* exit = new Button
    (
        buttonText,
        mSoundPlayer,
        [this]()
        {
            requestStackClear();
            requestStackPush(new MenuThemeState(getStack(), mTarget));
            requestStackPush(new MainMenu(getStack(), mTarget));
        }
    );


    sf::FloatRect titleRect = mMenu.getGlobalBounds();
    sf::Vector2f pos(titleRect.width / 2.f, titleRect.height * 2.f);

    float yIncrement = buttonText.getGlobalBounds().height * 1.5f;
    resume->setPosition(pos);
    pos.y += yIncrement;
    exit->setPosition(pos);
    return
    {
        resume,
        exit,
    };
}
