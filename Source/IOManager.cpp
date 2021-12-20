#include "IOManager.hpp"

#include "Logger.hpp"

namespace BARE2D {

	// Templated function defaults are in .tcc
	
	bool IOManager::readFileToBuffer(const char* filepath, std::string& buf, std::ios_base::openmode mode/** = std::ios::binary*/) {
		std::ifstream file(filepath, mode);
		
		if(file.fail()) {
			Logger::getInstance()->log("Failed to load file to buffer: " + std::string(filepath));
			return false;
		}
		
		// Seek to the end to get the file size
		file.seekg(0, std::ios::end);
		unsigned int fileSize = (unsigned int)file.tellg();
		
		// Go back to the start
		file.seekg(0, std::ios::beg);
		fileSize -= (unsigned int)file.tellg();
		
		// Resize for efficiency!
		buf.resize(fileSize);
		
		// Now read fileSize bytes
		file.read((char*)&(buf[0]), fileSize);
		
		// Close it up and return! Job done.
		file.close();
		
		return true;
	}

}
