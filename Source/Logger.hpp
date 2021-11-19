#pragma once

#include <string>
#include <fstream>

namespace BARE2D {

	/**
	 * @class Logger
	 * @brief For general purpose logging, this is the logger! It is a singleton class.
	 */
	class Logger
	{
	public:
		static Logger* getInstance();
		
		/**
		 * @brief Logs a message to a file and the terminal
		 * @param message The message to log
		 * @param important If this is set to true, the message will be surrounded with hashes. This implies importance!
		 */
		void log(std::string message, bool important = false);

	private:
		Logger();
		~Logger();
		
		// The stream for the file we're going to write to.
		std::ofstream m_logFile;
		
		static Logger* m_instance;

	};

}
