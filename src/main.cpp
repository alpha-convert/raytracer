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
	Vertex top = Vertex(Vec3(0,100,100),{0,1,2,3});
//	pyramid.push_back(
//	pyramid.push_back(Vec3(50,0,150)); //back right
//	pyramid.push_back(Vec3(50,0,50));	//front right
//	pyramid.push_back(Vec3(-50,0,50));	//front left
//	pyramid.push_back(Vec3(-50,0,150));	//back left

//	auto rotation = Quat::rotation(Vec2::J,M_PI/2);
//	auto rotated = a.rotate(rotation);
//	printf("%0.2f+%0.2fi+%0.2fj+%0.2fk\n",
//										rotation.w,
//										rotation.x,
//										rotation.y,
//										rotation.z);

//	printf("(%0.2f,%0.2f,%0.2f) -> (%.2f,%.2f,%.2f)\n",a.x,a.y,a.z,
//														rotated.x,
//														rotated.y,
//														rotated.z);

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

//		for(const auto&)

		//printf("%f\n",i);
	//	rotation = Quat::rotation(Vec2::I,DEG(i));
	//	rotated = a.rotate(rotation);
	//	g.ProjectVec3(rotated,Color::Red,100);
		g.Update();
	
	}

}



