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
	std::vector<int> vert_adj;
	std::vector<int> normal_adj;
	
	
}

class ObjFile{
	public:
		ObjFile(const std::string& fname);
		~ObjFile();

		std::vector<Vec4> verts;
		std::vector<Vec3> normals;
		//TODO: SHOULD BE POINTERS
		std::vector<std::vector<Vec4>> faces; //list of faces 


	protected:
		std::string raw;
		std::vector<std::vector<int> > face_refs; //list of adj lists
		Vec4 ParseVertex(const std::string& vstring);
		std::vector<int> ParseFaceRef(const std::string& vstring);
		void ConstructFaces();
};
#endif
