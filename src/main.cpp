#include <cmath>
#include <array>
#include <cstdio>
#include <vector>
#include "Math/Vec2/Vec2.h"
#include "Math/Vec3/Vec3.h"
#include "Math/Vec4/Vec4.h"
#include "Math/Quat/Quat.h"
#include "Math/Mat4/Mat4.h"
#include "ObjFile/ObjFile.h"

#include "Graphics/Graphics.h"
#include "OpenGL/OpenGL.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GLUT/glut.h>
//https://github.com/ssloy/tinyrenderer/wiki/Lesson-1:-Bresenham%E2%80%99s-Line-Drawing-Algorithm

#define DEG(x) (x*M_PI/180)


int main(int argc, char** argv){
	(void) argc;
	(void) argv;
	
	auto tbl = Vertex(Vec4(-100,100,100),		{1,3,4});
	auto tbr = Vertex(Vec4(100,100,100),		{0,2,5});
	auto tfr = Vertex(Vec4(100,100,-100),		{1,3,6});
	auto tfl = Vertex(Vec4(-100,100,-100),		{0,2,7});


	auto bbl = Vertex(Vec4(-100,-100,100),	{0,7,5});
	auto bbr = Vertex(Vec4(100,-100,100),		{1,4,6});
	auto bfr = Vertex(Vec4(100,-100,-100),		{2,5,7});
	auto bfl = Vertex(Vec4(-100,-100,-100),	{3,4,6});

	std::vector<Vertex> cube;
	cube.push_back(tbl);
	cube.push_back(tbr);
	cube.push_back(tfr);
	cube.push_back(tfl);

	cube.push_back(bbl);
	cube.push_back(bbr);
	cube.push_back(bfr);
	cube.push_back(bfl);

	ObjFile diamond("diamond.obj");

	auto t0 = Vec4(-100,-50,1);
	auto t1 = Vec4(100,-50,5);
	auto t2 = Vec4(0,100,1);

	auto a0 = Vec4(-100,-50,2);
	auto a1 = Vec4(100,-50,2);
	auto a2 = Vec4(0,100,2);

	std::array<Vec4,3> triangle = {{t0,t1,t2}};
	std::array<Vec4,3> triangle2 = {{a0,a1,a2}};

	(void) triangle;
	(void) triangle2;

	Graphics g = Graphics(1920/2,1080/2,"Window");

	float i = 0;
	Quat q;

	SDL_Event e;
//	bool running = true;
//	TODO: MAKE THIS TRUE TO RUN
	bool running =  true;
	while(running){
		if(SDL_PollEvent(&e)){
			if(e.type == SDL_QUIT || e.window.event == SDL_WINDOWEVENT_CLOSE){
				running = false;
				break;
			}
		}
		i += 0.05;

		Quat q = Quat::rotation(Vec3(sqrt(2)/2,0,-sqrt(2)/2),DEG(i));

		g.Clear();

		for(const auto& vert : diamond.faces){
//			Vertex v;
//			g.Pol
		}
		//g.Polygon(cube,Color::Red,q);
		//		g.Triangle(triangle,Color::Red);
		//		g.Triangle(triangle2,Color::Red);
		g.Update();

	}

	SDL_Quit();
}



