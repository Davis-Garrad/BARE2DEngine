#include "IOManager.hpp"

#include "Logger.hpp"

namespace BARE2D {

	template<typename T>
	bool IOManager::readFileToBuffer(std::string& filepath, std::vector<T>& buf, std::ios_base::openmode mode/** = std::ios::binary*/) {
		std::ifstream file(filepath, mode);
		
		if(file.fail()) {
			Logger::getInstance()->log("Failed to load file to buffer: " + filepath);
			return false;
		}
		
		// Seek to the end to get the file size
		file.seekg(0, std::ios::end);
		unsigned int fileSize = (unsigned int)file.tellg();
		
		// Go back to the start
		file.seekg(0, std::ios::beg);
		fileSize -= file.tellg();
		
		// Now read fileSize bytes
		buf.resize(fileSize);
		file.read((char*)&(buf[0]), fileSize);
		
		// Close it up and return! Job done.
		file.close();
		
		return true;
	}
	
	bool IOManager::readFileToBuffer(const std::string& filepath, std::string& buf, std::ios_base::openmode mode/** = std::ios::binary*/) {
		std::ifstream file(filepath, mode);
		
		if(file.fail()) {
			Logger::getInstance()->log("Failed to load file to buffer: " + filepath);
			return false;
		}
		
		// Seek to the end to get the file size
		file.seekg(0, std::ios::end);
		unsigned int fileSize = (unsigned int)file.tellg();
		
		// Go back to the start
		file.seekg(0, std::ios::beg);
		fileSize -= file.tellg();
		
		// Now read fileSize bytes
		file.read((char*)&(buf[0]), fileSize);
		
		// Close it up and return! Job done.
		file.close();
		
		return true;
	}

}
