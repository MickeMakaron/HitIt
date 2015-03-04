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


template <typename AssetIdentifierT>
AssetList<AssetIdentifierT>::AssetList(std::list<Asset> assets)
: mAssets(assets)
, mIsLoaded(false)
{
}

////////////////////////////////////////////////

template <typename AssetIdentifierT>
AssetList<AssetIdentifierT>::AssetList()
: mIsLoaded(false)
{
}

////////////////////////////////////////////////

template <typename AssetIdentifierT>
AssetList<AssetIdentifierT>::~AssetList()
{
    release();
}

////////////////////////////////////////////////

template <typename AssetIdentifierT>
void AssetList<AssetIdentifierT>::setAssets(std::list<Asset> assets)
{
    release();
    mAssets = assets;
}

////////////////////////////////////////////////

template <typename AssetIdentifierT>
void AssetList<AssetIdentifierT>::load()
{
    if(!mIsLoaded)
        for(Asset a : mAssets)
            Assets::load(a.id, a.filePath);

    mIsLoaded = true;
}

////////////////////////////////////////////////

template <typename AssetIdentifierT>
void AssetList<AssetIdentifierT>::release()
{
    if(mIsLoaded)
        for(Asset a : mAssets)
            Assets::release(a.id);

    mIsLoaded = false;
}
