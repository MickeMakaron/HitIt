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
// HitIt internal headers
#include "VictoryMenu.hpp"
#include "GameState.hpp"
#include "MainMenu.hpp"
#include "Button.hpp"
#include "Text.hpp"
#include "TrackMenu.hpp"
#include "MenuThemeState.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Graphics/RenderTarget.hpp"
////////////////////////////////////////////////

VictoryMenu::VictoryMenu(StateStack& stack, sf::RenderTarget& target, const std::string& midiFile)
: MenuState(stack, target)
, mMidiFile(midiFile)
{
    sf::Text text;
    text.setFont(Assets::get(ResourceID::Font::OldGateLaneNF));
    text.setCharacterSize(230);
    text.setString("Woohoo!");

    mMenu.insert(new Text(text));
    loadButtons();
    mMenu.setPosition(target.getView().getSize().x / 2.f, target.getView().getSize().y / 3.f);

    sf::Color background = sf::Color::Black;
    background.a = 120;
    setBackground(background);

    mMenu.setBackground(sf::Color(200, 200, 200, 100), sf::Color(240, 240, 240, 150), 3.f);
}

////////////////////////////////////////////////

void VictoryMenu::loadButtons()
{
    sf::Text buttonText;
    buttonText.setCharacterSize(80);
    buttonText.setFont(Assets::get(ResourceID::Font::OldGateLaneNF));

    buttonText.setString("Play again");
    Button* playSame = new Button
    (
        buttonText,
        Assets::get(ResourceID::Sound::Button),
        [this]()
        {
            requestStackClear();
            requestStackPush(new GameState(getStack(), mTarget, mMidiFile));
        }
    );

    buttonText.setString("Play another track");
    Button* playOther = new Button
    {
        buttonText,
        Assets::get(ResourceID::Sound::Button),
        [this]()
        {
            requestStackClear();
            requestStackPush(new MenuThemeState(getStack(), mTarget));
            requestStackPush(new TrackMenu(getStack(), mTarget));
        }
    };

    buttonText.setString("Go to main menu");
    Button* mainMenu = new Button
    (
        buttonText,
        Assets::get(ResourceID::Sound::Button),
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
    playSame->setPosition(pos);
    pos.y += yIncrement;
    playOther->setPosition(pos);
    pos.y += yIncrement;
    mainMenu->setPosition(pos);

    mMenu.insert({playSame, playOther, mainMenu});
}
