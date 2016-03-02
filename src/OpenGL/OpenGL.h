#ifndef OPENGL_H_
#define OPENGL_H_ 
#include <stdint.h>
struct SDL_Window;
typedef void *SDL_GLContext;

class OpenGL{
	
	SDL_Window *window;
	SDL_GLContext ctx;
public:
	OpenGL(uint32_t width, uint32_t height, const char *name);
	virtual ~OpenGL();
};

#endif
