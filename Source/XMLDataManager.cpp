#include "XMLDataManager.hpp"

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <algorithm>
#include <rapidxml/rapidxml_print.hpp> // For the overloaded << operator

#include "Logger.hpp"
#include "Filesystem.hpp"

namespace BARE2D {
	
	Cache<std::string, Cache<unsigned int, XMLData>> XMLDataManager::m_storedData;
	Cache<std::string, XMLData> XMLDataManager::m_dataTypes; 
	
	void XMLDataManager::loadXML(std::string filepath) {
		Logger::getInstance()->log("Beginning XML Data Load.");
		
		// Get all the different file names
		std::vector<std::string> files = Filesystem::getFilesIn(filepath);
		std::vector<std::string> xmlTypes{};
		
		for(unsigned int i = 0; i < files.size(); i++) {
			// Convert file names - (foobar.xml) - to data types - (foobar)
			std::string fileNameNoExt = files[i].substr(0, files[i].size()-4);
			std::string fileNameExt = files[i].substr(files[i].size()-4, 4);
			
			if(fileNameExt == ".xml") {
				// It ends with .xml, so it's probably an XML file. This is dirty and bad and we should probably do this better. But we won't.
				xmlTypes.push_back(fileNameNoExt);
			}
		}
		
		// Now load each file.
		for(unsigned int i = 0; i < xmlTypes.size(); i++) {
			std::ifstream file(filepath + "/" + xmlTypes[i] + ".xml");
			
			if(file.fail())
				throwFatalError(BAREError::XML_FAILURE, "Could not read from file: " + filepath + "/" + xmlTypes[i] + ".xml");
			
			readXMLData(file, xmlTypes[i]);
			
			file.close();
		}
		
		Logger::getInstance()->log("XML Data Load Complete.");
	}
	
	void XMLDataManager::readXMLData(std::ifstream& file, std::string dataType) {
		Logger::getInstance()->log("Starting XML data read from file");
		
		// Find the proper data cache
		Cache<unsigned int, XMLData>* data = getDataCache(dataType);
		
		// Create an XML document for the file
		rapidxml::xml_document<> doc;
		// Read the file
		std::string line;
		std::string totalContent;
		while(std::getline(file, line)) {
			totalContent += line + "\n";
		}
		doc.parse<rapidxml::parse_full>((char*)totalContent.c_str());
		
		// Use the data-specific read function for every node found
		for(rapidxml::xml_node<>* node = doc.first_node(); node; node = node->next_sibling()) {
			if(node->type() != rapidxml::node_comment) {
				// Figure out what attributes we actually need to read, and add them to the data.
				std::string nodeName = std::string(node->name());
				XMLData d = *m_dataTypes.findItem(nodeName);
				d.nodeName = nodeName;
				
				d.read(node);
				
				addData(&d);
				
				Logger::getInstance()->log("\tRead XML: " + d.nodeName + ": " + d.name + " (" + std::to_string(d.id) + ")");
			}
		}
		
		Logger::getInstance()->log("Finished XML data read from file");
	}
	
	void XMLDataManager::saveXML(std::string filepath) {
		Logger::getInstance()->log("Beginning XML Data Write.");
		
		for(auto& cache : m_storedData) {
			// For every cache of data, we need to write to their own file
			std::string dataType = cache.first;
			
			// First, make sure the file exists and is empty
			std::ofstream file(filepath + "/" + dataType + ".xml");
			
			// Make sure the file was created/opened A-okay.
			if(file.fail())
				throwFatalError(BAREError::XML_FAILURE, "Could not save to file: " + filepath + "/" + dataType + ".xml");
			
			// Now actually write the data to the open file
			writeXMLData(file, cache.second);
			
			// And finally close the file
			file.close();
		}
		
		Logger::getInstance()->log("XML Data Write Complete.");
	}
	
