#include "XMLDataTypes.hpp"

#include "XMLDataManager.hpp"
#include "ResourceManager.hpp"

namespace BARE2D {

	// AttributeBase definitions
	template<typename T>
	void AttributeBase::setData(T data) {
		// template acrobatics, baby!
		dynamic_cast<Attribute<T>*>(this)->setData(data);
	}
	
	template<typename T>
	T AttributeBase::getData() {
		// more acrobatics
		return dynamic_cast<Attribute<T>&>(*this).getData();
	}
	
	template<typename T>
	void AttributeBase::swapDataPointer(T* newPtr) {
		dynamic_cast<Attribute<T>*>(this)->swapDataPointer(newPtr);
	}
	
	template<typename T>
	T* AttributeBase::getDataPointer() {
		// now, template aerobics.
		return dynamic_cast<Attribute<T>&>(*this).getDataPointer();
	}
	
	// getDataString specializations
	template<>
	std::string Attribute<std::string>::getDataString() {
		return *m_data;
	}
	template<>
	std::string Attribute<unsigned int>::getDataString() {
		return std::to_string(*m_data);
	}
	template<>
	std::string Attribute<int>::getDataString() {
		return std::to_string(*m_data);
	}
	template<>
	std::string Attribute<float>::getDataString() {
		return std::to_string(*m_data);
	}
	template<>
	std::string Attribute<bool>::getDataString() {
		return std::to_string(*m_data);
	}
	template<>
	std::string Attribute<glm::vec2>::getDataString() {
		// "{x}{y}"
		return std::string("{" + std::to_string(m_data->x) + "," + std::to_string(m_data->y) + "}");
	}
	template<>
	std::string Attribute<std::vector<std::string>>::getDataString() {
		std::string ret = "";
		for(auto str : *m_data) {
			ret += "{" + str + "}";
		}
		return ret;
	}
	template<>
	std::string Attribute<std::vector<unsigned int>>::getDataString() {
		std::string ret = "";
		for(auto e : *m_data) {
			ret += "{" + std::to_string(e) + "}";
		}
		return ret;
	}
	template<>
	std::string Attribute<std::vector<int>>::getDataString() {
		std::string ret = "";
		for(auto e : *m_data) {
			ret += "{" + std::to_string(e) + "}";
		}
		return ret;
	}
	template<>
	std::string Attribute<std::vector<float>>::getDataString() {
		std::string ret = "";
		for(auto e : *m_data) {
			ret += "{" + std::to_string(e) + "}";
		}
		return ret;
	}
	template<>
	std::string Attribute<std::vector<bool>>::getDataString() {
		std::string ret = "";
		for(auto e : *m_data) {
			ret += "{" + std::to_string(e) + "}";
		}
		return ret;
	}
	template<>
	std::string Attribute<std::vector<glm::vec2>>::getDataString() {
		std::string ret = "";
		for(auto e : *m_data) {
			ret += "{" + std::to_string(e.x) + "," + std::to_string(e.y) + "},";
		}
		return ret;
	}
	template<>
	std::string Attribute<LuaScript>::getDataString() {
		return m_data->m_path;
	}
	template<>
	std::string Attribute<Texture>::getDataString() {
		return m_data->filepath;
	}
	
	// SetDefaultData
	template<>
	void Attribute<std::string>::setDefaultData() {
		setData("UNDEFINED");
	}
	template<>
	void Attribute<unsigned int>::setDefaultData() {
		setData((unsigned int)-1);
	}
	template<>
	void Attribute<int>::setDefaultData() {
		setData(-1);
	}
	template<>
	void Attribute<float>::setDefaultData() {
		setData(0.0f);
	}
	template<>
	void Attribute<bool>::setDefaultData() {
		setData(0);
	}
	template<>
	void Attribute<glm::vec2>::setDefaultData() {
		setData(glm::vec2(0.0f, 0.0f));
	}
	template<>
	void Attribute<std::vector<std::string>>::setDefaultData() {
		setData(std::vector<std::string>{});
	}
	template<>
	void Attribute<std::vector<unsigned int>>::setDefaultData() {
		setData(std::vector<unsigned int>{});
	}
	template<>
	void Attribute<std::vector<int>>::setDefaultData() {
		setData(std::vector<int>{});
	}
	template<>
	void Attribute<std::vector<float>>::setDefaultData() {
		setData(std::vector<float>{});
	}
	template<>
	void Attribute<std::vector<bool>>::setDefaultData() {
		setData(std::vector<bool>{});
	}
	template<>
	void Attribute<std::vector<glm::vec2>>::setDefaultData() {
		setData(std::vector<glm::vec2>{});	
	}
	template<>
	void Attribute<LuaScript>::setDefaultData() {
		setData(LuaScript());
	}
	template<>
	void Attribute<Texture>::setDefaultData() {
		Texture tex;
		tex.filepath = "UNDEFINED_PATH";
		setData(tex);
	}
	
