/*
 * Graphics.cpp
 *
 *  Created on: Oct 28, 2015
 *      Author: Admin
 */
#include "Graphics.h"
#include <SDL2/SDL.h>
#include <execinfo.h>

#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#include <array>
#include <functional>
#include <algorithm>

//General graphics flow:

Graphics::Graphics(uint32_t width, uint32_t height, const char *name) {
	if (!SDL_WasInit(SDL_INIT_VIDEO)) {
		SDL_Init(SDL_INIT_VIDEO);
	}
	this->width = width;
	this->height = height;

	this->window = SDL_CreateWindow(name,
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,
			SDL_WINDOW_SHOWN);
	if (!this->window) {
		fprintf(stderr, "Error creating window, %s\n", SDL_GetError());
	}
	assert(window != nullptr);

	this->renderer = SDL_CreateRenderer(this->window, -1,
			SDL_RENDERER_ACCELERATED);
	if (!this->renderer) {
		fprintf(stderr,"Error creating renderer: %s", SDL_GetError());
	}
	assert(renderer!= nullptr);


	SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND);


}

void Graphics::Clear() {
	SetColor(Color::White);
	SDL_RenderClear(this->renderer);
}

void Graphics::Update() {
	for(const auto &p : points_to_draw){
		SetColor(p.c);
		SDL_RenderDrawPoint(renderer,p.p.x,p.p.y);
	}
	for(const auto &r : rects_to_draw){
		SetColor(r.c);
		SDL_RenderDrawRect(renderer,&r.r);
	}
	for(const auto &r : filled_rects_to_draw){
		SetColor(r.c);
		SDL_RenderFillRect(renderer,&r.r);
	}
	for(const auto &l : lines_to_draw){
		SetColor(l.c);
		SDL_RenderDrawLine(renderer,l.x1,l.y1,l.x2,l.y2);
	}
	SDL_UpdateWindowSurface(this->window);
	SDL_RenderPresent(this->renderer);
}

void Graphics::ProjectVec3(const Vec3 &v, const Color &c, int scalar){
	this->SpaceLine(0, 0, v.dot(Vec3::I) * scalar, v.dot(Vec3::J) * scalar, c);
}

void Graphics::LineFromVec(const Vec3 &v1, const Vec3 &v2, const Color &c){
	this->SpaceLine(v1.x, v1.y, v2.x, v2.y, c);
}

void Graphics::SpaceLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2,const Color &c){
	Line(this->width / 2 + x1, this->height / 2 - y1, this->width / 2 + x2,
			this->height / 2 - y2, c);
}

void Graphics::Line(int32_t x1, int y1, int x2, int y2, const Color &c){
	DeferredRenderLine r;
	r.c = c;
	r.x1 = x1;
	r.y1 = y1;
	r.x2 = x2;
	r.y2 = y2;
	lines_to_draw.push_back(r);
}

void Graphics::PutPixel(int x, int y, const Color &c) {
	if (!(x > this->width && x < 0 && y > this->height && y < 0)) {
		DeferredRenderPoint p;
		p.c = c;
		p.p.x = x;
		p.p.y = y;
		points_to_draw.push_back(p);
	}
}

Graphics::~Graphics() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(this->renderer);
	SDL_Quit();
}

void Graphics::SetColor(const Color &c) {
	SDL_SetRenderDrawColor(this->renderer, 255 * c.r, 255 * c.g, 255*c.b, 255*c.a);

}

Color Graphics::SDLColorToColor(uint32_t n) const {
	Color c = Color(0,0,0);
	c.r = (n & 0xff000000) / 255.0f;
	c.g = (n & 0xff0000) / 255.0f;
	c.b = (n & 0xff00) / 255.0f;
	return c;
}

//https://github.com/ssloy/tinyrenderer/wiki/Lesson-2:-Triangle-rasterization-and-back-face-culling
void Graphics::Triangle(const std::array<Vec3,3>& tri, const Color& c, const Color &fill) {
/*
	std::array<Vec4,3> corrected = tri;
	(void) fill;
	Mat4 proj = Mat4::Projection();

	for(auto& v : corrected){
		auto scale = v.z;
		v = (proj * v) / scale;
	}

*/
	auto t0 = tri[0];
	auto t1 = tri[1];
	auto t2 = tri[2];

	//sort the three in order

	if (t0.y>t1.y) std::swap(t0, t1); 
	if (t0.y>t2.y) std::swap(t0, t2); 
	if (t1.y>t2.y) std::swap(t1, t2); 

	//draw lines
	LineFromVec(t0,t1,c);
	LineFromVec(t1,t2,c);
	LineFromVec(t2,t0,c);

	//get bounding box for rasterizing
	//nope jk this isn't done
	//@TODO: Do fills or whatever
}

void Graphics::Triangle(const std::array<Vec3,3>& tri, const Color& c) {
	Triangle(tri,c,c);
}



void Graphics::Polygon(const std::vector<Vertex>& poly, const Color& c) {
	std::vector<Vertex> corrected = poly;
	Mat4 proj = Mat4::Projection();

	for(auto& v : corrected){
		auto scale = v.pos.z;
		v.pos = (proj * v.pos) / scale;
	}

	for(const auto& vertex : poly){
		for(const auto vert_ref : vertex.adj){
			this->LineFromVec(vertex.pos,poly[vert_ref].pos,c);
		}
	}
}