	void XMLDataManager::writeXMLData(std::ofstream& file, Cache<unsigned int, XMLData>* data) {
		Logger::getInstance()->log("Starting XML data save to file");
		
		// Create an XML document for the file
		rapidxml::xml_document<> doc;
		
		// Now just write every piece of data to the doc
		for(auto& e : *data) {
			// Use the data-specific write function
			e.second->write(&doc);
			
			Logger::getInstance()->log("\tWrote XML: " + e.second->nodeName + ": " + e.second->name + " (" + std::to_string(e.second->id) + ")");
		}
		
		// Actually write the XML doc to the file, using rapidXML's overloaded << operator.
		file << doc;
		
		Logger::getInstance()->log("Finished XML data save to file");
	}
	
	unsigned int XMLDataManager::getDataCount(std::string dataType) {
		return getDataCache(dataType)->getCount();
	}
	
	void XMLDataManager::addData(XMLData* data) {
		Cache<unsigned int, XMLData>* c = getDataCache(data->nodeName);
		
		XMLData* dataPointer = c->findItem(data->id);
		
		if(!dataPointer) {
			dataPointer = c->createItem(data->id);
		}
		
		*dataPointer = *data;
	}
	
	XMLData XMLDataManager::getDataType(std::string dataType) {
		return *m_dataTypes.findItem(dataType);
	}
	
