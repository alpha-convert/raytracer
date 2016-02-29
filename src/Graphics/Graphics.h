/*
 * Graphics.h
 *
 *  Created on: Oct 28, 2015
 *      Author: Admin
 */

#ifndef GRAPHICS_GRAPHICS_H_
#define GRAPHICS_GRAPHICS_H_

#include <vector>

#include "Vec3/Vec3.h"
#include "../Color/Color.h"

struct SDL_Window;
struct SDL_Surface;
struct SDL_Renderer;
struct SDL_Texture;
class Color;

class Graphics {
public:
	SDL_Window *window;
	SDL_Renderer *renderer;



	unsigned int width;
	unsigned int height;

	Graphics(uint32_t width, uint32_t height, const char *);
	void Update();
	void Clear();

	inline void SpaceLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const Color &c);
	void ProjectVec3(const Vec3 &v, const Color &c, int32_t scalar = 1);
	void LineFromVec(const Vec3 &v1, const Vec3 &v2, const Color &c);

	void Line(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const Color &c);
	inline void PutPixel(int32_t x, int32_t y, const Color &c);
	inline void SetColor(const Color &c);

	void Polygon(const std::vector<const Vertex>& poly, const Color& c, const Quat& q = NULL);
	

	virtual ~Graphics();

private:

uint32_t GetRawPixelFromSurface(uint32_t x, uint32_t y, const SDL_Surface* const surface);
Color SDLColorToColor(uint32_t n);

};

#endif /* GRAPHICS_GRAPHICS_H_ */
