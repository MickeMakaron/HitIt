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
// C++ Standard Library
#include <stdexcept>
#include <cassert>
////////////////////////////////////////////////

template <typename ResourceT, typename IdentifierT>
const ResourceT& ResourceHolder<ResourceT, IdentifierT>::load(IdentifierT id, const std::string& filePath)
{
    auto inserted = mResourceMap.insert(std::make_pair(id, Resource()));

    // If insertion failed (i.e., ID is already loaded), increment the existing ID's counter
    if(!inserted.second)
        inserted.first->second.counter++;
    //If insertion succeeded, move the resource to it and set its counter to 1
    else
    {
        Ptr resource(new ResourceT());
        // Make sure the filePath is loadable.
        if(!resource->loadFromFile(filePath))
            throw std::runtime_error("ResourceHolder::load - Failed to load " + filePath);


        inserted.first->second.resource = std::move(resource);
        inserted.first->second.counter = 1;
    }

    return *inserted.first->second.resource;
}

////////////////////////////////////////////////

template <typename ResourceT, typename IdentifierT>
const ResourceT& ResourceHolder<ResourceT, IdentifierT>::load(IdentifierT id, const ResourceT& resource)
{
    auto inserted = mResourceMap.insert(std::make_pair(id, Resource()));

    // If insertion failed (i.e., ID is already loaded), increment the existing ID's counter
    if(!inserted.second)
        inserted.first->second.counter++;
    //If insertion succeeded, move the resource to it and set its counter to 1
    else
    {
        inserted.first->second.resource = std::move(Ptr(&resource));
        inserted.first->second.counter = 1;
    }

    return *inserted.first->second.resource;
}

////////////////////////////////////////////////

template <typename ResourceT, typename IdentifierT>
const ResourceT& ResourceHolder<ResourceT, IdentifierT>::get(IdentifierT id) const
{
    auto found = mResourceMap.find(id);
    assert(found != mResourceMap.end());
    return *found->second.resource;
}

////////////////////////////////////////////////

template <typename ResourceT, typename IdentifierT>
bool ResourceHolder<ResourceT, IdentifierT>::isLoaded(IdentifierT id)
{
    return mResourceMap.find(id) != mResourceMap.end();
}

////////////////////////////////////////////////

template <typename ResourceT, typename IdentifierT>
void ResourceHolder<ResourceT, IdentifierT>::release(IdentifierT id)
{
    auto found = mResourceMap.find(id);
    assert(found != mResourceMap.end());

    // Only decrement counter if multiple sessions need the resource.
    if(found->second.counter > 1)
        found->second.counter --;
    // Else erase the resource.
    else
        mResourceMap.erase(found);
}

////////////////////////////////////////////////

template <typename ResourceT, typename IdentifierT>
void ResourceHolder<ResourceT, IdentifierT>::release()
{
    mResourceMap.clear();
}
