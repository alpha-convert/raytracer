#include "OpenGL.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

OpenGL::OpenGL(uint32_t width, uint32_t height, const char *name){
	if(!SDL_WasInit(SDL_INIT_VIDEO)){
		SDL_Init(SDL_INIT_VIDEO);
	}
	this->window = SDL_CreateWindow(name,
									SDL_WINDOWPOS_UNDEFINED,
									SDL_WINDOWPOS_UNDEFINED,
									width, height,
									SDL_WINDOW_OPENGL);
	if(!this->window){
		fprintf(stderr,"Error creating window: %s",SDL_GetError());
	}	

	this->ctx = SDL_GL_CreateContext(window);

	if(!this->ctx){
		fprintf(stderr,"Error creating OpenGL context: %s",SDL_GetError());
	}	

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL,1);

}


OpenGL::~OpenGL(){
	SDL_GL_DeleteContext(ctx);
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}
