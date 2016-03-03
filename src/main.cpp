#include <cmath>
#include <cstdio>
#include <vector>
#include "Math/Vec2/Vec2.h"
#include "Math/Vec3/Vec3.h"
#include "Math/Quat/Quat.h"
#include "Graphics/Graphics.h"
#include "OpenGL/OpenGL.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GLUT/glut.h>

//https://github.com/ssloy/tinyrenderer/wiki/Lesson-1:-Bresenham%E2%80%99s-Line-Drawing-Algorithm

#define DEG(x) (x*M_PI/180)


int main(int argc, char** argv){

	auto t0 = Vec3(-100,-50,20);
	auto t1 = Vec3(100,-50,20);
	auto t2 = Vec3(0,100,20);

	auto a0 = Vec3(200,-50,100);
	auto a1 = Vec3(400,-50,100);
	auto a2 = Vec3(300,100,100);

	Vec3 triangle[3] = {t0,t1,t2};
	Vec3 tri2[3] = {a0,a1,a2};

	Graphics g = Graphics(1920/2,1080/2,"Window");


	SDL_Event e;
	bool running = true;
	while(running){
		while(SDL_PollEvent(&e)){
			if(e.type == SDL_QUIT || e.window.event == SDL_WINDOWEVENT_CLOSE){
				running = false;
				break;
			}
			g.Clear();
//			g.Polygon(pyramid,Color::Red);
			g.Triangle(triangle,Color::Red);
			g.Triangle(tri2,Color::Red);
			g.Update();
		}
	
	}

	SDL_Quit();
}



