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
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/System/Vector2.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "World.hpp"
#include "Assets.hpp"
#include "TIME_PER_FRAME.hpp"
#include "Player.hpp"
#include "CollissionCategory.hpp"
#include "Midi.hpp"
#include "HealthBar.hpp"
#include "ScoreDisplay.hpp"
#include "BonusStrip.hpp"
////////////////////////////////////////////////


World::World(sf::RenderTarget& target, std::string midiFile)
: mTarget(target)
, mTextures(getTextures())
, mSounds(getSounds())
, mSampler()
, mBounds(0.f, 0.f, mTarget.getView().getSize().x, mTarget.getView().getSize().y)
, mSpawner(std::string(midiFile), mSampler, mBounds, mScene.getLayer(SceneGraph::Layer::Middle))
, mPlayer(new Player(Assets::get(ResourceID::Texture::Player), mSpawner.getNoteWidth(), 5))
, mBonusStrip(*(new BonusStrip(mSpawner.getObstacles(), sf::Vector2f(mBounds.width, mBounds.height), mSpawner.getNoteWidth())))
, mScoreDisplay(nullptr)
, mCollission(*mPlayer, mBonusStrip)
, mState(Starting)
, mTimer(0.f)
, mPlayerIsDamaged(false)
, mStateFuncs(StateCount, [](){})
{
    mPlayer->setPosition(sf::Vector2f(mBounds.left + 1.f + mSpawner.getNoteWidth() * (int)((mBounds.width / 2.f)/ mSpawner.getNoteWidth()), mBounds.height / 2.f));

    buildWorld();

    mStateFuncs[Starting]   = [this](){updateStart();};
    mStateFuncs[Running]    = [this](){updateRun();};
    mStateFuncs[Victory]    = [this](){updateVictory();};
}

World::~World()
{
    mScene.clear();
}


////////////////////////////////////////////////

void World::draw()
{
    mScene.draw(mTarget);
}

////////////////////////////////////////////////

void World::update()
{
    mScene.update();
    mCollission.update();
    keepPlayerInBounds();

    if(mPlayerIsDamaged)
    {
        if(!mPlayer->isDamaged())
        {
            mPlayerIsDamaged = false;
            mSampler.setVolume(100.f);
        }

    }
    else if(mPlayer->isDamaged())
    {
        mPlayerIsDamaged = true;
        mSampler.setVolume(30.f);
    }


    mStateFuncs[mState]();

    mCollission.removeWrecks();
    mScene.removeWrecks();
}

void World::updateStart()
{
    mTimer += TIME_PER_FRAME::seconds();
    if(mTimer >= 1.f)
    {
        mState = Running;
        mTimer = 0.f;
    }
}

void World::updateRun()
{
    if(mPlayer->isDestroyed())
        mState = Defeat;

    mSpawner.update();

    if(mSpawner.isEmpty())
        mStateFuncs[Victory]();

    for(SceneNode* node : mSpawner.spawn())
        mCollission.insert(node);
}

void World::updateVictory()
{
    mTimer += TIME_PER_FRAME::seconds();

    if(mTimer >= 6.f)
    {
        mState = Victory;
        mTimer = 0.f;
    }
}


////////////////////////////////////////////////

void World::handleEvent(const sf::Event& event)
{
    mScene.handleEvent(event);
}

////////////////////////////////////////////////

void World::buildWorld()
{
    namespace ID = ResourceID::Texture;

    RectangleNode* background = new RectangleNode(mTarget.getView().getSize());
    sf::Color gray(200, 200, 200);
    background->setFillColor(gray);
    mScene.insert(background, SceneGraph::Background);
    mScene.insert(mPlayer, SceneGraph::Middle);

    for(float x = mSpawner.getNoteWidth(); x < mBounds.width; x += mSpawner.getNoteWidth())
    {
        RectangleNode* line = new RectangleNode(sf::Vector2f(1.5f, mBounds.height));
        line->setPosition(mBounds.left + x, 0.f);

        line->setFillColor(sf::Color::Black);
        mScene.insert(line, SceneGraph::Middle);
    }

    RectangleNode* playLine = new RectangleNode(sf::Vector2f(mBounds.width, 2.f));
    playLine->setFillColor(sf::Color::Black);
    playLine->setPosition(0.f, mBounds.height / 3.f);
    mScene.insert(playLine, SceneGraph::High);


    Assets::get(ID::Hp).setRepeated(true);
    HealthBar* hpBar = new HealthBar(Assets::get(ID::Hp), *mPlayer);
    mScene.insert(hpBar, SceneGraph::Foreground);

    sf::Text text;
    text.setCharacterSize(80);
    text.setFont(Assets::get(ResourceID::Font::OldGateLaneNF));
    mScoreDisplay = new ScoreDisplay(text, *mPlayer, mBonusStrip);
    mScoreDisplay->setPosition(10.f, 30.f);
    mScene.insert(mScoreDisplay, SceneGraph::Foreground);

    mScene.insert(&mBonusStrip, SceneGraph::Layer::Background);
}

void World::keepPlayerInBounds()
{
    sf::FloatRect playerRect = mPlayer->getBoundingRect();
    if(playerRect.top < mBounds.top)
        mPlayer->move(0.f, -playerRect.top);
    else if(playerRect.top + playerRect.height > mBounds.height)
        mPlayer->move(0.f,  mBounds.height - (playerRect.top + playerRect.height));

    if(playerRect.left < mBounds.left)
        mPlayer->move(mSpawner.getNoteWidth(), 0.f);
    else if(playerRect.left + playerRect.width > mBounds.width)
        mPlayer->move(-mSpawner.getNoteWidth(), 0.f);
}

std::list<TextureList::Asset> World::getTextures() const
{
    namespace ID = ResourceID::Texture;
    return
    {
        TextureList::Asset(ID::GameStateBg,     "textures/gamestate_bg_placeholder.png"),
        TextureList::Asset(ID::Player,          "textures/player_placeholder.png"),
        TextureList::Asset(ID::AudienceTerrace, "textures/audience_terrace_placeholder.png"),
        TextureList::Asset(ID::Fence,           "textures/fence_placeholder.png"),
        TextureList::Asset(ID::WorldBg,         "textures/world_bg_placeholder.png"),
        TextureList::Asset(ID::Hp,              "textures/hp_placeholder.png"),
    };
}

std::list<SoundList::Asset> World::getSounds() const
{
    namespace ID = ResourceID::Sound;
    return
    {
        SoundList::Asset(ID::PlayerDamaged,     "sounds/player_damaged.ogg"),
        SoundList::Asset(ID::PlayerStep,        "sounds/player_step.ogg"),
        SoundList::Asset(ID::PickupPoint,       "sounds/pickup_point.ogg"),
        SoundList::Asset(ID::Bonus1,            "sounds/bonus1.ogg"),
        SoundList::Asset(ID::Bonus2,            "sounds/bonus2.ogg"),
    };
}

World::State World::getState() const
{
    return mState;
}

void World::pause()
{
    mSampler.pause();
    mState = Paused;
}

void World::resume()
{
    mSampler.resume();
    mState = Running;
}

unsigned int World::getScore() const
{
    if(mScoreDisplay)
        return mScoreDisplay->getScore();
    else
        return 0;
}

