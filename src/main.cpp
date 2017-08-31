#include <fstream>
#include <streambuf>
#include <cmath>
#include <array>
#include <cstdio>
#include <vector>
#include <limits>
#include <cassert>
#include <memory>
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Quat.h"
#include "Mat4.h"
#include "Ray.h"
#include "Tree.h"
#include "Graphics.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Plane.h"
#include "Object.h"
#include "Light.h"
#include "Texture.h"
#include "OpenGL/OpenGL.h"
#include "Audio.h"
#include "settings.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GLUT/glut.h>

#include "json.hpp"

#define SUBPIXEL 1
using json = nlohmann::json;
using string = std::string;

void read_entire_json_file(const std::string &fname, json &contents){
  std::ifstream ifs (fname,std::ifstream::in);
  ifs >> contents;
}

int main(int argc, char** argv){
  USE(argc);
  USE(argv);

  //Audio a;
  Graphics g = Graphics(1920/2,1080/2,"Raytracer");
  g.Clear();

  //Texture lenna = Texture("textures/lenna.png");

  //this doesn't really work but it's a start
  constexpr float scene_angle = -M_PI/2; //angle from origin to camera
  constexpr float camera_dist = 1500;
  constexpr float screen_dist = 300;

  //Note: camera is currently always pointing to the origin
  Vec3 camera_pos = Vec3(camera_dist * cos(scene_angle),0,camera_dist * sin(scene_angle));
  Vec3 camera_dir = Vec3::K;
  USE(camera_dir);
  Vec3 screen_pos = Vec3(screen_dist * cos(scene_angle),0,screen_dist * sin(scene_angle));
  Vec3 screen_normal = (camera_pos - screen_pos).normalized();
  Vec3 screen_top_left = screen_pos + Vec3(-static_cast<float>(g.width)/2,static_cast<float>(g.height)/2,0);
  USE(screen_normal);

  //Global lists and maps
  std::vector<Object *> scene;
  std::vector<Light> lights;
  auto gtm = std::make_shared<Texture::texturemap>();

  json json_scene;
  read_entire_json_file("planescene.json",json_scene);


  for(const auto &o : json_scene["objects"]){
    auto type = o["geom_info"]["type"];
    if(type == "type_sphere"){
      scene.push_back(new Sphere(o,gtm));
    } else if(type == "type_plane"){
      scene.push_back(new Plane(o,gtm));
    } else if(type == "type_triangle"){
      scene.push_back(new Triangle(o,gtm));
    }
  }

  for(const auto &ljson : json_scene["lights"]){
    Light nl = Light(ljson);
    lights.push_back(nl);
    //Each light has a corresponding sphere in world space
    //Todo: Figure out why I put this here
    //Sphere s = Sphere();
    //s = nl.test_sphere;
    //scene.push_back(&s);
  }

  //For each pixel
  for(int y = 0; y < g.height; ++y){
    for(int x = 0; x < g.width; ++x){
#if SUBPIXEL
      Ray px_ray0 = Ray::ThroughPixel(x-0.5,y,camera_pos,screen_top_left);
      Ray px_ray1 = Ray::ThroughPixel(x,y-0.5,camera_pos,screen_top_left);
      Ray px_ray2 = Ray::ThroughPixel(x-0.5,y-0.5,camera_pos,screen_top_left);
      Ray px_ray3 = Ray::ThroughPixel(x,y,camera_pos,screen_top_left);
      Color c0 = g.Trace(scene,lights,px_ray0,camera_pos,0);
      Color c1 = g.Trace(scene,lights,px_ray1,camera_pos,0);
      Color c2 = g.Trace(scene,lights,px_ray2,camera_pos,0);
      Color c3 = g.Trace(scene,lights,px_ray3,camera_pos,0);
      Color final_color = c0.UnclampedAdd(c1).UnclampedAdd(c2).UnclampedAdd(c3) * (0.25);
#else
      Ray px_ray = Ray::ThroughPixel(x,y,camera_pos,screen_top_left);
      Color final_color = g.Trace(scene,lights,px_ray,camera_pos,0);
#endif
      g.PutPixel(x,y,final_color);
    }
  }

  g.Update();

  SDL_Event e;
  bool running =  true;
  while(running){
    if(SDL_PollEvent(&e)){
      if(e.type == SDL_QUIT || e.window.event == SDL_WINDOWEVENT_CLOSE){
        running = false;
      }
    }

  }

  for(auto &a:scene) delete a;
  SDL_Quit();

  assert(gtm->empty());
}