	// Now that all the templates have been specialized, let's do some real work
	
	// XMLData
	XMLData::XMLData() : name(""), id(0) {
		// All data have a typename and id
		addAttribute("name", AttributeType::STRING, &name);
		addAttribute("id", AttributeType::UNSIGNED_INT, &id);
	}
	
	XMLData::XMLData(std::string dataType, unsigned int ID) {
		// Also set the ID and get attributes
		*this = XMLDataManager::getData<XMLData>(dataType, ID);
		
		m_attributes["name"]->swapDataPointer(&name);
		m_attributes["id"]->swapDataPointer(&id);
	}
	
	XMLData::XMLData(std::vector<AttributeBase*> attributes) : XMLData() {
		// All data have a typename and id
		addAttribute("name", AttributeType::STRING, &name);
		addAttribute("id", AttributeType::UNSIGNED_INT, &id);
		
		// Add all of the extra attributes
		addAttributes(attributes);
	}
	
	XMLData::XMLData(std::unordered_map<std::string, AttributeBase*> attributes) : XMLData() {
		// Purely for copy operations
		m_attributes = attributes;
	}
	
	void XMLData::read(rapidxml::xml_node<>* node) {
		// The node is the node of the data, so we can read everything from it right away, no navigation
		// First, find the id
		unsigned int readID = (unsigned int)std::stoi(node->first_attribute("id")->value());
		m_attributes["id"]->setData(readID);
		id = readID;
		// Now, the name - returns a c_str, so we need to cast to std::string first
		std::string readName = std::string(node->first_attribute("name")->value());
		m_attributes["name"]->setData(readName);
		name = readName;
		
		// Now read every attribute - we read by reference so we can change the values that are stored in the class!
		for(auto& attr : m_attributes) {
			// Get some simple values
			std::string attrName = attr.first;
			AttributeBase* attrValue = attr.second; 
			
			// Make sure they're not ones we already loaded (name & id)
			if(attrName == "name" || attrName == "id")
				continue;
				
			// Now, get the value based on the type of attribute
			switch(attrValue->type) {
				case AttributeType::STRING: {
					std::string data;
					// Use the templated function to get the string interpretation
					XMLDataManager::readValue(node, attrName, data);
					// Set the data now
					attrValue->setData(data);
					break;
				}
				case AttributeType::UNSIGNED_INT: {
					unsigned int data;
					// Use the templated function to get the string interpretation
					XMLDataManager::readValue(node, attrName, data);
					// Set the data now
					attrValue->setData(data);
					break;
				}
				case AttributeType::VECTOR_UNSIGNED_INT: {
					std::vector<unsigned int> data;
					// Use the templated function to get the string interpretation
					XMLDataManager::readValue(node, attrName, data);
					// Set the data now
					attrValue->setData(data);
					break;
				}
				case AttributeType::INT: {
					int data;
					// Use the templated function to get the string interpretation
					XMLDataManager::readValue(node, attrName, data);
					// Set the data now
					attrValue->setData(data);
					break;
				}
				case AttributeType::FLOAT: {
					float data;
					// Use the templated function to get the string interpretation
					XMLDataManager::readValue(node, attrName, data);
					// Set the data now
					attrValue->setData(data);
					break;
				}
				case AttributeType::VECTOR_FLOAT: {
					std::vector<float> data;
					// Use the templated function to get the string interpretation
					XMLDataManager::readValue(node, attrName, data);
					// Set the data now
					attrValue->setData(data);
					break;
				}
				case AttributeType::BOOL: {
					bool data;
					// Use the templated function to get the string interpretation
					XMLDataManager::readValue(node, attrName, data);
					// Set the data now
					attrValue->setData(data);
					break;
				}
				case AttributeType::VECTOR_BOOL: {
					std::vector<bool> data;
					// Use the templated function to get the string interpretation
					XMLDataManager::readValue(node, attrName, data);
					// Set the data now
					attrValue->setData(data);
					break;
				}
				case AttributeType::VEC2: {
					glm::vec2 data;
					// Use the templated function to get the string interpretation
					XMLDataManager::readValue(node, attrName, data);
					// Set the data now
					attrValue->setData(data);
					break;
				}
				case AttributeType::VECTOR_VEC2: {
					std::vector<glm::vec2> data;
					// Use the templated function to get the string interpretation
					XMLDataManager::readValue(node, attrName, data);
					// Set the data now
					attrValue->setData(data);
					break;
				}
				case AttributeType::SCRIPT: {
					std::string path;
					// Get the string interpretation
					XMLDataManager::readValue(node, attrName, path);
					// Load the script.
					LuaScript scr = ResourceManager::loadScript(path);
					// Set the data.
					attrValue->setData(scr);
					break;
				}
				case AttributeType::TEXTURE: {
					std::string path;
					// Get the path
					XMLDataManager::readValue(node, attrName, path);
					// Load the texture
					Texture tex = ResourceManager::loadTexture(path);
					// Set the data
					attrValue->setData(tex);
					break;
				}
				
				default: {
					throwError(BAREError::XML_FAILURE, "Failed to read attribute with type: " + std::to_string((unsigned int)attrValue->type) + " of name " + attrName);
					return;
				}
			};
		}
		
	}
	
