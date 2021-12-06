#pragma once

// We use unordered maps for more efficient single-item access + appendation.
#include <unordered_map>
#include <string>

namespace BARE2D {

	/**
	 * @class Cache
	 * @brief This is a skeleton cache class. This can ***only*** be used by the ResourceManager or other classes who actually maintain proper pointer ownership.
	 */
	template<typename S, typename T>
	class Cache
	{
	public:
		Cache<S, T>() {}
	
		/**
		 * @brief Finds an item based on a key
		 * @param key The key to find the item by.
		 * @return A pointer to the data, or nullptr if no such data exists
		 */
		T* findItem(S& key);
		
		/**
		 * @brief An operator overload that returns the object stored at key. Analagous to findItem();
		 * @param key
		 */
		T* operator[](S& key);
		
		/**
		 * @brief Creates an item with a given key and uses the constructor to fill out the rest. If it already exists, overwrite it and return that pointer.
		 * @param key The key to give the item.
		 * @return A pointer to that item.
		 */
		T* createItem(S& key);
		
		/**
		 * @brief Clears the cache. Destroys all data, calling their respective destructors, then delete.
		 */
		void clear();
		
		/**
		 * @brief Returns the number of items in the cache.
		 */
		unsigned int getCount();
		
		// For iterating
		typename std::unordered_map<S, T*>::iterator begin();
		typename std::unordered_map<S, T*>::iterator end();
		bool operator!=(Cache& other);
		
	private:
		std::unordered_map<S, T*> m_data;
	};

}

#include "Cache_impl.tcc"
