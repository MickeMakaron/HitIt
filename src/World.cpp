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
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "World.hpp"
#include "Assets.hpp"
#include "TIME_PER_FRAME.hpp"
#include "SpriteNode.hpp"
#include "Player.hpp"
////////////////////////////////////////////////

World::World(sf::RenderWindow& window)
: mWindow(window)
, mPlayer(nullptr)
{
    buildWorld();
}

////////////////////////////////////////////////

void World::draw()
{
    mScene.draw(mWindow);
}

////////////////////////////////////////////////

void World::update()
{
    mScene.update();
    mCollission.update();
}

////////////////////////////////////////////////

void World::handleEvent(const sf::Event& event)
{

}

////////////////////////////////////////////////

void World::buildWorld()
{
    namespace ID = ResourceID::Texture;
    mTextures.setAssets
    ({
        TextureList::Asset(ID::GameStateBg, "textures/gamestate_bg_placeholder.png"),
        TextureList::Asset(ID::Player, "textures/player_placeholder.png"),
    });
    mTextures.load();

    mScene.insert(new SpriteNode(Assets::get(ID::GameStateBg)), SceneGraph::Background);

    mPlayer = new Player(Assets::get(ID::Player), 5, sf::Vector2f(500.f, 500.f));

    mScene.insert(mPlayer, SceneGraph::Middle);
    mCollission.setPlayer(mPlayer);

    SpriteNode* obstacle = new SpriteNode(Assets::get(ID::Player));
    obstacle->setPosition(400.f, 400.f);
    mScene.insert(obstacle, SceneGraph::Middle);

    mCollission.insert(obstacle);



}
