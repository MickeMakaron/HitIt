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
#include "World.hpp"
#include "Assets.hpp"
#include "TIME_PER_FRAME.hpp"
#include "Player.hpp"
#include "CollissionCategory.hpp"
#include "Collission.hpp"
#include "HealthBar.hpp"
#include "ScoreDisplay.hpp"
#include "BonusStrip.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Graphics/RenderTarget.hpp"
////////////////////////////////////////////////

World::World(sf::RenderTarget& target, std::string midiFile)
: mTarget(target)
, mBounds(0.f, 0.f, mTarget.getView().getSize().x, mTarget.getView().getSize().y)
, mSpawner(std::string(midiFile), mSampler, mBounds, mScene.getLayer(SceneGraph::Layer::Middle))
, mPlayer(nullptr)
, mBonusStrip(nullptr)
, mScoreDisplay(nullptr)
, mCollission(nullptr)
, mState(Starting)
, mTimer(0.f)
, mPlayerIsDamaged(false)
, mStateFuncs(StateCount, [](){})
{
    mStateFuncs[Starting]   = [this](){updateStart();};
    mStateFuncs[Running]    = [this](){updateRun();};
    mStateFuncs[Victory]    = [this](){updateVictory();};
}

////////////////////////////////////////////////

World::~World()
{
    mScene.clear();
    delete mCollission;
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
    mCollission->update();
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

    mCollission->removeWrecks();
    mScene.removeWrecks();
}

////////////////////////////////////////////////

void World::updateStart()
{
    mTimer += TIME_PER_FRAME::seconds();
    if(mTimer >= 1.f)
    {
        mState = Running;
        mTimer = 0.f;
    }
}

////////////////////////////////////////////////

void World::updateRun()
{
    if(mPlayer->isDestroyed())
        mState = Defeat;

    mSpawner.update();

    if(mSpawner.isEmpty())
        mStateFuncs[Victory]();

    for(SceneNode* node : mSpawner.spawn())
        mCollission->insert(node);
}

////////////////////////////////////////////////

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
    RectangleNode* background = new RectangleNode(mTarget.getView().getSize());
    sf::Color gray(200, 200, 200);
    background->setFillColor(gray);
    mScene.insert(background, SceneGraph::Background);

    mPlayer = new Player(Assets::get(ResourceID::Texture::Player), mSpawner.getNoteWidth(), 5);
    mPlayer->setPosition(sf::Vector2f(mBounds.left + 1.f + mSpawner.getNoteWidth() * (int)((mBounds.width / 2.f)/ mSpawner.getNoteWidth()), mBounds.height / 2.f));
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


    namespace ID = ResourceID::Texture;
    Assets::get(ID::Hp).setRepeated(true);
    HealthBar* hpBar = new HealthBar(Assets::get(ID::Hp), *mPlayer);
    mScene.insert(hpBar, SceneGraph::Foreground);


    mBonusStrip = new BonusStrip(mSpawner.getObstacles(), sf::Vector2f(mBounds.width, mBounds.height), mSpawner.getNoteWidth());
    mScene.insert(mBonusStrip, SceneGraph::Layer::Background);

    sf::Text text;
    text.setCharacterSize(80);
    text.setFont(Assets::get(ResourceID::Font::OldGateLaneNF));
    mScoreDisplay = new ScoreDisplay(text, *mPlayer, *mBonusStrip);
    mScoreDisplay->setPosition(10.f, 30.f);
    mScene.insert(mScoreDisplay, SceneGraph::Foreground);

    mCollission = new Collission(*mPlayer, *mBonusStrip);
}

////////////////////////////////////////////////

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

////////////////////////////////////////////////

World::State World::getState() const
{
    return mState;
}

////////////////////////////////////////////////

void World::pause()
{
    mSampler.pause();
    mState = Paused;
}

////////////////////////////////////////////////

void World::resume()
{
    mSampler.resume();
    mState = Running;
}

////////////////////////////////////////////////

unsigned int World::getScore() const
{
    if(mScoreDisplay)
        return mScoreDisplay->getScore();
    else
        return 0;
}
