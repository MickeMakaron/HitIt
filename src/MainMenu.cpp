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
#include "MainMenu.hpp"
#include "Button.hpp"
#include "TrackMenu.hpp"
#include "Text.hpp"
////////////////////////////////////////////////

MainMenu::MainMenu(StateStack& stack, sf::RenderTarget& target)
: MenuState(stack, target)
{
    sf::Text text;
    text.setFont(Assets::get(ResourceID::Font::OldGateLaneNF));
    text.setCharacterSize(350);
    text.setString("Hit it!");

    mMenu.insert(new Text(text));
    mMenu.insert(getButtons());

    mTextures.insert(getTextures());

    sf::Color gray(100, 100, 100);
    setBackground(gray);

    mMenu.setPosition(target.getView().getSize().x / 2.f, target.getView().getSize().y / 3.f);
}

std::list<GUIElement*> MainMenu::getButtons()
{
    sf::Text buttonText;
    buttonText.setCharacterSize(100);
    buttonText.setFont(Assets::get(ResourceID::Font::OldGateLaneNF));

    buttonText.setString("Play");
    Button* play = new Button
    (
        buttonText,
        mSoundPlayer,
        [this](){requestStackPop(); requestStackPush(new TrackMenu(getStack(), mTarget));}
    );

    buttonText.setString("About");
    Button* about = new Button
    (
        buttonText,
        mSoundPlayer,
        [this](){requestStackPop(); requestStackPush(new TrackMenu(getStack(), mTarget));}
    );

    buttonText.setString("Exit");
    Button* exit = new Button
    (
        buttonText,
        mSoundPlayer,
        [this](){requestStackClear();}
    );


    sf::FloatRect titleRect = mMenu.getGlobalBounds();
    sf::Vector2f pos(titleRect.width / 2.f, titleRect.height * 1.75f);

    float yIncrement = buttonText.getGlobalBounds().height * 1.25f;
    play->setPosition(pos);
    pos.y += yIncrement;

    about->setPosition(pos);
    pos.y += yIncrement;

    exit->setPosition(pos);
    return
    {
        play,
        about,
        exit,
    };
}

std::list<TextureList::Asset> MainMenu::getTextures() const
{
    namespace ID = ResourceID::Texture;
    return
    {
        TextureList::Asset(ID::MenuStateBg, "textures/menustate_bg_placeholder.png"),
    };
}
