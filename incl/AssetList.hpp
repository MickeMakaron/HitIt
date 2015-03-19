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

#ifndef HITIT_ASSETLIST_HPP
#define HITIT_ASSETLIST_HPP

////////////////////////////////////////////////
// HitIt internal headers
#include "ResourceIdentifiers.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// STD - C++ Standard Library
#include <list>
#include <string>
////////////////////////////////////////////////

template <typename AssetIdentifierT>
class AssetList
{
    public:
        /**
         * \struct Asset
         * Wrap resource ID and resource file path into a struct.
         */
        struct Asset
        {
            /**
             * \brief Constructor
             *
             * \param id Resource ID
             * \param filePath File path to resource
             */
            Asset(AssetIdentifierT id, std::string filePath) : id(id), filePath(filePath){};
            AssetIdentifierT id;    ///< Resource ID of resource
            std::string filePath;   ///< Path to resource
        };

    public:
        /**
         * \brief Constructor
         *
         * \param assets List of assets to use
         */
        AssetList(std::list<Asset> assets);

        /**
         * \brief Constructor
         */
        AssetList();

        /**
         * \brief Destructor
         */
        ~AssetList();

        /**
         * \brief Set list of assets to use
         *
         * \param assets List of assets to use
         * \param loadImmediately If set to true, AssetList will load the resources
         * to memory immediately
         */
        void setAssets(std::list<Asset> assets);

        /**
         * \brief Add multiple assets
         *
         * \param assets List of assets to insert
         */
        void insert(std::list<Asset> assets);

    private:
        /**
         * \brief Load assets into memory
         */
        void load();

        /**
         * \brief Release assets from memory
         */
        void release();

    private:
        std::list<Asset> mAssets; ///< Assets to use
};

/************************************************
 * \class AssetList
 *
 * Container for managing asset loading and releasing.
 * Using an AssetList for resource management assures
 * proper resource release from memory.
 *
************************************************/

typedef AssetList<ResourceID::Texture::ID>  TextureList;
typedef AssetList<ResourceID::Font::ID>     FontList;
typedef AssetList<ResourceID::Sound::ID>    SoundList;

#include "AssetList.inl"

#endif // HITIT_ASSETLIST_HPP