	void XMLData::write(rapidxml::xml_document<>* doc) {
		// RapidXML requires that we allocate the name of the node by their function so it doesn't get cleaned up
		char* allocatedNodeName = doc->allocate_string(nodeName.c_str());
		
		// Now we can actually allocate the node, creating a new one for this data
		rapidxml::xml_node<>* node = doc->allocate_node(rapidxml::node_element, allocatedNodeName);
		doc->append_node(node);
		
		// Write the name and id
		{ // ID
			// First, allocate the value as a c_string within rapidxml's systems
			char* allocatedValue = doc->allocate_string(std::to_string(id).c_str());
			// Now allocate the attribute itself as a node-ish thing
			rapidxml::xml_attribute<>* idAttribute = doc->allocate_attribute("id", allocatedValue);
			// Now actually add the attribute to the node
			node->append_attribute(idAttribute);
		}
		
		{ // Name
			// First, allocate the value as a c_string within rapidxml's systems
			char* allocatedValue = doc->allocate_string(name.c_str());
			// Now allocate the attribute itself as a node-ish thing
			rapidxml::xml_attribute<>* nameAttribute = doc->allocate_attribute("name", allocatedValue);
			// Now actually add the attribute to the node
			node->append_attribute(nameAttribute);
		}
		
		// Now we're done with the simple name and id attributes, we need to add child nodes in the same way we loaded them
		for(auto& attr : m_attributes) {
			// Get some initial stuff
			std::string attrName = attr.first;
			AttributeBase* attrValue = attr.second;
			
			// Make sure we aren't re-saving stuff we've already done
			if(attrName == "name" || attrName == "id")
				continue;
				
			// We don't even really need to interpret (exterpret?) the value, as converting from data to a string is defined by the actual attribute, not by the type.
			
			// Actually allocate that value, as well as the attribute's name
			const char* allocatedValue = doc->allocate_string(attrValue->getDataString().c_str());
			const char* allocatedName = doc->allocate_string(attrName.c_str());
			
			// Allocate the node
			rapidxml::xml_node<>* allocatedNode = doc->allocate_node(rapidxml::node_element, allocatedName, allocatedValue);
			
			// Actually add the node
			node->append_node(allocatedNode);
		}
		
		// Now we've written all of the XML data to the document!
	}
	
	std::unordered_map<std::string, AttributeBase*> XMLData::getAttributes() {
		return m_attributes;
	}
	
	void XMLData::addAttribute(AttributeBase* attr) {
		m_attributes[attr->name] = attr;
	}
	
	void XMLData::addAttributes(std::vector<AttributeBase*> attrs) {
		for(auto a : attrs) {
			addAttribute(a);
		}
	}
	
}
