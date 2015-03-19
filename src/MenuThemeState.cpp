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
#include "MenuThemeState.hpp"
#include "Spawner.hpp"
#include "VertexArrayNode.hpp"
////////////////////////////////////////////////


MenuThemeState::MenuThemeState(StateStack& stack, sf::RenderTarget& target)
: State(stack)
, mTarget(target)
, mSpawner1(new Spawner(M_THEME_FILE_PATH, mSampler, sf::FloatRect(sf::Vector2f(0.f, 0.f), mTarget.getView().getSize()), &mNotes))
, mSpawner2(nullptr)
, mBackground(mTarget.getView().getSize())
{
    loadAssets();
    mSampler.setVolume(60.f);

    Assets::get(ResourceID::Texture::MenuStateBg).setRepeated(true);
    mBackground.setTexture(&Assets::get(ResourceID::Texture::MenuStateBg));
    mBackground.setTextureRect(sf::IntRect(0, 0, mTarget.getView().getSize().x, mTarget.getView().getSize().y));
}

////////////////////////////////////////////////

MenuThemeState::~MenuThemeState()
{
    if(mSpawner1)
        delete mSpawner1;
    if(mSpawner2)
        delete mSpawner2;
}

void MenuThemeState::draw()
{
    mTarget.draw(mBackground);
    mTarget.draw(mNotes);
}

bool MenuThemeState::update()
{
    mNotes.update();

    mSpawner1->update();
    mSpawner1->spawn();

    if(mSpawner2)
    {
        mSpawner2->update();
        mSpawner2->spawn();
    }

    mNotes.removeWrecks();


    if(mSpawner2)
    {
        if(mSpawner1->getObstacles().getSize() == 0)
        {
            mSampler.pause();
            delete mSpawner1;
            mSampler.resume();

            mSpawner1 = mSpawner2;

            mSpawner2 = nullptr;
        }
    }
    else if(mSpawner1->isEmpty())
    {
        mSpawner2 = new Spawner(M_THEME_FILE_PATH, mSampler, sf::FloatRect(sf::Vector2f(0.f, 0.f), mTarget.getView().getSize()), &mNotes);
    }

    return true;
}

bool MenuThemeState::handleEvent(const sf::Event& event)
{
    return true;
}

void MenuThemeState::loadAssets()
{
    mTextures.insert({TextureList::Asset(ResourceID::Texture::MenuStateBg, "textures/menu_bg.png")});
}
