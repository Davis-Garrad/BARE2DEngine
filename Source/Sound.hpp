#pragma once

#include <SDL2/SDL_mixer.h>

namespace BARE2D {

	struct Sound {
		Mix_Chunk* chunk = nullptr;
	};

}

