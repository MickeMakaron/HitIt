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
#include "Button.hpp"
////////////////////////////////////////////////


MenuState::MenuState(StateStack& stack, sf::RenderWindow& window)
: State(stack)
, mWindow(window)
, mTextures(getTextures(), true)
, mSounds(getSounds(), true)
, mSoundPlayer(Assets::get(ResourceID::Sound::Button))
, mMenu(getButtons())
{
    mBackground.setTexture(Assets::get(ResourceID::Texture::MenuStateBg));
}

////////////////////////////////////////////////

void MenuState::draw()
{
    mWindow.draw(mBackground);
    mMenu.draw(mWindow);
}

////////////////////////////////////////////////

bool MenuState::update()
{
    mMenu.update();
	return true;
}

////////////////////////////////////////////////

bool MenuState::handleEvent(const sf::Event& event)
{
    mMenu.handleEvent(event);

	// Escape pressed, trigger the pause screen
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    {
        requestStackPop();
		requestStackPush(new GameState(getStack(), mWindow));
    }

	return true;
}

#include <iostream>
std::list<GUIElement*> MenuState::getButtons()
{
    namespace Tex = ResourceID::Texture;
    namespace Font = ResourceID::Font;
    sf::Vector2f pos = mWindow.getView().getSize() / 2.f;
    pos.x -= Assets::get(Tex::Button).getSize().x / 2.f;

    auto playButtonClickFunc = [&](){mSoundPlayer.play();};
    Button* play = new Button
    (
        Assets::get(Tex::Button),
        sf::Text("Derp", Assets::get(Font::OldGateLaneNF)),
        mSoundPlayer,
        [this](){requestStackPop(); requestStackPush(new GameState(getStack(), mWindow));}
    );

    Button* about = new Button
    (
        Assets::get(Tex::Button),
        sf::Text("Derp", Assets::get(Font::OldGateLaneNF)),
        mSoundPlayer,
        [this](){requestStackPop(); requestStackPush(new GameState(getStack(), mWindow));}
    );
    Button* exit = new Button
    (
        Assets::get(Tex::Button),
        sf::Text("Derp", Assets::get(Font::OldGateLaneNF)),
        mSoundPlayer,
        [this](){requestStackClear();}
    );

    play->setPosition(pos);
    pos.y += 50.f;

    about->setPosition(pos);
    pos.y += 50.f;

    exit->setPosition(pos);
    return
    {
        play,
        about,
        exit,
    };
}

std::list<TextureList::Asset> MenuState::getTextures() const
{
    namespace ID = ResourceID::Texture;
    return
    {
        TextureList::Asset(ID::MenuStateBg, "textures/menustate_bg_placeholder.png"),
        TextureList::Asset(ID::Button, "textures/button_placeholder.png"),
    };
}

std::list<SoundList::Asset> MenuState::getSounds() const
{
    namespace ID = ResourceID::Sound;
    return
    {
        SoundList::Asset(ID::Button, "sounds/button_placeholder.ogg"),
    };
}
