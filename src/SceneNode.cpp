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
// STD - C++ Standard Library
#include <algorithm>
#include <cassert>
#include <cmath>
#include <deque>
#include <set>
#include <utility>
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "SceneNode.hpp"
////////////////////////////////////////////////


SceneNode::SceneNode(int category)
: mChildren()
, mParent(nullptr)
, mCategory(category)
{
}

////////////////////////////////////////////////

SceneNode::~SceneNode()
{

}

////////////////////////////////////////////////

void SceneNode::attachChild(SceneNode* child)
{
    child->mParent = this;
	mChildren.push_back(std::move(Ptr(child)));
}

////////////////////////////////////////////////

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
	auto found = std::find_if(mChildren.begin(), mChildren.end(), [&] (Ptr& p) { return p.get() == &node; });
	assert(found != mChildren.end());

	Ptr result = std::move(*found);
	result->mParent = nullptr;
	mChildren.erase(found);
	return result;
}

////////////////////////////////////////////////

void SceneNode::update()
{
    updateCurrent();
	updateChildren();
}

////////////////////////////////////////////////

void SceneNode::updateCurrent()
{
    // Do nothing by default.
}

////////////////////////////////////////////////

void SceneNode::updateChildren()
{
	for(Ptr& child : mChildren)
        child->update();
}

////////////////////////////////////////////////


void SceneNode::handleEvent(const sf::Event& event)
{
    handleEventCurrent(event);
    handleEventChildren(event);
}


void SceneNode::handleEventCurrent(const sf::Event& event)
{
    // Nothing by default.
}

void SceneNode::handleEventChildren(const sf::Event& event)
{
    for(Ptr& child : mChildren)
        child->handleEvent(event);
}


void SceneNode::removeWrecks()
{
	// Remove all children which request so
	auto wreckfieldBegin = std::remove_if(mChildren.begin(), mChildren.end(), std::mem_fn(&SceneNode::isMarkedForRemoval));
	mChildren.erase(wreckfieldBegin, mChildren.end());

	// Call function recursively for all remaining children
	for(Ptr& child : mChildren)
        child->removeWrecks();
}

////////////////////////////////////////////////

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Apply transform matrix.
	states.transform *= getTransform();

    // Draw this node.
    drawCurrent(target, states);

    // Draw children while inheriting this node's transform matrix.
	drawChildren(target, states);
}

////////////////////////////////////////////////

void SceneNode::drawCurrent(sf::RenderTarget&, sf::RenderStates) const
{
	// Do nothing by default.
}

////////////////////////////////////////////////

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(const Ptr& child : mChildren)
        child->draw(target, states);
}

////////////////////////////////////////////////

void SceneNode::drawBoundingRect(sf::RenderTarget& target, sf::RenderStates) const
{
	sf::FloatRect rect = getBoundingRect();

	sf::RectangleShape shape;
	shape.setPosition(sf::Vector2f(rect.left, rect.top));
	shape.setSize(sf::Vector2f(rect.width, rect.height));
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Blue);
	shape.setOutlineThickness(1.f);

	target.draw(shape);
}

////////////////////////////////////////////////

sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}

////////////////////////////////////////////////

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;

    // Get transforms recursively from all parents.
	for(const SceneNode* node = this; node != nullptr; node = node->mParent)
		transform = node->getTransform() * transform;

	return transform;
}

////////////////////////////////////////////////

bool SceneNode::isMarkedForRemoval() const
{
    // Return false by default.
    return false;
}

////////////////////////////////////////////////

sf::FloatRect SceneNode::getBoundingRect() const
{
    // By default, a node has no bounds
	return sf::FloatRect();
}

////////////////////////////////////////////////

int SceneNode::getCategory() const
{
    return mCategory;
}
