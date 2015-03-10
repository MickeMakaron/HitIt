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
#include "SpriteNode.hpp"
#include "Player.hpp"
#include "CollissionCategory.hpp"
#include "Midi.hpp"
#include "HealthBar.hpp"
////////////////////////////////////////////////


World::World(sf::RenderTarget& target)
: mTarget(target)
, mView(mTarget.getView())
, mTextures(getTextures())
, mPlayer(new Player(Assets::get(ResourceID::Texture::Player), 10, sf::Vector2f(500.f, 500.f)))
, mCollission(*mPlayer)
, mSpawner(std::string("assets/midi/35468_Circus-Galop.mid"), sf::FloatRect(mView.getSize().x / 5.f, 0.f, 3.f * mView.getSize().x / 5.f, mView.getSize().y))
, mState(Running)
{
    buildWorld();
}

World::~World()
{
    mScene.clear();
}


////////////////////////////////////////////////

void World::draw()
{
    mScene.draw(mTarget);
    mSpawner.draw(mTarget);
}

////////////////////////////////////////////////

void World::update()
{
    mScene.update();
    mCollission.update();
    keepPlayerInBounds();

    mCollission.removeWrecks();
    mScene.removeWrecks();

    mSpawner.update();

    for(SceneNode* node : mSpawner.fetchNewNodes())
    {
        mScene.insert(node, SceneGraph::Layer::Middle);
        mCollission.insert(node);
    }


    if(mPlayer->isDestroyed())
        mState = Defeat;
    else if(mSpawner.isEmpty())
    {
        mState = Victory;
    }
}

////////////////////////////////////////////////

void World::handleEvent(const sf::Event& event)
{

}

////////////////////////////////////////////////

void World::buildWorld()
{
    namespace ID = ResourceID::Texture;

    mScene.insert(new SpriteNode(Assets::get(ID::WorldBg)), SceneGraph::Background);
    mScene.insert(mPlayer, SceneGraph::Middle);


    SpriteNode* props[4] =
    {
        new SpriteNode(Assets::get(ID::AudienceTerrace), CollissionCategory::Collidable),
        new SpriteNode(Assets::get(ID::AudienceTerrace), CollissionCategory::Collidable),
        new SpriteNode(Assets::get(ID::Fence), CollissionCategory::Collidable),
        new SpriteNode(Assets::get(ID::Fence), CollissionCategory::Collidable),
    };

    sf::Vector2f viewSize = mView.getSize();

    // Audience terraces
    sf::FloatRect terraceRect = props[0]->getBoundingRect();
    float terracePositionY = (viewSize.y - terraceRect.height) / 2.f;
    props[0]->setPosition(10.f, terracePositionY);
    props[1]->setPosition(viewSize.x - 10.f - terraceRect.width, terracePositionY);

    // Fence
    sf::FloatRect fenceRect = props[2]->getBoundingRect();
    props[2]->setPosition(15.f + terraceRect.width, 0.f);
    props[3]->setPosition(viewSize.x - 15.f - fenceRect.width - terraceRect.width, 0.f);


    for(SpriteNode* prop : props)
    {
        mScene.insert(prop, SceneGraph::Middle);
        mCollission.insert(prop);
    }

    Assets::get(ID::Hp).setRepeated(true);
    HealthBar* hpBar = new HealthBar(Assets::get(ID::Hp), *mPlayer);
    mScene.insert(hpBar, SceneGraph::Foreground);
}

void World::keepPlayerInBounds()
{
    sf::FloatRect playerRect = mPlayer->getBoundingRect();
    if(playerRect.top < 0.f)
        mPlayer->move(0.f, -playerRect.top);
    else
    {
        float d = mView.getSize().y - (playerRect.top + playerRect.height);
        if(d < 0.f)
            mPlayer->move(0.f, d);
    }
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


World::State World::getState() const
{
    return mState;
}

void World::pause()
{
    mSpawner.pause();
    mState = Paused;
}

void World::resume()
{
    mSpawner.resume();
    mState = Running;
}
