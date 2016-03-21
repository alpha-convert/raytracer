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
#include "Math/Tree/Tree.h"

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

//	AVLTree<unsigned int> tree = AVLTree<unsigned int>(7);
	AVLTree<int> tree = AVLTree<int>(8);
	tree.Insert(3);
	tree.Insert(10);
	tree.Insert(1);
	tree.Insert(6);
	tree.Insert(4);
	tree.Insert(7);
	tree.Insert(14);
	tree.Insert(13);

//	tree.root->MakeLeft(2);
//	tree.root->MakeRight(30);

	tree.Print();

//	tree.Apply([](unsigned int i){
//			printf("%d\n",i);
//			return i;
//	});

	auto tbl = Vertex(Vec4(-1,1,1),		{1,3,4});
	auto tbr = Vertex(Vec4(1,1,1),		{0,2,5});
	auto tfr = Vertex(Vec4(1,1,-1),		{1,3,6});
	auto tfl = Vertex(Vec4(-1,1,-1),		{0,2,7});


	auto bbl = Vertex(Vec4(-1,-1,1),	{0,7,5});
	auto bbr = Vertex(Vec4(1,-1,1),		{1,4,6});
	auto bfr = Vertex(Vec4(1,-1,-1),		{2,5,7});
	auto bfl = Vertex(Vec4(-1,-1,-1),	{3,4,6});

	std::vector<Vertex> cube;
	cube.push_back(tbl);
	cube.push_back(tbr);
	cube.push_back(tfr);
	cube.push_back(tfl);

	cube.push_back(bbl);
	cube.push_back(bbr);
	cube.push_back(bfr);
	cube.push_back(bfl);

	//ObjFile diamond("diamond.obj");

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

	float i = 0.05;
	Quat q;

	SDL_Event e;

	auto initial_rot = Quat::rotation((Vec3::J + Vec3::K).normalized(),DEG(90));
	auto initial_trans = Mat4::Translation(0,0,100);
	auto initial_scale = Mat4::Scale(100);
	for(auto& v : cube){
		v.pos = initial_trans * initial_scale * v.pos.rotate(initial_rot);
	}

	//TODO:TRUE TO RUN
	bool running =  false;

	while(running){
		//TODO: DEBUGGING
//		running = false;
		if(SDL_PollEvent(&e)){
			if(e.type == SDL_QUIT || e.window.event == SDL_WINDOWEVENT_CLOSE){
				running = false;
			}
		}

		i += 0.5;
		const auto proj = Mat4::Projection();

		g.Clear();


//		g.Polygon(cube,Color::Green,[&](Vec4 v){
//			auto scale = v.z;
//			v = (proj * v) / scale;
//			return v;
//		});

	//	g.Polygon(cube,Color::Green,Quat::rotation(Vec3::I,DEG(i)));

//		auto rotation_axis = (Vec3::J).normalized();
//		q = Quat::rotation(rotation_axis,DEG(i));
//		for(auto& v : cube){
//			v.pos = v.pos.rotate(q);
//		}
//		g.Polygon(cube,Color::Green);

		g.Update();

	}

	SDL_Quit();
}


