#include "ObjFile.h"
#include "Vec4/Vec4.h"
#include "Vec3/Vec3.h"

#include <sstream>
#include <fstream>
#include <iostream>
#include <locale>
#include <typeinfo>
#include <cctype>


#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

inline bool IsNum(const std::string &str){	return std::all_of(str.begin(), str.end(), ::isdigit);} // C++11

inline bool IsSpaces(const std::string& s){	return s.find_first_not_of("\t\n ") == s.npos;}

inline std::vector<std::string> split(const std::string& str, std::string delim){
	std::vector<std::string> slist;
	boost::split(slist,str,boost::is_any_of(delim));
	return slist;
}


ObjFile::ObjFile(const std::string& fname){
	std::ifstream t(fname.c_str());
	std::stringstream buffer;
	buffer << t.rdbuf();
	raw = buffer.str();

	auto lines = split(raw,"\n");

	//parse each line into its type
	for(const auto& line : lines){
		if(boost::starts_with(line,"v")){
			verts.push_back(ParseVertex(line));

		} else if(boost::starts_with(line,"vn")){
			normals.push_back(ParseNormal(line)); //same format as vertexes.

		} else if(boost::starts_with(line,"vt")){
			textures.push_back(ParseTexture(line));
			
		} else if(boost::starts_with(line,"f")){
			faces.push_back(ParseFace(line));
		}
	}

//	for(const auto& vert : verts){
//		printf("%.2f,%.2f,%.2f,%.2f\n",vert.x,vert.y,vert.z,vert.w);
//	}

}

ObjFile::~ObjFile(){}

Face ObjFile::ParseFace(const std::string& vstring) const{
	printf("Parsing face: \"%s\"\n",vstring.c_str());
	Face f;
	auto components = split(vstring,"\t\n ");

	//remove all non/essential data
	components.erase(std::remove_if(components.begin(),components.end(), [](std::string x){
				return !IsNum(x) | IsSpaces(x);
		}), components.end()
	);

	//TODO: Make this work for more than just verts
	for(const auto& v : components){
		f.vert_adj.push_back(boost::lexical_cast<float>(v));
	}
	
	return f;
}

Vec3 ObjFile::ParseNormal(const std::string& vstring) const{
	printf("Parsing normal: \"%s\"\n",vstring.c_str());
	Vec3 normal;
	auto components = split(vstring," ");

	normal.x = boost::lexical_cast<float,std::string>(components.at(1));
	normal.y = boost::lexical_cast<float,std::string>(components.at(2));
	normal.z = boost::lexical_cast<float,std::string>(components.at(3));

	return normal.normalized();
}

Vec3 ObjFile::ParseTexture(const std::string& vstring) const{
	printf("Parsing texture: \"%s\"\n",vstring.c_str());
	Vec3 texture;
	int num_components = std::count_if(vstring.begin(), vstring.end(),[](unsigned char c){
			return std::isspace(c);});

	auto components = split(vstring," ");
	
	if(num_components < 3){
		texture.z = 0;
	} else {
		texture.z = boost::lexical_cast<float,std::string>(components.at(3));
	}
	return texture;
}

Vec4 ObjFile::ParseVertex(const std::string& vstring) const{
	printf("Parsing vertex: \"%s\"\n",vstring.c_str());
	Vec4 vertex;
	//get the number of components that are given
	int num_components = std::count_if(vstring.begin(), vstring.end(),[](unsigned char c){
			return std::isspace(c);});

	auto components = split(vstring," ");

	//w is optional in file, add it in if it's not there.
	if(num_components < 4){
		vertex.w = 1;
	} else {
		vertex.w = boost::lexical_cast<float,std::string>(components.at(4));
	}

	//set the rest of the components
	vertex.x = boost::lexical_cast<float,std::string>(components.at(1));
	vertex.y = boost::lexical_cast<float,std::string>(components.at(2));
	vertex.z = boost::lexical_cast<float,std::string>(components.at(3));

	return vertex;
}

