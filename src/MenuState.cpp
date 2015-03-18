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
#include "MenuState.hpp"
#include "GameState.hpp"
#include "Button.hpp"
////////////////////////////////////////////////


MenuState::MenuState(StateStack& stack, sf::RenderTarget& target, std::list<GUIElement*> elements)
: State(stack)
, mTarget(target)
, mTextures(getTextures())
, mSounds(getSounds())
, mSoundPlayer(Assets::get(ResourceID::Sound::Button))
, mMenu(elements)
, mBackground(mTarget.getView().getSize())
{
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

void MenuState::setBackground(const sf::Texture& background)
{
    mBackground.setTexture(&background);
}

void MenuState::setBackground(sf::Color color)
{
    mBackground.setFillColor(color);
}

std::list<TextureList::Asset> MenuState::getTextures() const
{
    namespace ID = ResourceID::Texture;
    return
    {
        TextureList::Asset(ID::MenuStateBg,  "textures/menu_bg.png"),
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
