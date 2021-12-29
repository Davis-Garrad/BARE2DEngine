#pragma once

#include "Sound.hpp"
#include "Music.hpp"

namespace BARE2D {

	/**
	 * @class AudioManager
	 * @file AudioManager.hpp
	 * @brief The AudioManager acts as a friendly wrapper for the SDL_Mixer library. It basically just plays sounds and music, and allows a user to adjust sound levels, etc.
	 */
	class AudioManager
	{
	public:
		AudioManager();
		~AudioManager();

		unsigned int playSound(Sound& sound);
		void stopSound(unsigned int& soundID);
		void pauseSound(unsigned int& soundID);
		void resumeSound(unsigned int& soundID);
		
		unsigned int playMusic(Music& music);
		void stopMusic(unsigned int& musicID);
		void pauseMusic(unsigned int& musicID);
		void resumeMusic(unsigned int& musicID);
		
		void mute();
		void unmute();
		
		void setSoundVolume(float& volumeLevel);
		void setMusicVolume(float& volumeLevel);
		void setMasterVolumeModifier(float& masterLevel);

	};

}

