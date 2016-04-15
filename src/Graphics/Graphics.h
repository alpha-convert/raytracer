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

#include "Math/Vec2/Vec2.h"
#include "Math/Vec3/Vec3.h"
#include "Math/Vec4/Vec4.h"
#include "Math/Mat4/Mat4.h"
#include "Color/Color.h"
#include "Ray/Ray.h"
#include "Sphere/Sphere.h"
#include "Vertex/Vertex.h"
#include "macros.h"

struct SDL_Window;
struct SDL_Surface;
struct SDL_Renderer;
struct SDL_Texture;
class Color;

///OpenGL style screen point [-1,1]
class ConventionalPoint{
	ConventionalPoint(int8_t x, int8_t y);
private:
	int8_t x, y;
};

/**
 * @class Graphics
 * @brief Wrapper around SDL graphics
 * @author Joseph Cutler
 *
 * The SDL graphics library (while very elegant and cross platform) isn't really meant for C++ use.
 * It relies on a lot of pointer passing and things that you'd usually consider outdated or archaic in modern C++.
 * This class wraps the library, providing more user-friendly methods and functions.
 */
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
		 */
		Graphics(uint32_t width, uint32_t height, const char *);

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
		 */
		void SpaceLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const Color &c) const;

		/**
		 * @brief Draw a Vec3 to the screen from the origin.
		 */
		void ProjectVec3(const Vec3 &v, const Color &c, int32_t scalar = 1) const;

		/**
		 * @brief draw a line between v1 and v2
		 *	
		 */
		void LineFromVec(const Vec3 &v1, const Vec3 &v2, const Color &c) const;

		void Line(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const Color &c) const;

		void Bezier(const Vec2 &begin, const Vec2 &end, const Vec2 &control, const Color &c = Color::Black) const;

		void PutPixel(int32_t x, int32_t y, const Color &c) const;
		inline void SetColor(const Color &c) const;

		void Triangle(const std::array<Vec4,3>& tri, const Color& c) const;
		void Triangle(const std::array<Vec4,3>& tri, const Color& c, const Color &fill) const;

		//std::transform
		void Polygon(const std::vector<Vertex>& poly, const Color& c) const;
		void Polygon(const std::vector<Vertex>& poly, const Color& c, const Quat& rotation) const;

		void Polygon(const std::vector<Vertex>& poly, const Color& c, const std::function<Vec4(Vec4)> transform);

		//TODO: change to general object ptr
		Color Trace(int x, int y, const std::vector<Sphere> &scene, const Vec3& camera_pos, const Vec3 &screen_top_left) const;

		virtual ~Graphics();

	private:
		
		SDL_Window *window;
		SDL_Renderer *renderer;
		uint32_t GetRawPixelFromSurface(uint32_t x, uint32_t y, const SDL_Surface* const surface);
		Color SDLColorToColor(uint32_t n) const;

};

#endif /* GRAPHICS_GRAPHICS_H_ */
