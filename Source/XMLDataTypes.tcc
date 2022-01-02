#pragma once

#include <glm/glm.hpp>

#include "Cache.hpp"
#include "Texture.hpp"
#include "LuaScript.hpp"
#include "BAREErrors.hpp"

namespace BARE2D {
	// AttributeBase is completely abstract. We don't need to actually define its methods
	// First, the Attribute methods
	// These ones will work for any T
	template<typename T>
	Attribute<T>::Attribute(std::string Name, AttributeType Type, T* data) {
		name = Name;
		type = Type;
		
		m_data = data;
	}
	
	template<typename T>
	void Attribute<T>::setData(T data) {
		if(!m_data) throwFatalError(BAREError::XML_FAILURE, "Failed to set data value - pointer not allocated");
		*m_data = data;
	}
	
	template<typename T>
	void Attribute<T>::swapDataPointer(T* newPtr) {
		*newPtr = *m_data;
		m_data = newPtr;
	}
	
	template<typename T>
	T Attribute<T>::getData() {
		return *static_cast<T*>(m_data);
	}
	
	template<typename T>
	T* Attribute<T>::getDataPointer() {
		return m_data;
	}
	
	// The following Attribute methods must be specialized, as they differ for each type of T
	// getDataString
	template<>
	std::string Attribute<std::string>::getDataString();
	template<>
	std::string Attribute<unsigned int>::getDataString();
	template<>
	std::string Attribute<int>::getDataString();
	template<>
	std::string Attribute<float>::getDataString();
	template<>
	std::string Attribute<bool>::getDataString();
	template<>
	std::string Attribute<glm::vec2>::getDataString();
	template<>
	std::string Attribute<std::vector<std::string>>::getDataString();
	template<>
	std::string Attribute<std::vector<unsigned int>>::getDataString();
	template<>
	std::string Attribute<std::vector<int>>::getDataString();
	template<>
	std::string Attribute<std::vector<float>>::getDataString();
	template<>
	std::string Attribute<std::vector<bool>>::getDataString();
	template<>
	std::string Attribute<std::vector<glm::vec2>>::getDataString();
	template<>
	std::string Attribute<LuaScript>::getDataString();
	template<>
	std::string Attribute<Texture>::getDataString();
	
	// SetDefaultData
	template<>
	void Attribute<std::string>::setDefaultData();
	template<>
	void Attribute<unsigned int>::setDefaultData();
	template<>
	void Attribute<int>::setDefaultData();
	template<>
	void Attribute<float>::setDefaultData();
	template<>
	void Attribute<bool>::setDefaultData();
	template<>
	void Attribute<glm::vec2>::setDefaultData();
	template<>
	void Attribute<std::vector<std::string>>::setDefaultData();
	template<>
	void Attribute<std::vector<unsigned int>>::setDefaultData();
	template<>
	void Attribute<std::vector<int>>::setDefaultData();
	template<>
	void Attribute<std::vector<float>>::setDefaultData();
	template<>
	void Attribute<std::vector<bool>>::setDefaultData();
	template<>
	void Attribute<std::vector<glm::vec2>>::setDefaultData();
	template<>
	void Attribute<LuaScript>::setDefaultData();
	template<>
	void Attribute<Texture>::setDefaultData();
	
	template<typename T>
	T XMLData::getAttributeByName(std::string name) {
		// Make sure the attribute exists:
		auto searchVariable = m_attributes.find(name);
		if(searchVariable == m_attributes.end()) {
			// Attribute was not found, send an error and return 0.
			throwError(BAREError::XML_FAILURE, "Warning: Attribute " + name + " does not exist.");
			return (T)0;
		}
		
		// If we make it here, the searchVaraible iterator has found our T - return the data in the attribute
		return static_cast<Attribute<T>*>(searchVariable->second)->getData();
	}
	
	template<typename T>
	void XMLData::addAttribute(std::string name, AttributeType type, T* data) {
		Attribute<T>* attr = new Attribute<T>(name, type, data);
		
		m_attributes[name] = attr;
	}
	// I believe that is all that needs to be specialized.
	
}
