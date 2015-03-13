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

#ifndef HITIT_SCENENODE_HPP
#define HITIT_SCENENODE_HPP


////////////////////////////////////////////////
// STD - C++ Standard Library
#include <list>
#include <memory>
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/System/NonCopyable.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Graphics/Drawable.hpp"
namespace sf
{
    class Event;
}
////////////////////////////////////////////////

class SceneNode : public sf::Transformable, virtual public sf::Drawable, private sf::NonCopyable
{
	public:
		typedef std::unique_ptr<SceneNode> Ptr;


	public:
	    /**
	     * \brief Constructor
	     */
		SceneNode(int category = 0);

        /**
         * \brief Destructor
         */
        virtual ~SceneNode();

        /**
         * \brief Attach child to node.
         *
         * \param child node to attach.
         */
		void attachChild(SceneNode* child);

		/**
		 * \brief Detach child from node.
		 *
		 * \param node node to detach.
		 *
		 * \return detached node.
		 */
		Ptr detachChild(const SceneNode& node);

        /**
         * \brief Update node.
         *
         * Performs the updateCurrent and updateChildren update functions.
         */
		void update();

		/**
		 * \brief Remove children marked for removal.
		 */
        void removeWrecks();

        /**
         * \brief Get world position of node.
         *
         * \return absolute world position of node.
         */
		sf::Vector2f getWorldPosition() const;

		/**
		 * \brief Get world transform of node.
		 *
		 * \return absolute world transform of node.
		 */
		sf::Transform getWorldTransform() const;

		/**
		 * \brief Get bounding rectangle of node.
		 *
		 * \return bounding rectangle of node.
		 */
		virtual sf::FloatRect	getBoundingRect() const;

		/**
         * \brief Get category of node.
         *
         * \return enumarable value (int) representing categories.
         */
        virtual int getCategory() const;

		/**
		 * \brief Indicate whether this node is marked for removal.
		 *
		 * \return true if marked for removal, else false.
		 */
        virtual bool isMarkedForRemoval() const;

        /**
         * \brief Draw bounding rectangle of node.
         *
         * \param target SFML RenderTarget object to draw bounding rectangle to.
         * \param states SFML RenderStates object to transform draw with.
         */
		void drawBoundingRect(sf::RenderTarget& target, sf::RenderStates states) const;

		/**
		 * \brief Handle device input.
		 *
		 * \param event event to handle
		 */
        void handleEvent(const sf::Event& event);

    protected:
        void clearChildren();

	private:
		/**
		 * \brief Handle device input for this node.
		 *
		 * \param event event to handle
		 */
        virtual void handleEventCurrent(const sf::Event& event);


		/**
		 * \brief Handle device input for children.
		 *
		 * \param event event to handle
		 */
        void handleEventChildren(const sf::Event& event);


	    /**
	     * \brief Update this node.
	     */
		virtual void            updateCurrent();

		/**
		 * \brief Update children of this node.
		 */
		void					updateChildren();

        /**
         * \brief Overloaded SFML draw function.
         *
         * Performs the drawCurrent and drawChildren draw functions.
         *
         * \param target SFML RenderTarget object to draw to.
         * \param states SFML RenderStates object ot transform draw with.
         */
		virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;

        /**
         * \brief Draw this node.
         *
         * \param target SFML RenderTarget object to draw this node to.
         * \param states SFML RenderStates object ot transform draw with.
         */
		virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

        /**
         * \brief Draw children of this node.
         *
         * \param target SFML RenderTarget object to draw children of this node to.
         * \param states SFML RenderStates object ot transform draw with.
         */
		void					drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;


	private:
		std::list<Ptr>		    mChildren;  ///< Children of this node.
		SceneNode*              mParent;    ///< Parent of this node.
		int                     mCategory;  ///< Category of node.
};

/************************************************
 * \class SceneNode
 *
 * Base class of all nodes that reside in the
 * scene.
 *
************************************************/


#endif // HITIT_SCENENODE_HPP
