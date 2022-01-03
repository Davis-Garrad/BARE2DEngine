#pragma once

#include "Sound.hpp"
#include "Music.hpp"

namespace BARE2D
{

	/**
	 * @class AudioManager
	 * @file AudioManager.hpp
	 * @brief The AudioManager acts as a friendly wrapper for the SDL_Mixer library. It basically just plays sounds and music, and allows a user to adjust sound levels, etc.
	 */
	class AudioManager
	{
	public:
		static AudioManager* getInstance();
		static void release();

		/**
		 * @brief Initializes all necessary bits and pieces.
		 */
		void init();

		/**
		 * @brief Destroys/quits all necessary bits and pieces.
		 */
		void destroy();

		/**
		 * @brief Plays a sound at a position.
		 * @param sound A reference to the sound that is to be played.
		 * @param fadeTime The number of milliseconds that the sound will take to fade in. Defaults to 0 (no fade).
		 * @param timeOut the number of milliseconds before the sound times out. Defaults to 0 (never).
		 * @param angle The angle (clockwise in degrees, where 0 is directly forward) that the sound is to be played at. Defaults to 0 (directly in front)
		 * @param distance The distance from the camera that the sound should be played (from 0 (very near, loud) to 255 (very distant, quiet))
		 * @return The unsigned integer that represents the sound's ID.
		 */
		unsigned int playSound(Sound& sound, unsigned int fadeTime = 0, unsigned int timeOut = 0, int angle = 0, unsigned char distance = 128);
		/**
		 * @brief Resets the sound's position for positional audio.
		 * @param soundID A reference to the ID that represents the sound to move.
		 * @param angle The angle (clockwise in degrees, where 0 is directly forward) that the sound is to be played at.
		 * @param distance The distance from the camera that the sound should be played (from 0 (very near, loud) to 255 (very distant, quiet))
		 */
		void moveSound(unsigned int& soundID, int angle, unsigned char distance = 128);
		/**
		 * @brief Stops a sound
		 * @param fadeTime The number of milliseconds the sound will take to fade out. Defaults to 0 (no fade).
		 * @param soundID The ID of the sound to stop, given by playSound(...) calls.
		 */
		void stopSound(unsigned int& soundID, unsigned int fadeTime = 0);
		/**
		 * @brief Pauses a sound
		 * @param soundID The ID of the sound to pause, given by playSound(...) calls.
		 */
		void pauseSound(unsigned int& soundID);
		/**
		 * @brief Resumes a paused sound
		 * @param soundID The ID of the sound to resume, given by playSound(...) calls.
		 */
		void resumeSound(unsigned int& soundID);

		/**
		 * @brief Plays some music! Only one "music" can be played at a time.
		 * @param music The music to play
		 * @param fadeTime The number of milliseconds that the sound will take to fade in. Defaults to 0 (no fade).
		 */
		void playMusic(Music& music, unsigned int fadeTime = 0);
		/**
		 * @brief Stops the music
		 * @param fadeTime The number of milliseconds the sound will take to fade out. Defaults to 0 (no fade).
		 */
		void stopMusic(unsigned int fadeTime = 0);
		/**
		 * @brief Pauses the music
		 */
		void pauseMusic();
		/**
		 * @brief Resumes the paused music
		 */
		void resumeMusic();

		/**
		 * @brief Mutes all sounds and music
		 */
		void mute();
		/**
		 * @brief Unmutes all sounds and music
		 */
		void unmute();

		/**
		 * @brief Sets the volume level of all sounds
		 * @param volumeLevel The level of the volume (clamped from 0 (muted) to 255(loud))
		 */
		void setSoundVolume(unsigned char volumeLevel);
		/**
		 * @brief Sets the volume level of all music
		 * @param volumeLevel The level of the volume - 0 is muted, 255 is very loud.
		 */
		void setMusicVolume(unsigned char volumeLevel);
		/**
		 * @brief Sets the modifier of all sound levels - eg., if sounds were set at 40% and music at 60%, setting the master modifier to 50% would set sounds to 20% and music to 30%
		 * @param masterLevel The level of the volume - 0 is muted, 255 is very loud.
		 */
		void setMasterVolumeModifier(unsigned char masterLevel);

		/**
		 * @return True if there is music currently playing, false otherwise.
		 */
		bool isMusicPlaying();

	private:
		AudioManager();
		~AudioManager();

		static AudioManager* m_instance;

		unsigned char m_soundVolume = 255, m_musicVolume = 255, m_masterVolume = 255;
		bool m_muted = false;

	};

}
