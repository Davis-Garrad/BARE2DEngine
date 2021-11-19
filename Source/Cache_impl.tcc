#pragma once
// This holds all the non-specialized templates for Cache.hpp

namespace BARE2D {
	
	template<typename T>
	T* Cache<T>::findItem(std::string& key) {
		// Check if we have the item in the m_data map
		
		auto iter = m_data.find(key);
		
		if(iter == m_data.end()) {
			return nullptr;
		} else {
			return m_data[key];
		}
	}
	
	template<typename T>
	T* Cache<T>::createItem(std::string& key) {
		// Creates an item, or overwrites the existing item if it already exists.
		
		// Check if it already exists
		T* object = findItem(key);
		
		// nullptr if object doesn't already exist
		if(object) {
			*object = (T());
			return object;
		}
		
		// Now we know the object doesn't exist, so we need to create one!
		object = new T();
		
		m_data.insert(std::make_pair(key, object));
		
		return object; 
	}
	
	template<typename T>
	void Cache<T>::clear() {
		// Deletes all in m_data, then clears m_data.
		// Delete em all
		for(std::pair<std::string, T*> i : m_data) {
			delete i.second;
		}
		
		// Clear it all
		m_data.clear();
		
	}
	
}
