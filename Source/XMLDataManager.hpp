#pragma once

#include <string>
#include <rapidxml/rapidxml.hpp>
#include <glm/glm.hpp>

#include "XMLDataTypes.hpp"

namespace BARE2D {
	
	/**
	 * @class XMLDataManager
	 * @brief A singleton class that statically manages all XML data, including read and write operations.
	 */
	class XMLDataManager
	{
		friend class XMLData;
	
	public:
		/**
		 * @brief Loads all of the files from the filepath that end in .xml to the caches. Does not clear caches.
		 * @param filepath The path of the folder of files to load, or the path of an actual singular file to load.
		 */
		static void loadXML(std::string filepath);
		
		/**
		 * @brief Writes all of the currently cached data to the data's respective files in a folder at filepath. Does not clear caches.
		 * @param filepath The path of the folder of files to save.
		 */
		static void saveXML(std::string filepath);
		
		/**
		 * @brief Adds a type of data that can be read. Make sure that the custom data type's nodeName is set.
		 */
		template<typename T>
		static void addDataType();
		
		/**
		 * @brief Adds a piece of data to the cache, in the appropriate sub-cache.
		 * @param data A pointer to the data to be added. data->nodeName must be set for appropriate sub-caching.
		 */
		static void addData(XMLData* data);
		
		/**
		 * @brief Finds some data in the subcache.
		 * @param dataType The string type of the data to get.
		 * @param key The ID of the data.
		 * @return A copy of the data, as nobody should be modifying the cached data.
		 */
		template<typename T>
		static T getData(std::string dataType, unsigned int key);
		
		/**
		 * @param dataType The string type of the data to get info on.
		 * @return The number of elements of the type of data.
		 */
		static unsigned int getDataCount(std::string dataType);
		
		/**
		 * @brief Clears the various caches and subcaches that the class uses. Useful for refreshes.
		 */
		static void clearCache();
		
		/**
		 * @brief Provides a copy of some data type added by the addDataType function
		 * @param dataType The string identifier for the type of data. In other words, nodeName
		 * @return A copy of some type of data, complete with nodeName and attributes set.
		 */
		static XMLData getDataType(std::string dataType);

	private:
		/**
		 * @brief Writes a single subcache of data to a single file
		 * @param file The file to write the data to
		 * @param data A pointer to the subcache to write
		 */
		static void writeXMLData(std::ofstream& file, Cache<unsigned int, XMLData>* data);
		/**
		 * @brief Reads a single subcache from a single file.
		 * @param file The file to read from.
		 * @param dataType The nodeName of the data to read. This will be the key for the cache.
		 */
		static void readXMLData(std::ifstream& file, std::string dataType);
	
		/**
		 * @brief Reads a value from a node. Templated for almost any primitive.
		 * @param parent A pointer to the node of the parent data.
		 * @param valueName The "nodeName" of the value to be read.
		 * @param variable The return variable.
		 * @return True on success, false on failure.
		 */
		template<typename T>
		static bool readValue(rapidxml::xml_node<>* parent, std::string valueName, T& variable);
	
		/**
		 * @brief Returns a cache for a certain type of data
		 * @param dataType The string type of the data
		 * @return A pointer to the subcache.
		 */
		static Cache<unsigned int, XMLData>* getDataCache(std::string dataType);
		
		static Cache<std::string, Cache<unsigned int, XMLData>> m_storedData;
		static Cache<std::string, XMLData> m_dataTypes; 

	};

}

#include "XMLDataManager.tcc"

