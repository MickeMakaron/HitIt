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
// C Standard library
#include <dirent.h>
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "TrackMenu.hpp"
#include "Button.hpp"
#include "GameState.hpp"
#include "Text.hpp"
#include "MainMenu.hpp"
#include "MenuThemeState.hpp"
////////////////////////////////////////////////


TrackMenu::TrackMenu(StateStack& stack, sf::RenderTarget& target)
: MenuState(stack, target)
{
    sf::Text text;
    text.setFont(Assets::get(ResourceID::Font::OldGateLaneNF));
    text.setCharacterSize(150);
    text.setString("Pick a track");

    mMenu.insert(new Text(text));
    mMenu.insert(getButtons());

    mTextures.insert(getTextures());

    sf::Color gray(100, 100, 100);
    setBackground(gray);

    mMenu.setPosition(target.getView().getSize().x / 2.f, target.getView().getSize().y / 3.f);
}

std::list<GUIElement*> TrackMenu::getButtons()
{
    sf::Text buttonText;
    buttonText.setCharacterSize(30);
    buttonText.setFont(Assets::get(ResourceID::Font::Arial));
    buttonText.setString("A");

    DIR* dir = opendir("assets/midi");
    // Skip ".." and ".".
    readdir(dir);
    readdir(dir);

    std::string directory = dir->dd_name;
    directory.erase(directory.end() - 1);
    sf::FloatRect titleRect = mMenu.getGlobalBounds();
    sf::Vector2f pos(titleRect.width / 16.f, titleRect.height * 1.75f);
    std::list<GUIElement*> buttons;
    float yIncrement = buttonText.getGlobalBounds().height * 1.25f;
    dirent* entry = readdir(dir);
    while(entry != NULL)
    {
        // This is used for display.
        std::string fileName = entry->d_name;

        // Remove file extension from file name.
        fileName.resize(fileName.find_last_of('.'));

        // This is used for reading the file.
        std::string filePath = directory + entry->d_name;
        buttonText.setString(fileName);
        Button* button = new Button
        (
            buttonText,
            mSoundPlayer,
            [=](){requestStackClear(); requestStackPush(new GameState(getStack(), mTarget, filePath));}
        );
        button->setOrigin(0.f, 0.f);
        button->setPosition(pos);
        pos.y += yIncrement;
        buttons.push_back(button);
        entry = readdir(dir);
    }
    closedir(dir);

    buttonText.setCharacterSize(75);
    buttonText.setFont(Assets::get(ResourceID::Font::OldGateLaneNF));
    buttonText.setString("Go to main menu");
    Button* mainMenu = new Button
    (
        buttonText,
        mSoundPlayer,
        [this]()
        {
            requestStackPop();
            requestStackPush(new MenuThemeState(getStack(), mTarget));
            requestStackPush(new MainMenu(getStack(), mTarget));
        }
    );
    pos.x = titleRect.width / 2.f;
    pos.y += yIncrement * 2.f;
    mainMenu->setPosition(pos);
    buttons.push_back(mainMenu);

    return buttons;
}

std::list<TextureList::Asset> TrackMenu::getTextures() const
{
    namespace ID = ResourceID::Texture;
    return
    {
        TextureList::Asset(ID::MenuStateBg, "textures/menustate_bg_placeholder.png"),
    };
}
