#include "AudioManager.hpp"

#include <SDL2/SDL_mixer.h>

#include "BAREErrors.hpp"

namespace BARE2D
{

	AudioManager* AudioManager::m_instance = nullptr;

	AudioManager* AudioManager::getInstance()
	{
		if(!m_instance) {
			m_instance = new AudioManager();
		}
		return m_instance;
	}

	void AudioManager::release()
	{
		if(m_instance) {
			m_instance->destroy();
			delete m_instance;
		}
	}

	AudioManager::AudioManager()
	{
	}

	AudioManager::~AudioManager()
	{
	}


	void AudioManager::init()
	{
		// Load all of the DLLs which may or may not exist on our system.
		int initedFlags = Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG);

		// Check each flag, and report if it couldn't be inited.
		if(!(initedFlags & MIX_INIT_FLAC)) {
			// Couldn't init .flac extension. report
			throwError(BAREError::SDL_MIXER_FLAC_FAILURE, Mix_GetError());
		}
		if(!(initedFlags & MIX_INIT_MOD)) {
			// Couldn't init .mod extension. report
			throwError(BAREError::SDL_MIXER_MOD_FAILURE, Mix_GetError());
		}
		if(!(initedFlags & MIX_INIT_MP3)) {
			// Couldn't init .mp3 extension. report
			throwError(BAREError::SDL_MIXER_MP3_FAILURE, Mix_GetError());
		}
		if(!(initedFlags & MIX_INIT_OGG)) {
			// Couldn't init .ogg extension. report
			throwError(BAREError::SDL_MIXER_OGG_FAILURE, Mix_GetError());
		}

		// Now actually open the API and allow calls to the library
		// The default frequency is a decent middleground for weaker and stronger CPUs but still sounds good
		// The default format is "Signed 16-bit samples, in system byte order"
		// There will be 2 output channels open (for stereo) - this is different than the mixer channels, which are what sounds are actually played in
		// Each chunk will be of size 1024 - this is a decent size as our hooks will not be called too often, but audio won't skip either.
		Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);

		// Arbitrarily allocate a bunch of channels.
		Mix_AllocateChannels(32); // 32 is almost definitely going to be enough for anything reasonable. This can be jacked up, however.
	}

	void AudioManager::destroy()
	{
		// Clean up SDL
		// Get how many times we called Mix_OpenAudio (the dummies store the frequency, format, and the number of channels)
		int numTimesOpened, dummyA, dummyC;
		Uint16 dummyB;
		numTimesOpened = Mix_QuerySpec(&dummyA, &dummyB, &dummyC);
		// Check for errors
		if(numTimesOpened == 0) {
			throwError(BAREError::SDL_MIXER_CLOSE_FAILURE, Mix_GetError());
		}

		// Actually close each mixer.
		for(unsigned int i = 0; i < numTimesOpened; i++)
			Mix_CloseAudio();

		while(Mix_Init(0)) // This makes sure that no matter how many DLLs are loaded, we quit them all.
			Mix_Quit();
	}

	unsigned int AudioManager::playSound(Sound& sound, unsigned int fadeTime, unsigned int timeOut, int angle, unsigned char distance)
	{
		int channel = -1;
		if(fadeTime > 0) {
			if(timeOut > 0) {
				// Fade + Timeout
				// -1 represents the first available chunk
				// It will loop 0 times
				channel = Mix_FadeInChannelTimed(-1, sound.chunk, 0, fadeTime, timeOut);
			} else {
				// Just Fade - no timeout
				// -1 represents the first available chunk
				channel = Mix_FadeInChannel(-1, sound.chunk, 0, fadeTime);
			}
		} else {
			if(timeOut > 0) {
				channel = Mix_PlayChannelTimed(-1, sound.chunk, 0, timeOut);
			} else {
				channel = Mix_PlayChannel(-1, sound.chunk, 0);
			}
		}
		if(channel == -1) {
			throwFatalError(BAREError::SDL_MIXER_SOUND_FAILURE, "Failed to play sound: " + std::string(Mix_GetError()));
		}
		return (unsigned int)channel;
	}

	void AudioManager::moveSound(unsigned int& soundID, int angle, unsigned char distance)
	{
		if(!Mix_SetPosition(soundID, angle, distance)) {
			throwFatalError(BAREError::SDL_MIXER_SOUND_FAILURE, "Failed to move sound: " + std::string(Mix_GetError()));
		}
	}

	void AudioManager::stopSound(unsigned int& soundID, unsigned int fadeTime)
	{
		if(fadeTime > 0) {
			Mix_FadeOutChannel(soundID, fadeTime);
		} else {
			Mix_HaltChannel(soundID);
		}
	}

	void AudioManager::pauseSound(unsigned int& soundID)
	{
		Mix_Pause(soundID);
	}

	void AudioManager::resumeSound(unsigned int& soundID)
	{
		Mix_Resume(soundID);
	}

	void AudioManager::playMusic(Music& music, unsigned int fadeTime)
	{
		int error = -1;
		if(fadeTime > 0) {
			// Never loops, fades.
			error = Mix_FadeInMusic(music.music, 0, fadeTime);
		} else {
			// Never loops, doesn't fade.
			error = Mix_PlayMusic(music.music, 0);
		}
		if(error == -1) {
			throwFatalError(BAREError::SDL_MIXER_SOUND_FAILURE, "Failed to play music: " + std::string(Mix_GetError()));
		}
	}

	void AudioManager::stopMusic(unsigned int fadeTime)
	{
		if(fadeTime > 0) {
			Mix_FadeOutMusic(fadeTime);
		} else {
			Mix_HaltMusic();
		}
	}

	void AudioManager::pauseMusic()
	{
		Mix_PauseMusic();
	}

	void AudioManager::resumeMusic()
	{
		Mix_ResumeMusic();
	}

	void AudioManager::mute()
	{
		if(m_muted) return;

		// Get the original volumes and set the current volumes to 0 (muted)
		m_soundVolume = Mix_Volume(-1, 0);
		m_musicVolume = Mix_VolumeMusic(0);
		m_muted = true;
	}

	void AudioManager::unmute()
	{
		if(!m_muted) return;
		m_muted = false;

		Mix_Volume(-1, m_soundVolume);
		Mix_VolumeMusic(m_musicVolume);
	}

	void AudioManager::setSoundVolume(unsigned char volumeLevel)
	{
		m_soundVolume = volumeLevel * m_masterVolume;
		Mix_Volume(-1, m_soundVolume / (255 * 255) * 128); // Normalize the volume from 0-128 (that's the mixer max)
	}

	void AudioManager::setMusicVolume(unsigned char volumeLevel)
	{
		m_musicVolume = volumeLevel * m_masterVolume;
		Mix_VolumeMusic(m_musicVolume / (255 * 255) * 128); // Normalize the volume from 0-128 (that's the mixer max)
	}

	void AudioManager::setMasterVolumeModifier(unsigned char masterLevel)
	{
		// First, get the oldl music and sound volumes before the master adjustment.
		m_musicVolume /= m_masterVolume;
		m_soundVolume /= m_masterVolume;

		m_masterVolume = masterLevel;

		// Now reset the new music and sound volumes
		setMusicVolume(m_musicVolume);
		setSoundVolume(m_soundVolume);
	}

	bool AudioManager::isMusicPlaying()
	{
		return Mix_PlayingMusic();
	}

}
