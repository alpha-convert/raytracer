#include "Audio.h"
#include "macros.h"
#include <cmath>


void Audio::Callback(void *udata, uint8_t *stream, int len){
	SDL_LockAudio();
	for(int i = 0; i < len; ++i){
		stream[i] = i % 255;
	}
	SDL_UnlockAudio();
}

Audio::Audio(){
	if (!SDL_WasInit(SDL_INIT_AUDIO)) {
		SDL_Init(SDL_INIT_AUDIO);
	}
	SDL_AudioSpec wanted;
	wanted.freq = 22050;
	wanted.format = AUDIO_S16;
	wanted.channels = 2;
	wanted.samples = 1024;
	wanted.callback = &Audio::Callback;
	wanted.userdata = NULL;

	if(SDL_OpenAudio(&wanted,&spec) < 0){
		fprintf(stderr,"Couldn't open audio: %s\n",SDL_GetError());
	}

	SDL_PauseAudio(0);
}


Audio::~Audio(){
	SDL_AudioQuit();
}
