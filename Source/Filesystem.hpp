#pragma once

#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>
#undef BOOST_FILESYSTEM_NO_DEPRECATED

namespace BARE2D {

	class Filesystem {
		public:
			/**
			 * @brief Gets all the names of directories at the given path
			 * @param path The path to check
			 * @return A vector of string names of directories
			 */
			static std::vector<std::string> getDirectoriesIn(std::string path);

			/**
			 * @brief Gets all the names of files at the given path
			 * @param path The path to check
			 * @return A vector of string names of files
			 */
			static std::vector<std::string> getFilesIn(std::string path);

			/**
			 * @return The path to the program's working directory.
			 */
			static std::string getWorkingDirectory();
	};

}  // namespace BARE2D
