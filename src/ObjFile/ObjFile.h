#ifndef OBJFILE_H_
#define OBJFILE_H_ 

#include <string>
#include <vector>

#ifndef VEC4_H_
class Vec4;
#endif

#ifndef VEC3_H_
class Vec3;
#endif

class Face{
	public:
	std::vector<unsigned> vert_adj; 	//NOTE: 1 INDEXED
	std::vector<unsigned> normal_adj;	//NOTE: 1 INDEXED
	std::vector<unsigned> texture_adj;	//NOTE: 1 INDEXED
	
};

class ObjFile{
	public:
		ObjFile(const std::string& fname);
		~ObjFile();

		std::vector<Vec4> verts;
		std::vector<Vec3> normals;
		std::vector<Vec3> textures;

		//list of faces, which are just adj lists.
		std::vector<Face> faces;


	protected:
		std::string raw;
		Vec4 ParseVertex(const std::string& vstring) const;
		Vec3 ParseNormal(const std::string& vstring) const;
		Vec3 ParseTexture(const std::string& vstring) const;
		Face ParseFace(const std::string& vstring) const;


};
#endif
