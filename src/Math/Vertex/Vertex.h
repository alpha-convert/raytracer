#ifndef VERTEX_H_
#define VERTEX_H_ 
#include <vector>
#include "Vec4/Vec4.h"
class Vertex{
public:
	std::vector<unsigned> adj;
	Vec4 pos;
	Vertex(Vec4 pos, std::vector<unsigned> adj) : adj(adj), pos(pos){}
};


#endif

