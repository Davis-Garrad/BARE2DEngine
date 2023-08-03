#pragma once
// This holds all the non-specialized templates for Cache.hpp

#include "BAREErrors.hpp"

namespace BARE2D {

template <typename S, typename T> T* Cache<S, T>::findItem(S& key)
{
    // Check if we have the item in the m_data map

    auto iter = m_data.find(key);

    if(iter == m_data.end())
	{
	    return nullptr;
    } else
	{
	    return m_data[key];
	}
}

template <typename S, typename T> T* Cache<S, T>::operator[](S& key)
{
    return findItem(key);
}

template <typename S, typename T> bool Cache<S, T>::addItem(S& key, T* item)
{
    if(findItem(key))
	return false;
    m_data[key] = item;
    return true;
}

template <typename S, typename T> bool Cache<S, T>::setItem(S& key, T* item)
{
    if(findItem(key))
	{
	    delete findItem(key);
    }
    m_data[key] = item;
    return true;
}

template <typename S, typename T> T* Cache<S, T>::createItem(S& key, std::function<T*()> creationFunc)
{
    // Creates an item, or overwrites the existing item if it already exists.

    // Check if it already exists
    T* object = findItem(key);

    // nullptr if object doesn't already exist
    if(object)
	{
	    throwFatalError(BAREError::CACHE_FAILURE, "Item was created twice.");
	    return nullptr;
    }

    // Now we know the object doesn't exist, so we need to create one!
    object = creationFunc();

    m_data.insert(std::make_pair(key, object));

    return object;
}

template <typename S, typename T> void Cache<S, T>::clear()
{
    // Deletes all in m_data, then clears m_data.
    // Delete em all
    for(std::pair<S, T*> i : m_data)
	{
	    delete i.second;
	}

    // Clear it all
    m_data.clear();
}

template <typename S, typename T> unsigned int Cache<S, T>::getCount()
{
    return m_data.size();
}

template <typename S, typename T> typename std::unordered_map<S, T*>::iterator Cache<S, T>::begin()
{
    return m_data.begin();
}

template <typename S, typename T> typename std::unordered_map<S, T*>::iterator Cache<S, T>::end()
{
    return m_data.end();
}

template <typename S, typename T> bool Cache<S, T>::operator!=(Cache& other)
{
    return m_data != other.m_data;
}

} // namespace BARE2D
