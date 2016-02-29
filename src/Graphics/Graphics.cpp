/*
 * Graphics.cpp
 *
 *  Created on: Oct 28, 2015
 *      Author: Admin
 */

#include "Graphics.h"
#include <SDL2/SDL.h>
#include <execinfo.h>

#include <math.h>
#include <stdint.h>
#include <stdlib.h>

//General graphics flow:

Graphics::Graphics(uint32_t width, uint32_t height, const char *name) {
	if (!SDL_WasInit(SDL_INIT_VIDEO)) {
		SDL_Init(SDL_INIT_VIDEO);
	}
	this->width = width;
	this->height = height;

	this->window = SDL_CreateWindow(name,
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,
			SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
	if (!this->window) {
		fprintf(stderr, "Error creating window, %s\n", SDL_GetError());
	}


	this->renderer = SDL_CreateRenderer(this->window, -1,
			SDL_RENDERER_ACCELERATED);
	if (!this->renderer) {
		printf("Error creating renderer: %s", SDL_GetError());

	}

}

void Graphics::Clear() {
	//for(int y = 0; y < this->height; ++y){
	//	for(int x = 0; x < this->width; ++x){
	//		this->PutPixel(x,y,Color(255,255,255));
	//	}
	//}
	SetColor(Color::White);
	SDL_RenderClear(this->renderer);
}

void Graphics::Update() {
	SDL_UpdateWindowSurface(this->window);
	SDL_RenderPresent(this->renderer);

}


void Graphics::ProjectVec3(const Vec3 &v, const Color &c, int scalar) {
	this->SpaceLine(0, 0, v.dot(Vec3::I) * scalar, v.dot(Vec3::J) * scalar, c);
}

void Graphics::LineFromVec(const Vec3 &v1, const Vec3 &v2, const Color &c) {
	this->SpaceLine(v1.x, v1.y, v2.x, v2.y, c);
}


inline void Graphics::SpaceLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2,
		const Color &c) {
	Line(this->width / 2 + x1, this->height / 2 - y1, this->width / 2 + x2,
			this->height / 2 - y2, c);
}

void Graphics::Line(int32_t x1, int y1, int x2, int y2, const Color &c) {
	SetColor(c);
	SDL_RenderDrawLine(this->renderer, x1, y1, x2, y2);

}



inline void Graphics::PutPixel(int x, int y, const Color &c) {
	if (!(x > this->width && x < 0 && y > this->height && y < 0)) {
		SetColor(c);
		SDL_RenderDrawPoint(this->renderer, x, y);
	} else {
		fprintf(stderr,
				"Error putting pixel at (%d,%d) with color (%d,%d,%d)\n", x, y,
				c.r, c.g, c.b);
	}
}

Graphics::~Graphics() {
	// TODO Auto-generated destructor stub
//	SDL_FreeSurface(surface);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(this->renderer);
	SDL_Quit();
}

void Graphics::SetColor(const Color &c){
	SDL_SetRenderDrawColor(this->renderer, c.r, c.g, c.b, 255);

}

Color Graphics::SDLColorToColor(uint32_t n){
	Color c =Color(0,0,0);
	c.r = n & 0xff000000;
	c.g = n & 0xff0000;
	c.b = n & 0xff00;
	return c;
}

void Graphics::Polygon(const std::vector<const Vertex>& poly, Color& c);



