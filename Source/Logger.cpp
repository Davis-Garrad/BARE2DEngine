#include "Logger.hpp"

#include <chrono>

#include "BAREErrors.hpp"

namespace BARE2D {

	Logger* Logger::m_instance = nullptr;

	Logger::Logger()
	{
		// Open the log file!
		m_logFile.open("GameLog.txt", std::ios::trunc);
		
		// Make sure we can load it.
		if(m_logFile.fail()) {
			throwFatalError(BAREError::LOGGER_FAILURE, "Logger failed to open log file.");
			return;
		}
		
		// Just to timestamp the log
		auto timeA = std::chrono::system_clock::now();
		auto timeB = std::chrono::system_clock::to_time_t(timeA);
		
		std::string date = std::ctime(&timeB);
		date.pop_back();
		
		m_logFile << "\n\n\n### LOG: " << date << " ###\n\n";
		m_logFile << "Thanks for using BARE2D! Original engine by Davis Garrad\n\n";
		m_logFile.flush();
	}

	Logger* Logger::getInstance()
	{
		if (m_instance == nullptr) {
			m_instance = new Logger();
		}
		return m_instance;
	}
	
	void Logger::log(std::string message, bool important/** = false*/) {
		if(important) {
			message = "\n### " + message + " ###\n";
		}
		message = message + "\n";
		m_logFile << message;
		std::printf("%s", message.c_str());
		m_logFile.flush();
	}

}
