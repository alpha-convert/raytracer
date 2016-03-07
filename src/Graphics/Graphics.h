/*
 * Graphics.h
 *
 *  Created on: Oct 28, 2015
 *      Author: Admin
 */

#ifndef GRAPHICS_GRAPHICS_H_
#define GRAPHICS_GRAPHICS_H_

#include <vector>

#include "Math/Vec3/Vec3.h"
#include "Math/Vec4/Vec4.h"
#include "Math/Mat4/Mat4.h"
#include "Color/Color.h"
#include "Vertex/Vertex.h"

struct SDL_Window;
struct SDL_Surface;
struct SDL_Renderer;
struct SDL_Texture;
class Color;

typedef struct ScreenPoint{int x, y;} ScreenPoint;

class Graphics {
	public:
		SDL_Window *window;
		SDL_Renderer *renderer;

		uint32_t width;
		uint32_t height;

		float vertical_angle;
		float horizontal_angle;

		Graphics(uint32_t width, uint32_t height, const char *);
		void Update();
		void Clear();

		inline void SpaceLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const Color &c) const;
		void ProjectVec3(const Vec3 &v, const Color &c, int32_t scalar = 1) const;
		void LineFromVec(const Vec3 &v1, const Vec3 &v2, const Color &c) const;

		void Line(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const Color &c) const;
		inline void PutPixel(int32_t x, int32_t y, const Color &c) const;
		inline void SetColor(const Color &c) const;

		void Triangle(const std::array<Vec4,3>& tri, const Color& c) const;
		void Triangle(const std::array<Vec4,3>& tri, const Color& c, const Color &fill) const;

		void Polygon(const std::vector<Vertex>& poly, const Color& c) const;
		void Polygon(const std::vector<Vertex>& poly, const Color& c, const Quat& rotation) const;

		virtual ~Graphics();

	private:

		uint32_t GetRawPixelFromSurface(uint32_t x, uint32_t y, const SDL_Surface* const surface);
		Color SDLColorToColor(uint32_t n) const;


		ScreenPoint Vec3ToScreenPoint(const Vec3& v);
		Vec3		ScreenPointToVec3(const ScreenPoint &p);

};

#endif /* GRAPHICS_GRAPHICS_H_ */
