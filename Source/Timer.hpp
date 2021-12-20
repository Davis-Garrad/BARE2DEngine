#pragma once

#include <chrono>

namespace BARE2D {

	/**
	 * @class Timer
	 * @brief Not only does the timer keep track of the current time and delta-times, it can do all the "fancy" calculations for timestepping! Uses semi-fixed timestepping, as this engine isn't going to be used for advanced physics!
	 */
	class Timer
	{
	public:
		Timer();
		
		/**
		 * @brief IntegrateFrame gives an indication of whether we should be updatign again with dt or if we should exit our loop
		 * @return True if we should continue to integrate the update function or False if we're good.
		 */
		bool integrateFrame();
		
		/**
		 * @return The dt variable for update integration. 
		 */
		double getDeltaTime();
		
		/**
		 * @brief To be called at the start of a frame
		 */
		void startTimer();
		
		/**
		 * @brief To be called at the end of a frame.
		 */
		void endTimer();
		
		/**
		 * @brief Sets the maximum value of dt. Naturally, there is no minimum. This doesn't take away from accuracy. Setting a maximum means we subdivide the frames if necessary.
		 */
		void setDeltaTimeLimit(double minDt);
		
	private:
		double m_minDeltaTime;
		double m_frameTime;
		std::chrono::steady_clock::time_point m_startTime;

	};

}
