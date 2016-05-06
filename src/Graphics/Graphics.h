/*
 * Graphics.h
 *
 *  Created on: Oct 28, 2015
 *      Author: Admin
 */

#ifndef GRAPHICS_GRAPHICS_H_
#define GRAPHICS_GRAPHICS_H_

#include <vector>
#include <functional>
#include <cstdint>
#include <SDL2/SDL.h>

#include "Math/Vec2/Vec2.h"
#include "Math/Vec3/Vec3.h"
#include "Math/Vec4/Vec4.h"
#include "Math/Mat4/Mat4.h"
#include "Color/Color.h"
#include "Light/Light.h"
#include "Ray/Ray.h"
#include "Sphere/Sphere.h"
#include "Vertex/Vertex.h"
#include "macros.h"

//struct SDL_Window;
//struct SDL_Surface;
//struct SDL_Renderer;
//struct SDL_Texture;
//struct SDL_Rect;
//struct SDL_Point;
//class Color;

/**
 * @class Graphics
 * @brief Wrapper around SDL graphics
 * @author Joseph Cutler
 *
 * The SDL graphics library (while very elegant and cross platform) isn't really meant for C++ use.
 * It relies on a lot of pointer passing and things that you'd usually consider outdated or archaic in modern C++.
 * This class wraps the library, providing more user-friendly methods and functions.
 */

typedef struct DeferredRenderPoint{
	SDL_Point p;
	Color c;
}DeferredRenderPoint;

typedef struct DeferredRenderRect{
	SDL_Rect r;
	Color c;
} DeferredRenderRect;

typedef struct DeferredRenderFilledRect{
	SDL_Rect r;
	Color c;
} DeferredRenderFilledRect;

typedef struct DeferredRenderLine{
	int x1, y1,x2,y2;
	Color c;
} DeferredRenderLine;

class Graphics {
	public:

		///Width of window
		uint32_t width;
		///Height of window
		uint32_t height;

		float vertical_angle;
		float horizontal_angle;

		/**
		 * @brief Constructs and opens a window
		 *
		 * While very powerful and more user-friendly than OpenGL or D3D, SDL still requires some verbose and tedious setup before you can get to the good stuff.
		 * One of the goals of this class is to provide a one line way to safely allocate all nessicary resources and display the window. This takes advantage of C++'s wonderful RAII philosophy.
		 * This also means that the user of this class doesn't need to worry about destroy resources and memory after the window closes. All allocated memory is freed in the constructor.
		 *
		 * @param width Width of the window that is opened when this object is constructed
		 * @param height Height of the window that is opened when this object is constructed
		 * @param name Title of the window
		 */
		Graphics(uint32_t width, uint32_t height, const char *name);

		/**
		 * @brief Updates the window with the drawings created since the last update (or construction)
		 * @note This method must be called beofre any drawing will be visible.
		 */
		void Update();
		/**
		 * @brief Clear the screen
		 */
		void Clear();

		/**
		 * @brief Draw line such that (0,0) is the center of the screen
		 * @param x1 x component of endpoint 1
		 * @param y1 y component of endpoint 1
		 * @param x2 x component of endpoint 2
		 * @param y2 y component of endpoint 2
		 */
		void SpaceLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const Color &c);

		/**
		 * @brief Draw a Vec3 to the screen from the origin.
		 * @param v endpoint of the line
		 * @param scalar scaling factor of the line. Unit vectors may be mard to see, so passing a larger number here will make it easier to see
		 */
		void ProjectVec3(const Vec3 &v, const Color &c, int32_t scalar = 1);

		/**
		 * @brief draw a line between v1 and v2
		 *	
		 */
		void LineFromVec(const Vec4 &v1, const Vec3 &v2, const Color &c);

		void Line(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const Color &c);

		void PutPixel(int32_t x, int32_t y, const Color &c);
		inline void SetColor(const Color &c);

		void Triangle(const std::array<Vec4,3>& tri, const Color& c);
		void Triangle(const std::array<Vec4,3>& tri, const Color& c, const Color &fill);

		//std::transform
		void Polygon(const std::vector<Vertex>& poly, const Color& c);
		void Polygon(const std::vector<Vertex>& poly, const Color& c, const Quat& rotation);

		void Polygon(const std::vector<Vertex>& poly, const Color& c, const std::function<Vec4(Vec4)> transform);

		/**
		 * I hate this pattern, but we have to use it.
		 */
		Color Trace(const std::vector<Object *> &scene, const std::vector<Light> lights, const Ray &cast_ray, const Vec3 &camera_pos,unsigned recurse_times) const;
		Color Trace(const std::vector<Object *> &scene, const std::vector<Light>, const Ray &cast_ray, unsigned recurse_times) const;
		Object* GetClosestObject(const std::vector<Object *> &objects, const Ray &cast_ray, float &dist) const;
		Object* GetClosestObject(const std::vector<Object *> &objects, const Ray &cast_ray) const;

		virtual ~Graphics();

	private:

		std::vector<DeferredRenderPoint> points_to_draw;
		std::vector<DeferredRenderLine> lines_to_draw;
		std::vector<DeferredRenderRect> rects_to_draw;
		std::vector<DeferredRenderFilledRect> filled_rects_to_draw;
		
		SDL_Window *window;
		SDL_Renderer *renderer;
		uint32_t GetRawPixelFromSurface(uint32_t x, uint32_t y, const SDL_Surface* const surface) const;
		Color SDLColorToColor(uint32_t n) const;

};

#endif /* GRAPHICS_GRAPHICS_H_ */
