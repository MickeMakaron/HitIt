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
#include "MenuState.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Graphics/RenderTarget.hpp"
////////////////////////////////////////////////

MenuState::MenuState(StateStack& stack, sf::RenderTarget& target)
: State(stack)
, mTarget(target)
, mBackground(mTarget.getView().getSize())
{
    loadAssets();
    sf::Text text;
    mWaterMark.setString("© 2015 Mikael Hernvall");
    mWaterMark.setFont(Assets::get(ResourceID::Font::ID::OldGateLaneNF));
    mWaterMark.setColor(sf::Color(0, 0, 0, 150));

    sf::FloatRect waterMarkRect = mWaterMark.getGlobalBounds();
    mWaterMark.setPosition(target.getView().getSize().x - waterMarkRect.width * 1.1f, target.getView().getSize().y - waterMarkRect.height * 1.5f);
}

////////////////////////////////////////////////

void MenuState::draw()
{
    mTarget.draw(mBackground);
    mTarget.draw(mMenu);
    mTarget.draw(mWaterMark);
}

////////////////////////////////////////////////

bool MenuState::update()
{
    mMenu.update();
	return false;
}

////////////////////////////////////////////////

bool MenuState::handleEvent(const sf::Event& event)
{
    mMenu.handleEvent(event);
	return false;
}

////////////////////////////////////////////////

void MenuState::setBackground(const sf::Texture& background)
{
    mBackground.setTexture(&background);
}

////////////////////////////////////////////////

void MenuState::setBackground(sf::Color color)
{
    mBackground.setFillColor(color);
}

////////////////////////////////////////////////

void MenuState::loadAssets()
{
    using namespace ResourceID;
    mTextures.insert
    ({
        TextureList::Asset(Texture::MenuStateBg,     "textures/menu_bg.png"),
        TextureList::Asset(Texture::About,           "textures/about.png"),
    });

    mSounds.insert
    ({
        SoundList::Asset(Sound::Button, "sounds/button_placeholder.ogg"),
        SoundList::Asset(Sound::Defeat, "sounds/defeat.ogg"),
    });

    mFonts.insert
    ({
        FontList::Asset(Font::OldGateLaneNF,    "fonts/OldGateLaneNF.ttf"),
        FontList::Asset(Font::Arial,            "fonts/arial.ttf"),
     });
}
