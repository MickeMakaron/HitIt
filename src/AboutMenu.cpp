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
#include "AboutMenu.hpp"
#include "Button.hpp"
#include "MainMenu.hpp"
#include "Text.hpp"
////////////////////////////////////////////////

AboutMenu::AboutMenu(StateStack& stack, sf::RenderTarget& target)
: MenuState(stack, target)
{
    Assets::get(ResourceID::Texture::About).setSmooth(true);
    mAbout.setTexture(Assets::get(ResourceID::Texture::About));

    mAbout.setOrigin(mAbout.getGlobalBounds().width / 2.f, mAbout.getGlobalBounds().height / 2.f);
    mAbout.setPosition(mTarget.getView().getSize() / 2.f);

    mAbout.setScale(0.8f, 0.8f);
    setBackground(sf::Color::Transparent);

    loadButtons();

    mGUIBackground.setFillColor(sf::Color(100, 100, 100, 100));
    mGUIBackground.setOutlineColor(sf::Color(240, 240, 240, 150));
    mGUIBackground.setOutlineThickness(3.f);

    sf::FloatRect guiRect = mAbout.getGlobalBounds();
    mGUIBackground.setSize(sf::Vector2f(guiRect.width, guiRect.height) * 1.1f);
    mGUIBackground.setPosition(sf::Vector2f(guiRect.left, guiRect.top) - sf::Vector2f(guiRect.width, guiRect.height) * 0.05f);

}

void AboutMenu::draw()
{

    mTarget.draw(mGUIBackground);
    mTarget.draw(mAbout);
    MenuState::draw();
}

bool AboutMenu::update()
{
    MenuState::update();
    return true;
}

void AboutMenu::loadButtons()
{
    sf::Text text;
    text.setFont(Assets::get(ResourceID::Font::OldGateLaneNF));
    text.setCharacterSize(100);
    text.setString("Ok!");

    Button* ok = new Button(text, Assets::get(ResourceID::Sound::Button), [this](){requestStackPop(); requestStackPush(new MainMenu(getStack(), mTarget));});
    ok->setOrigin(0, ok->getBoundingRect().height / 2.f);
    ok->setPosition(mTarget.getView().getSize().x / 2.f, mTarget.getView().getSize().y * 2.f / 3.f);
    mMenu.insert(ok);
}