	template<>
	bool XMLDataManager::readValue(rapidxml::xml_node<>* parent, std::string valueName, std::string& variable) {
		// Find the node that has a name valueName	
		rapidxml::xml_node<>* node = parent->first_node(valueName.c_str());
		
		// Make sure that such a node actually exists
		if(!node) {
			throwError(BAREError::XML_FAILURE, "Could not find node with name " + valueName);
			return false;
		}
		
		// We're good if we reach here, so its time to just read the value and interpret it, as long as it actually has a value.
		if(std::string(node->value()) != std::string("")) {
			variable = std::string(node->value());
		}
		
		return true;
	}
	template<>
	bool XMLDataManager::readValue(rapidxml::xml_node<>* parent, std::string valueName, unsigned int& variable) {
		// Find the node that has a name valueName	
		rapidxml::xml_node<>* node = parent->first_node(valueName.c_str());
		
		// Make sure that such a node actually exists
		if(!node) {
			throwError(BAREError::XML_FAILURE, "Could not find node with name " + valueName);
			return false;
		}
		
		// We're good if we reach here, so its time to just read the value and interpret it, as long as it actually has a value.
		if(std::string(node->value()) != std::string("")) {
			variable = std::stoi(std::string(node->value()));
		}
		
		return true;
	}
	template<>
	bool XMLDataManager::readValue(rapidxml::xml_node<>* parent, std::string valueName, std::vector<unsigned int>& variable) {
		// Find the node that has a name valueName	
		rapidxml::xml_node<>* node = parent->first_node(valueName.c_str());
		
		// Make sure that such a node actually exists
		if(!node) {
			throwError(BAREError::XML_FAILURE, "Could not find node with name " + valueName);
			return false;
		}
		
		// We're good if we reach here, so its time to just read the value and interpret it, as long as it actually has a value.
		if(std::string(node->value()) != std::string("")) {
			variable = std::vector<unsigned int>{};
			
			std::string value = node->value();
			
			// Now we need to actually interpret the string
			// First, figure out how many ints we have
			unsigned int elementCount = std::count(value.begin(), value.end(), '{');
			
			// Now, for every element, actually read it!
			for(unsigned int i = 0; i < elementCount; i++) {
				// Find the first substring that represents our vector value
				std::string uintStr = value.substr(value.find('{')+1, value.find('}') - value.find('{') - 1);
				
				// Interpret the string
				unsigned int val = std::stoi(uintStr);
				
				// Actually add the values to the vector.
				variable.emplace_back(val);
				
				// Change what our search range actually is.
				value = value.substr(value.find('{')+1, value.size() - value.find('{') - 1);
			}
		}
		
		return true;
	}
	template<>
	bool XMLDataManager::readValue(rapidxml::xml_node<>* parent, std::string valueName, int& variable) {
		// Find the node that has a name valueName	
		rapidxml::xml_node<>* node = parent->first_node(valueName.c_str());
		
		// Make sure that such a node actually exists
		if(!node) {
			throwError(BAREError::XML_FAILURE, "Could not find node with name " + valueName);
			return false;
		}
		
		// We're good if we reach here, so its time to just read the value and interpret it, as long as it actually has a value.
		if(std::string(node->value()) != std::string("")) {
			variable = std::stoi(std::string(node->value()));
		}
		
		return true;
	}
	template<>
	bool XMLDataManager::readValue(rapidxml::xml_node<>* parent, std::string valueName, float& variable) {
		// Find the node that has a name valueName	
		rapidxml::xml_node<>* node = parent->first_node(valueName.c_str());
		
		// Make sure that such a node actually exists
		if(!node) {
			throwError(BAREError::XML_FAILURE, "Could not find node with name " + valueName);
			return false;
		}
		
		// We're good if we reach here, so its time to just read the value and interpret it, as long as it actually has a value.
		if(std::string(node->value()) != std::string("")) {
			variable = std::stof(std::string(node->value()));
		}
		
		return true;
	}
	template<>
	bool XMLDataManager::readValue(rapidxml::xml_node<>* parent, std::string valueName, std::vector<float>& variable) {
		// Find the node that has a name valueName	
		rapidxml::xml_node<>* node = parent->first_node(valueName.c_str());
		
		// Make sure that such a node actually exists
		if(!node) {
			throwError(BAREError::XML_FAILURE, "Could not find node with name " + valueName);
			return false;
		}
		
		// We're good if we reach here, so its time to just read the value and interpret it, as long as it actually has a value.
		if(std::string(node->value()) != std::string("")) {
			variable = std::vector<float>{};
			
			std::string value = node->value();
			
			// Now we need to actually interpret the string
			// First, figure out how many floats we have
			unsigned int elementCount = std::count(value.begin(), value.end(), '{');
			
			// Now, for every element, actually read it!
			for(unsigned int i = 0; i < elementCount; i++) {
				// Find the first substring that represents our vector value
				std::string floatStr = value.substr(value.find('{')+1, value.find('}') - value.find('{') - 1);
				
				// Interpret the string
				float val = std::stof(floatStr);
				
				// Actually add the values to the vector.
				variable.emplace_back(val);
				
				// Change what our search range actually is.
				value = value.substr(value.find('{')+1, value.size() - value.find('{') - 1);
			}
		}
		
		return true;
	}
	template<>
	bool XMLDataManager::readValue(rapidxml::xml_node<>* parent, std::string valueName, bool& variable) {
		// Find the node that has a name valueName	
		rapidxml::xml_node<>* node = parent->first_node(valueName.c_str());
		
		// Make sure that such a node actually exists
		if(!node) {
			throwError(BAREError::XML_FAILURE, "Could not find node with name " + valueName);
			return false;
		}
		
		// We're good if we reach here, so its time to just read the value and interpret it, as long as it actually has a value.
		if(std::string(node->value()) != std::string("")) {
			variable = (std::string(node->value()) != "0");
		}
		
		return true;
	}
	template<>
	bool XMLDataManager::readValue(rapidxml::xml_node<>* parent, std::string valueName, std::vector<bool>& variable) {
		// Find the node that has a name valueName	
		rapidxml::xml_node<>* node = parent->first_node(valueName.c_str());
		
		// Make sure that such a node actually exists
		if(!node) {
			throwError(BAREError::XML_FAILURE, "Could not find node with name " + valueName);
			return false;
		}
		
		// We're good if we reach here, so its time to just read the value and interpret it, as long as it actually has a value.
		if(std::string(node->value()) != std::string("")) {
			variable = std::vector<bool>{};
			
			std::string value = node->value();
			
			// Now we need to actually interpret the string
			// First, figure out how many bools's we have
			unsigned int elementCount = std::count(value.begin(), value.end(), '{');
			
			// Now, for every element, actually read it!
			for(unsigned int i = 0; i < elementCount; i++) {
				// Find the first substring that represents our value
				std::string boolStr = value.substr(value.find('{')+1, value.find('}') - value.find('{') - 1);
				
				// Interpret the string
				bool val = (boolStr != "0");
				
				// Actually add the values to the vector.
				variable.emplace_back(val);
				
				// Change what our search range actually is.
				value = value.substr(value.find('{')+1, value.size() - value.find('{') - 1);
			}
		}
		
		return true;
	}
	template<>
	bool XMLDataManager::readValue(rapidxml::xml_node<>* parent, std::string valueName, glm::vec2& variable) {
		// Find the node that has a name valueName	
		rapidxml::xml_node<>* node = parent->first_node(valueName.c_str());
		
		// Make sure that such a node actually exists
		if(!node) {
			throwError(BAREError::XML_FAILURE, "Could not find node with name " + valueName);
			return false;
		}
		
		// We're good if we reach here, so its time to just read the value and interpret it, as long as it actually has a value.
		if(std::string(node->value()) != std::string("")) {
			std::string value = node->value();
			
			// Interpret the string
			float val0 = std::stof(value.substr(0, value.find(',')));
			float val1 = std::stof(value.substr(value.find(',') + 1, value.size() - value.find(',') - 1));
			
			// Actually add the values to the vector.
			variable = glm::vec2(val0, val1);
		}
		
		return true;
	}
	template<>
	bool XMLDataManager::readValue(rapidxml::xml_node<>* parent, std::string valueName, std::vector<glm::vec2>& variable) {
		// Find the node that has a name valueName	
		rapidxml::xml_node<>* node = parent->first_node(valueName.c_str());
		
		// Make sure that such a node actually exists
		if(!node) {
			throwError(BAREError::XML_FAILURE, "Could not find node with name " + valueName);
			return false;
		}
		
		// We're good if we reach here, so its time to just read the value and interpret it, as long as it actually has a value.
		if(std::string(node->value()) != std::string("")) {
			variable = std::vector<glm::vec2>{};
			
			std::string value = node->value();
			
			// Now we need to actually interpret the string
			// First, figure out how many vec2's we have
			unsigned int elementCount = std::count(value.begin(), value.end(), '{');
			
			// Now, for every element, actually read it!
			for(unsigned int i = 0; i < elementCount; i++) {
				// Find the first substring that represents our vector, and nip off the brackets on either end
				std::string vec2Str = value.substr(value.find('{')+1, value.find('}') - value.find('{') - 1);
				
				// Interpret the string
				float val0 = std::stof(vec2Str.substr(0, vec2Str.find(',')));
				float val1 = std::stof(vec2Str.substr(vec2Str.find(',') + 1, vec2Str.size() - vec2Str.find(',') - 1));
				
				// Actually add the values to the vector.
				variable.emplace_back(val0, val1);
				
				// Change what our search range actually is.
				value = value.substr(value.find('}')+1, value.size() - value.find('}') - 1);
			}
		}
		
		return true;
	}
	
	Cache<unsigned int, XMLData>* XMLDataManager::getDataCache(std::string dataType) {
		Cache<unsigned int, XMLData>* cache = m_storedData[dataType];
		
		if(!cache) {
			Logger::getInstance()->log("Creating new cache for XML Data: " + dataType);
			cache = m_storedData.createItem(dataType);
		}
		return cache;
	}
	
	void XMLDataManager::clearCache() {
		m_storedData.clear();
		m_dataTypes.clear();
	}
}
