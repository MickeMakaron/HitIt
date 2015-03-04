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

#ifndef HITIT_RESOURCEHOLDER_HPP
#define HITIT_RESOURCEHOLDER_HPP

////////////////////////////////////////////////
// C++ Standard Library
#include <map>
#include <string>
#include <memory>
////////////////////////////////////////////////

template <typename ResourceT, typename IdentifierT>
class ResourceHolder
{
    public:
        /**
         * \brief Load resource into memory by file path.
         *
         * \param id ID of resource
         * \param filePath file path to resource
         *
         * \return reference to loaded resource.
         */
        ResourceT& load(IdentifierT id, const std::string& filePath);

        /**
         * \brief Load resource into memory by resource object.
         *
         * \param id ID of resource
         * \param resource resource object to load
         *
         * \return reference to loaded resource.
         */
        ResourceT& load(IdentifierT id, ResourceT& resource);


        /**
         * \brief Get resource from memory.
         *
         * \param id ID of resource
         *
         * \return reference to resource.
         */
        ResourceT& get(IdentifierT id);

        /**
         * \brief Check if resource is loaded into memory.
         *
         * \param id ID of resource
         *
         * \return true if resource is loaded into memory, else false.
         */
        bool isLoaded(IdentifierT id);

        /**
         * \brief Release resource from memory.
         *
         * \param id ID of resource
         */
        void release(IdentifierT id);

        /**
         * \brief Release all resources from memory.
         */
        void release();


    private:
        typedef std::unique_ptr<ResourceT> Ptr;

        /**
         * \struct Resource
         *
         * Resulting struct that is inserted into resource map.
         */
        struct Resource
        {
            Ptr resource;   ///< Unique resource pointer. Multiple sessions of the same resource is not allowed.
            int counter;    ///< Indicator of how many sessions that are using this resource.
        };

        std::map<IdentifierT, Resource> mResourceMap; ///< ID-resource map.
};
/************************************************
 * \class ResourceHolder
 *
 * Resource holder for generic SFML resource objects.
 * A ResourceHolder object has ownership of the
 * SFML resource object pointers. It makes sure only
 * one instance per ID is loaded and that it is loaded
 * until no session requests it.
 *
************************************************/

#include "ResourceHolder.inl"

#endif // HITIT_RESOURCEHOLDER_HPP
