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
#include "Text.hpp"
////////////////////////////////////////////////


DefeatMenu::DefeatMenu(StateStack& stack, sf::RenderTarget& target)
: MenuState(stack, target)
{
    mSounds.insert({SoundList::Asset(ResourceID::Sound::Defeat, "sounds/defeat.ogg")});
    mTaunt.setBuffer(Assets::get(ResourceID::Sound::Defeat));
    mTaunt.play();

    sf::Text text;
    text.setFont(Assets::get(ResourceID::Font::OldGateLaneNF));
    text.setCharacterSize(300);
    text.setString("Dangit!");

    mMenu.insert(new Text(text));
    mMenu.insert(getButtons());
    mMenu.setPosition(target.getView().getSize().x / 2.f, target.getView().getSize().y / 3.f);

    sf::Color background = sf::Color::Black;
    background.a = 120;
    setBackground(background);
}

bool DefeatMenu::handleEvent(const sf::Event& event)
{
    MenuState::handleEvent(event);
    return false;
}

std::list<GUIElement*> DefeatMenu::getButtons()
{
    sf::Text buttonText;
    buttonText.setCharacterSize(100);
    buttonText.setFont(Assets::get(ResourceID::Font::OldGateLaneNF));

    buttonText.setString("Try again");
    Button* tryAgain = new Button
    (
        buttonText,
        mSoundPlayer,
        [this](){requestStackClear(); requestStackPush(new GameState(getStack(), mTarget));}
    );

    buttonText.setString("Try another track");
    Button* tryAnother = new Button
    {
        buttonText,
        mSoundPlayer,
        [this](){requestStackClear(); requestStackPush(new MainMenu(getStack(), mTarget));}
    };

    buttonText.setString("Go to main menu");
    Button* mainMenu = new Button
    (
        buttonText,
        mSoundPlayer,
        [this](){requestStackClear(); requestStackPush(new MainMenu(getStack(), mTarget));}
    );


    sf::FloatRect titleRect = mMenu.getGlobalBounds();
    sf::Vector2f pos(titleRect.width / 2.f, titleRect.height * 2.f);

    float yIncrement = buttonText.getGlobalBounds().height * 1.5f;
    tryAgain->setPosition(pos);
    pos.y += yIncrement;
    tryAnother->setPosition(pos);
    pos.y += yIncrement;
    mainMenu->setPosition(pos);

    return
    {
        tryAgain,
        tryAnother,
        mainMenu,
    };
}
