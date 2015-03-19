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
#include "Assets.hpp"
////////////////////////////////////////////////

std::string Assets::mWorkingDirectory;
ResourceHolder<sf::Texture, ResourceID::Texture::ID>    Assets::mTextureHolder;
ResourceHolder<sf::Font, ResourceID::Font::ID>          Assets::mFontHolder;
ResourceHolder<sf::SoundBuffer, ResourceID::Sound::ID>  Assets::mSoundHolder;

////////////////////////////////////////////////

const sf::Texture& Assets::load(ResourceID::Texture::ID texture, const std::string& filePath)
{
    return mTextureHolder.load(texture, mWorkingDirectory + filePath);
}

////////////////////////////////////////////////

const sf::Font& Assets::load(ResourceID::Font::ID font, const std::string& filePath)
{
    return mFontHolder.load(font, mWorkingDirectory + filePath);
}

////////////////////////////////////////////////

const sf::SoundBuffer& Assets::load(ResourceID::Sound::ID sound, const std::string& filePath)
{
    return mSoundHolder.load(sound, mWorkingDirectory + filePath);
}

////////////////////////////////////////////////

sf::Texture& Assets::get(ResourceID::Texture::ID texture)
{
    return mTextureHolder.get(texture);
}

////////////////////////////////////////////////

sf::Font& Assets::get(ResourceID::Font::ID font)
{
    return mFontHolder.get(font);
}

////////////////////////////////////////////////

sf::SoundBuffer& Assets::get(ResourceID::Sound::ID sound)
{
    return mSoundHolder.get(sound);
}

////////////////////////////////////////////////

void Assets::release(ResourceID::Texture::ID texture)
{
    mTextureHolder.release(texture);
}

////////////////////////////////////////////////

void Assets::release(ResourceID::Font::ID font)
{
    mFontHolder.release(font);
}

////////////////////////////////////////////////

void Assets::release(ResourceID::Sound::ID sound)
{
    mSoundHolder.release(sound);
}

////////////////////////////////////////////////

void Assets::release()
{
    mTextureHolder.release();
    mFontHolder.release();
    mSoundHolder.release();
}

////////////////////////////////////////////////

void Assets::setDirectory(const std::string& path)
{
    mWorkingDirectory = path;
}
