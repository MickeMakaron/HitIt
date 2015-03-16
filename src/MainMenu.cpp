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
#include "Spawner.hpp"
#include "AudioSampler.hpp"
#include "VertexArrayNode.hpp"
////////////////////////////////////////////////

MainMenu::MainMenu(StateStack& stack, sf::RenderTarget& target)
: MenuState(stack, target)
, mTheme("assets/midi/damp.mid")
, mSampler1(new AudioSampler())
, mSampler2(nullptr)
, mSpawner1(new Spawner(mTheme, *mSampler1, sf::FloatRect(sf::Vector2f(0.f, 0.f), mTarget.getView().getSize()), &mNotes))
, mSpawner2(nullptr)
, mCurrentMenu(&mMenu)
, mAboutMenu({})
{
    mSampler1->setVolume(60.f);

    sf::Text text;
    text.setFont(Assets::get(ResourceID::Font::OldGateLaneNF));
    text.setCharacterSize(350);
    text.setString("Hit it!");

    mMenu.insert(new Text(text));
    mMenu.insert(getButtons());

    mTextures.insert(getTextures());
    mAbout.setTexture((Assets::get(ResourceID::Texture::About)));
    mAbout.setPosition(0.f, mTarget.getView().getSize().y / 5.f);

    sf::Color gray(100, 100, 100);
    setBackground(gray);

    mMenu.setPosition(target.getView().getSize().x / 2.f, target.getView().getSize().y / 3.f);

    text.setCharacterSize(100);
    text.setString("Ok!");
    Button* ok = new Button(text, mSoundPlayer, [this](){mCurrentMenu = &mMenu;});
    mAboutMenu.setPosition(mTarget.getView().getSize().x / 2.f, mTarget.getView().getSize().y * 2.f / 3.f);
    mAboutMenu.insert(ok);
}

MainMenu::~MainMenu()
{
    if(mSampler1)
        delete mSampler1;
    if(mSampler2)
        delete mSampler2;
    if(mSpawner1)
        delete mSpawner1;
    if(mSpawner2)
        delete mSpawner2;
}

bool MainMenu::handleEvent(const sf::Event& event)
{
    mCurrentMenu->handleEvent(event);
}

void MainMenu::draw()
{
    mTarget.draw(mBackground);
    mTarget.draw(mNotes);
    mTarget.draw(*mCurrentMenu);

    if(mCurrentMenu == &mAboutMenu)
        mTarget.draw(mAbout);
}

bool MainMenu::update()
{
    mCurrentMenu->update();
    mNotes.update();

    mSpawner1->update();
    mSpawner1->spawn();


    if(mSpawner2 && mSampler2)
    {
        mSpawner2->update();
        mSpawner2->spawn();
    }

    mNotes.removeWrecks();


    if(mSpawner2)
    {
        if(mSpawner1->getObstacles().getSize() == 0)
        {
            delete mSpawner1;
            delete mSampler1;

            mSpawner1 = mSpawner2;
            mSampler1 = mSampler2;

            mSpawner2 = nullptr;
            mSampler2 = nullptr;
        }
    }
    else if(mSpawner1->isEmpty())
    {
        mSampler2 = new AudioSampler();
        mSpawner2 = new Spawner(mTheme, *mSampler2, sf::FloatRect(sf::Vector2f(0.f, 0.f), mTarget.getView().getSize()), &mNotes);
        mSampler2->setVolume(60.f);
    }

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
        [this](){mCurrentMenu = &mAboutMenu;}
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
        TextureList::Asset(ID::About,       "textures/about.png"),
    };
}
