#include "Filesystem.hpp"

namespace fs = boost::filesystem;

namespace BARE2D {

std::vector<std::string> Filesystem::getDirectoriesIn(std::string path)
{
    std::vector<std::string> ret;

    fs::path filepath(path);

    if(fs::exists(filepath) && fs::is_directory(filepath))
	{
	    for(fs::directory_iterator it(filepath); it != fs::directory_iterator(); it++)
		{
		    auto filename = static_cast<std::string>(it->path().filename().string());

		    if(fs::is_directory(filename))
			{
			    ret.push_back(filename);
		    }
		}
    }

    return ret;
}

std::vector<std::string> Filesystem::getFilesIn(std::string path)
{
    std::vector<std::string> ret;

    fs::path filepath(path);

    if(fs::exists(filepath) && fs::is_directory(filepath))
	{
	    for(fs::directory_iterator it(filepath); it != fs::directory_iterator(); it++)
		{
		    auto filename = static_cast<std::string>(it->path().filename().string());

		    if(fs::is_regular_file(it->status()))
			{
			    ret.push_back(filename);
		    }
		}
    }

    return ret;
}

std::string Filesystem::getWorkingDirectory()
{
    return fs::current_path().string();
}

}  // namespace BARE2D
