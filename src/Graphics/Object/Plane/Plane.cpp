#include "Plane.h"

//https://www.cs.princeton.edu/courses/archive/fall00/cs426/lectures/raycast/sld017.htm
bool Plane::IntersectDist(const Ray &ray, float &dist) const{
    bool hit = false;
    Vec3 Pr = ray.orig;
    Vec3 P0 = pos;
    Vec3 n = normal;
    Vec3 ur = ray.dir;

    float denom = n.dot(ur);
    if(denom < 0){
        hit = true;
        float num = n.dot(Pr - P0);
        dist = -num/denom;
    }

    return hit;
}

Vec3 Plane::NormalAt(const Vec3 & p) const{
    USE(p); //just for compatibility
    return normal;
}

Color Plane::ColorAt(const Vec3 &d) const{
    if(tex){
        //auto dist_from_center = (p - pos).mag();
        auto tex_width = tex->GetWidth();
        auto tex_height = tex->GetHeight();

        //auto u = std::abs(((int)floor(d.x) + tex_width/2) % (int)tex_width);
        //auto v = std::abs(((int)floor(d.z) + tex_height/2) % (int)tex_height);
        //return tex->AtReal(u,v);

        auto to_point = d - pos;
        float u = to_point.dot(basis_u);
        float v = to_point.dot(basis_v);

        return tex->AtReal(fabs(fmod(u,tex_width)),fabs(fmod(v,tex_height)));
    } else {
        return surface_color;
    }
}

Plane::Plane(const json &j, std::shared_ptr<Texture::texturemap> _gtm){
    global_texture_map = _gtm;

    auto geom_info = j["geom_info"];
    auto texture_info = j["texture_info"];
    auto color_info = j["color_info"];

    pos.x = geom_info["pos"]["x"];
    pos.y = geom_info["pos"]["y"];
    pos.z = geom_info["pos"]["z"];
    normal.x = geom_info["normal"]["x"];
    normal.y = geom_info["normal"]["y"];
    normal.z = geom_info["normal"]["z"];
    normal.normalizeInPlace();
    surface_color.g = color_info["surface_color"]["g"];
    surface_color.b = color_info["surface_color"]["b"];
    ks = color_info["blinn"]["ks"];
    kd = color_info["blinn"]["kd"];
    ka = color_info["blinn"]["ka"];
    alpha = color_info["blinn"]["alpha"];
    surface_color.r = color_info["surface_color"]["r"];
    tex = nullptr;

    LoadTexture(texture_info,_gtm);

    ComputeBasis();
    assert(UNITLENGTH(normal));
}


//Thanks to
//https://www.reddit.com/r/math/comments/5qbth4/how_can_i_get_a_uv_coordinate_space_for_a_plane/dcy27va/
void Plane::ComputeBasis(){
    auto u = Vec3::I.cross(normal);
    auto v = u.cross(normal);
    basis_u = u.normalized();
    basis_v = v.normalized();
}
