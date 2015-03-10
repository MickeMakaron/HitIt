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
#include "GameState.hpp"
////////////////////////////////////////////////


MainMenu::MainMenu(StateStack& stack, sf::RenderTarget& target)
: MenuState(stack, target)
{
    setElements(getButtons());
    mTextures.insert(getTextures());
    setBackground(Assets::get(ResourceID::Texture::MenuStateBg));


}

std::list<GUIElement*> MainMenu::getButtons()
{
    namespace Tex = ResourceID::Texture;
    namespace Font = ResourceID::Font;
    sf::Vector2f pos = mTarget.getView().getSize() / 2.f;
    pos.x -= Assets::get(Tex::Button).getSize().x / 2.f;

    Button* play = new Button
    (
        Assets::get(Tex::Button),
        sf::Text("Play", Assets::get(Font::OldGateLaneNF)),
        mSoundPlayer,
        [this](){requestStackPop(); requestStackPush(new GameState(getStack(), mTarget));}
    );

    Button* about = new Button
    (
        Assets::get(Tex::Button),
        sf::Text("About", Assets::get(Font::OldGateLaneNF)),
        mSoundPlayer,
        [this](){requestStackPop(); requestStackPush(new GameState(getStack(), mTarget));}
    );
    Button* exit = new Button
    (
        Assets::get(Tex::Button),
        sf::Text("Exit", Assets::get(Font::OldGateLaneNF)),
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

std::list<TextureList::Asset> MainMenu::getTextures() const
{
    namespace ID = ResourceID::Texture;
    return
    {
        TextureList::Asset(ID::MenuStateBg, "textures/menustate_bg_placeholder.png"),
    };
}
