#include <cmath>
#include <cstdio>
#include <vector>
#include "Vec2/Vec2.h"
#include "Vec3/Vec3.h"
#include "Quat/Quat.h"
#include "Testing/Graphics/Graphics.h"
#include <SDL2/SDL.h>

#define DEG(x) (x*M_PI/180)

class Vertex{
public:
	std::vector<unsigned> adj;
	Vec3 pos;
	Vertex(Vec3 pos, std::vector<unsigned> adj) : adj(adj), pos(pos){}
};

int main(void){

	std::vector<Vertex> pyramid;	
	Vertex top = Vertex(Vec3(0,100,100),		{0,1,2,3});
	Vertex back = Vertex(Vec3(0,0,150),			{0,2,3});
	Vertex front_left = Vertex(Vec3(-50,0,50),	{0,1,3});
	Vertex front_right = Vertex(Vec3(50,0,50),	{0,1,2});

	pyramid.push_back(top);
	pyramid.push_back(back);
	pyramid.push_back(front_left);
	pyramid.push_back(front_right);


	Graphics g = Graphics(1920/2,1080/2,"Window");

	float i = 0;

	SDL_Event e;
	bool running = true;
	while(running){
		i += 0.1;
		while(SDL_PollEvent(&e)){
			if(e.type == SDL_QUIT || e.window.event == SDL_WINDOWEVENT_CLOSE){
				running = false;
				break;
			}
		}

		g.Clear();

		auto rotation = Quat::rotation(Vec2::I,DEG(0));

		for(const auto& vertex: pyramid){
			for(const auto vert_ref : vertex.adj){
				g.LineFromVec(vertex.pos.rotate(rotation),pyramid[vert_ref].pos.rotate(rotation),Color::Red);
			}
		}

		g.Update();
	
	}

}



