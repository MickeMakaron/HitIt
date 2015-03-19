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

#ifndef HITIT_ASSETS_HPP
#define HITIT_ASSETS_HPP

////////////////////////////////////////////////
// HitIt internal headers
#include "ResourceIdentifiers.hpp"
#include "ResourceHolder.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Audio/SoundBuffer.hpp"
////////////////////////////////////////////////

class Assets
{
    public:
        /**
         * \brief Load texture
         *
         * \param texture ID of texture
         * \param filePath Path to texture
         *
         * \return Reference to loaded texture
         */
        static const sf::Texture& load(ResourceID::Texture::ID texture, const std::string& filePath);

        /**
         * \brief Load font
         *
         * \param font ID of font
         * \param filePath Path to font
         *
         * \return Reference to loaded font
         */
        static const sf::Font& load(ResourceID::Font::ID font, const std::string& filePath);

        /**
         * \brief Load sound
         *
         * \param sound ID of sound
         * \param filePath Path to sound
         *
         * \return Reference to loaded sound
         */
        static const sf::SoundBuffer& load(ResourceID::Sound::ID sound, const std::string& filePath);

        /**
         * \brief Get texture
         *
         * \param texture ID of texture
         *
         * \return Reference to texture
         */
        static sf::Texture& get(ResourceID::Texture::ID texture);

        /**
         * \brief Get font
         *
         * \param font ID of font
         *
         * \return Reference to font
         */
        static sf::Font& get(ResourceID::Font::ID font);

        /**
         * \brief Get sound
         *
         * \param sound ID of sound
         *
         * \return Reference to sound
         */
        static sf::SoundBuffer& get(ResourceID::Sound::ID sound);

        /**
         * \brief Release texture
         *
         * \param texture ID of texture
         */
        static void release(ResourceID::Texture::ID texture);

        /**
         * \brief Release font
         *
         * \param font ID of font
         */
        static void release(ResourceID::Font::ID font);

        /**
         * \brief Release sound
         *
         * \param sound ID of sound
         */
        static void release(ResourceID::Sound::ID sound);

        /**
         * \brief Release all resources
         */
        static void release();

        /**
         * \brief Set working directory
         *
         * All file paths passed into the "load" functions
         * will be regarded as relative to this directory.
         *
         * \param path Absolute path to directory
         */
         static void setDirectory(const std::string& path);

    private:
        static std::string mWorkingDirectory; ///< Relative directory to search in for resource files

        static ResourceHolder<sf::Texture, ResourceID::Texture::ID>     mTextureHolder; ///< Holder of texture resources
        static ResourceHolder<sf::Font, ResourceID::Font::ID>           mFontHolder;    ///< Holder of font resources
        static ResourceHolder<sf::SoundBuffer, ResourceID::Sound::ID>   mSoundHolder;   ///< Holder of sound resources
};

/************************************************
 * \class Assets
 *
 * The Assets class holds all assets, such as
 * textures, fonts and sounds. It does NOT manage
 * resource lifetime.
 *
 * Since Assets is a static class it is not
 * responsible for making sure resources are
 * released on exit. Use AssetList for this.
 *
************************************************/

#endif // HITIT_ASSETS_HPP
