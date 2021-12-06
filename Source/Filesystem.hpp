#pragma once

#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>
#undef BOOST_FILESYSTEM_NO_DEPRECATED

namespace BARE2D {

	class Filesystem
	{
	public:
		static std::vector<std::string> getDirectoriesIn(std::string path);
		static std::vector<std::string> getFilesIn(std::string path);

	};

}

