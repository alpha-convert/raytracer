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
	SDL_UpdateWindowSurface(this->window);
	SDL_RenderPresent(this->renderer);

}

void Graphics::ProjectVec3(const Vec3 &v, const Color &c, int scalar) const{
	this->SpaceLine(0, 0, v.dot(Vec3::I) * scalar, v.dot(Vec3::J) * scalar, c);
}

void Graphics::LineFromVec(const Vec3 &v1, const Vec3 &v2, const Color &c) const {
	this->SpaceLine(v1.x, v1.y, v2.x, v2.y, c);
}

void Graphics::SpaceLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2,const Color &c) const {
	Line(this->width / 2 + x1, this->height / 2 - y1, this->width / 2 + x2,
			this->height / 2 - y2, c);
}

void Graphics::Line(int32_t x1, int y1, int x2, int y2, const Color &c) const {
	SetColor(c);
	SDL_RenderDrawLine(this->renderer, x1, y1, x2, y2);
}


void Graphics::Bezier(const Vec2 &begin, const Vec2 &end, const Vec2 &control, const Color &c) const{
	int x_min = std::min(begin.x,end.x);
	int y_min = std::min(begin.y,end.y);
	(void) (x_min + y_min);
	(void) control;
	(void) c;
}



void Graphics::PutPixel(int x, int y, const Color &c) const {
	if (!(x > this->width && x < 0 && y > this->height && y < 0)) {
		SetColor(c);
		SDL_RenderDrawPoint(this->renderer, x, y);
	}
}

Graphics::~Graphics() {

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(this->renderer);
	SDL_Quit();
}

void Graphics::SetColor(const Color &c) const {
	//assert(INRANGE(c.r,0,1));
	//assert(INRANGE(c.g,0,1));
	//assert(INRANGE(c.b,0,1));
	SDL_SetRenderDrawColor(this->renderer, 255 * c.r, 255 * c.g, 255*c.b, 255);

}

Color Graphics::SDLColorToColor(uint32_t n) const{
	Color c = Color(0,0,0);
	c.r = (n & 0xff000000) / 255.0f;
	c.g = (n & 0xff0000) / 255.0f;
	c.b = (n & 0xff00) / 255.0f;
	return c;
}

Vec3 GetBarycentric(const Vec3 &t0, const Vec3 &t1, const Vec3 &t2, const Vec3 &p){
	(void) t0;
	(void) t1;
	(void) t2;
	(void) p;
	Vec3 as_bary;
	return as_bary;
}

//https://github.com/ssloy/tinyrenderer/wiki/Lesson-2:-Triangle-rasterization-and-back-face-culling
void Graphics::Triangle(const std::array<Vec4,3>& tri, const Color& c, const Color &fill) const{
	std::array<Vec4,3> corrected = tri;
	(void) fill;
	Mat4 proj = Mat4::Projection();

	for(auto& v : corrected){
		auto scale = v.z;
		v = (proj * v) / scale;
	}

	auto t0 = corrected[0];
	auto t1 = corrected[1];
	auto t2 = corrected[2];

	//sort the three in order

	if (t0.y>t1.y) std::swap(t0, t1); 
	if (t0.y>t2.y) std::swap(t0, t2); 
	if (t1.y>t2.y) std::swap(t1, t2); 

	//draw lines
	LineFromVec(t0,t1,c);
	LineFromVec(t1,t2,c);
	LineFromVec(t2,t0,c);

	//get bounding box for rasterizing
}

void Graphics::Triangle(const std::array<Vec4,3>& tri, const Color& c) const{
	Triangle(tri,c,c);
}



void Graphics::Polygon(const std::vector<Vertex>& poly, const Color& c) const{
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


void Graphics::Polygon(const std::vector<Vertex>& poly, const Color& c, const Quat& rotation) const{
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


Color Graphics::Trace(const std::vector<Object *> &scene, const std::vector<Light> lights, const Ray &cast_ray, const Vec3 &camera_pos,unsigned recurse_times) const{
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
		Color ambient = closest_object->surface_color;
		final_color = ambient * closest_object->ka;
		//Iterate over lights
		Vec3 intersection_point = cast_ray.Along(closest_dist);
		Vec3 normal = closest_object->NormalAt(intersection_point);

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

			float light_check_dist;
			Object *closest_to_light = GetClosestObject(scene,light_check_ray,light_check_dist);
			USE(closest_to_light);

			auto light_check_point = light_check_ray.orig + light_check_ray.dir * light_check_dist;

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

				Color reflection_term = Trace(scene,lights,light_check_ray,camera_pos,recurse_times+1) * 0.1;

				final_color = (final_color + diffuse_term + specular_term);
			}
		}
	}
	return final_color;
}



//TODO: make this work
void Graphics::AvgBlur(float ksize) const{
	SDL_RendererInfo info;
	SDL_GetRendererInfo(renderer,&info);

	auto render_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, 
			    SDL_TEXTUREACCESS_STREAMING, width, height);

	uint32_t format;
	int *acc;
	int *w;
	int *h;
	USE(w);
	USE(h);
	USE(ksize);
	acc = w = h = nullptr;
	SDL_QueryTexture(render_texture,&format,acc,w,h);
	auto pitch = SDL_BITSPERPIXEL(format) * width / 8;

	void *raw_pixel_data = malloc(width * height * sizeof(uint8_t) * pitch);
	uint32_t *pixel_data = (uint32_t *) raw_pixel_data;
	SDL_RenderReadPixels(renderer,NULL, format,raw_pixel_data,pitch);
	USE(raw_pixel_data);
	USE(pixel_data);

	for(int y = 0; y < height; ++y){
		for(int x = 0; x < width; ++x){
			auto i = width * y + x;
			USE(i);
//			printf("%x\n",pixel_data[i]);

		}
	}
	
	free(raw_pixel_data);
}

ConventionalPoint::ConventionalPoint(int8_t x, int8_t y){
	assert(INEQ(-1,<=,x,<=,1));
	assert(INEQ(-1,<=,y,<=,1));
	this->x = x;
	this->y = y;
}