void Graphics::Polygon(const std::vector<Vertex>& poly, const Color& c, const Quat& rotation) {
	std::vector<Vertex> corrected = poly;
	Mat4 proj = Mat4::Projection();

	for(auto& v : corrected){
		auto scale = v.pos.z;
		v.pos = (proj * v.pos) / scale;
	}

	for(const auto& vertex : poly){
		for(const auto vert_ref : vertex.adj){
			this->LineFromVec(vertex.pos.rotate(rotation),poly[vert_ref].pos.rotate(rotation),c);
		}
	}
}

void Graphics::Polygon(const std::vector<Vertex>& poly, const Color& c, const std::function<Vec4(Vec4)> transform){
	auto post_transform = poly;
	for(auto& vert : post_transform){
		vert.pos = transform(vert.pos);
	}

	for(const auto& vertex : post_transform){
		for(const auto vert_ref : vertex.adj){
			this->LineFromVec(vertex.pos,post_transform[vert_ref].pos,c);
		}
	}
}

Object *Graphics::GetClosestObject(const std::vector<Object *> &objects, const Ray &cast_ray, float &dist) const{
	Object *closest_object = NULL;
	dist = std::numeric_limits<float>::infinity();
	for(const auto &object : objects){
		float obj_dist;
		auto hit_this = object->IntersectDist(cast_ray,obj_dist);
		if(obj_dist < dist && hit_this){
			dist = obj_dist;
			closest_object = object;
		}
	}
	return closest_object;

}

Object *Graphics::GetClosestObject(const std::vector<Object *> &objects, const Ray &cast_ray) const{
	float dist = std::numeric_limits<float>::infinity();
	Object *closest_object = NULL;
	for(const auto &object : objects){
		float obj_dist;
		auto hit_this = object->IntersectDist(cast_ray,obj_dist);
		if(obj_dist < dist && hit_this){
			dist = obj_dist;
			closest_object = object;
		}
	}
	return closest_object;

}


Color Graphics::Trace(const std::vector<Object *> &scene, const std::vector<Light> &lights, const Ray &cast_ray, const Vec3 &camera_pos,unsigned recurse_times) const{
	//general init stuff
	float closest_dist = std::numeric_limits<float>::infinity();
	auto hit = false;
	Color final_color = Color::White;

	//base case
	if(recurse_times >= 3){
		return final_color;
	}

	//Find the closest object
	Object *closest_object = GetClosestObject(scene,cast_ray,closest_dist);
	hit = closest_object ? true : false;

	assert(IMPLIES(hit,closest_object));
	assert(IMPLIES(closest_dist == std::numeric_limits<float>::infinity(),!hit));


	if(hit){
		Vec3 intersection_point = cast_ray.Along(closest_dist);
		Vec3 normal = closest_object->NormalAt(intersection_point);

		Color ambient = closest_object->ColorAt(intersection_point);
		final_color = ambient * closest_object->ka;
		//Iterate over lights

		//create the bounce ray
		Ray bounce_ray;
		bounce_ray.orig = intersection_point;
		bounce_ray.dir = cast_ray.dir - normal * 2*(cast_ray.dir.dot(normal));

		//go over each light
		for(const auto &l : lights){
			float light_intersect_dist = (intersection_point - l.pos).mag();
			USE(light_intersect_dist);

			//make a ray from from the light to the sphere
			Ray light_check_ray;
			light_check_ray.orig = l.test_sphere.pos;
			light_check_ray.dir = (l.test_sphere.pos - intersection_point).normalized();

			//get the distance from the closest object to the light
			float light_check_dist;
			Object *closest_to_light = GetClosestObject(scene,light_check_ray,light_check_dist);
			USE(closest_to_light);

			//get the point where it hits
			auto light_check_point = light_check_ray.orig + light_check_ray.dir * light_check_dist;
			//and check if we're talking about the same point here
			if(light_check_point == intersection_point){
				Vec3 Lm = (light_check_point-l.pos).normalized();
				Vec3 N = normal.normalized();
				Vec3 Rm = N*2*(Lm.dot(N)) - Lm;
				Vec3 V = (camera_pos - intersection_point).normalized();
				float alpha = closest_to_light->alpha;

				float ks = closest_to_light->ks;
				Color is = l.is;
				Color specular_term = is * ks * std::pow(std::max<float>(Rm.dot(V),0),alpha);
				assert(0<=specular_term.r<=1);
				assert(0<=specular_term.g<=1);
				assert(0<=specular_term.b<=1);

				float kd = closest_to_light->kd;
				Color id = l.id;
				Color diffuse_term = id * kd * std::max<float>(Lm.dot(N),0);
				assert(0<=diffuse_term.r<=1);
				assert(0<=diffuse_term.g<=1);
				assert(0<=diffuse_term.b<=1);

				Color reflection_term = Trace(scene,lights,light_check_ray,camera_pos,recurse_times+1) * closest_to_light->ks;

				final_color = (final_color + diffuse_term + specular_term);
			}
		}
	}
	return final_color;
}

