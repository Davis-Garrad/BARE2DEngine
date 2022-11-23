#pragma once

namespace BARE2D {
	// Need to define getData()
	template<typename T>
	T XMLDataManager::getData(std::string dataType, unsigned int key) {
		XMLData* dataPtr = getDataCache(dataType)->findItem(key);
		if(!dataPtr) return T();
		T* data = static_cast<T*>(dataPtr);
		return *data;
	}
	
	// Need to specialize XMLDataManager::readValue()
	template<>
	bool XMLDataManager::readValue(rapidxml::xml_node<>* parent, std::string valueName, std::string& variable);
	template<>
	bool XMLDataManager::readValue(rapidxml::xml_node<>* parent, std::string valueName, unsigned int& variable);
	template<>
	bool XMLDataManager::readValue(rapidxml::xml_node<>* parent, std::string valueName, std::vector<unsigned int>& variable);
	template<>
	bool XMLDataManager::readValue(rapidxml::xml_node<>* parent, std::string valueName, int& variable);
	template<>
	bool XMLDataManager::readValue(rapidxml::xml_node<>* parent, std::string valueName, float& variable);
	template<>
	bool XMLDataManager::readValue(rapidxml::xml_node<>* parent, std::string valueName, std::vector<float>& variable);
	template<>
	bool XMLDataManager::readValue(rapidxml::xml_node<>* parent, std::string valueName, bool& variable);
	template<>
	bool XMLDataManager::readValue(rapidxml::xml_node<>* parent, std::string valueName, std::vector<bool>& variable);
	template<>
	bool XMLDataManager::readValue(rapidxml::xml_node<>* parent, std::string valueName, glm::vec2& variable);
	template<>
	bool XMLDataManager::readValue(rapidxml::xml_node<>* parent, std::string valueName, std::vector<glm::vec2>& variable);

	template<typename T>
	void XMLDataManager::addDataType() {
		//  Make sure that T is actually a child class of XMLData
		static_assert(std::is_base_of<XMLData, T>::value, "XML Data Type is not derived class of BARE2D::XMLData");
		
		T sample;
		
		m_dataTypingFunctions[sample.nodeName] = []() ->  XMLData* { return new T; };
	}
}
