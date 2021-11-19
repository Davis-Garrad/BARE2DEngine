#pragma once

#include <string>
#include <vector>
#include <fstream>

namespace BARE2D {

	class IOManager
	{
	public:
		/**
		 * @brief Loads a file into a buffer
		 * @param filepath The filepath to be read from
		 * @param buf The buffer to read to
		 * @return Returns false if there was a problem reading the file, true otherwise.
		 */
		template<typename T>
		static bool readFileToBuffer(std::string& filepath, std::vector<T>& buf, std::ios_base::openmode mode = std::ios::binary);
		
		
		
		static bool readFileToBuffer(const std::string& filepath, std::string& buf, std::ios_base::openmode mode = std::ios::binary);
		
		// Other functions...

	};

}

