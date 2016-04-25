#pragma once
/***
* @Author Joseph Cutler
* @Date April 25, 2016
* @Copyright WTFPL
*/
#include <SDL2/SDL.h>
class Audio {
public:
	Audio();
	~Audio();
private:
	SDL_AudioSpec spec;
	static void Callback(void *udata, uint8_t *stream, int len);
};
