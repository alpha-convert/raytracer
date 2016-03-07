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
	for(auto& line : lines){
		if(boost::starts_with(line,"v")){
			verts.push_back(ParseVertex(line));

		} else if(boost::starts_with(line,"vn")){
			normals.push_back((Vec3) ParseVertex(line)); //same format as vertexes.

		} else if(boost::starts_with(line,"f")){
			face_refs.push_back(ParseFaceRef(line));
		}
	}
	ConstructFaces();
}


ObjFile::~ObjFile(){

}

void ObjFile::ConstructFaces(){
	//for each adjacency list
	for(auto i = 0; i < face_refs.size(); ++i){
		//derefrence the list
		const auto vert_ref_arr = face_refs.at(i);
		printf("Constructing face with adj ");
		std::vector<Vec4> face;
		for(const auto& vert_index : vert_ref_arr){
			//for each index in the adj list, add a pointer.
			printf(" %d",vert_index);
			face.push_back((verts.at(vert_index - 1))); //one indexed
		}
		printf("\n");
		faces.push_back(face);
	}
}


std::vector<int> ObjFile::ParseFaceRef(const std::string& vstring){
	printf("Parsing face line: \"%s\"\n",vstring.c_str());
	std::vector<int> face_ref;
	//
	//given an adjacency list string, split it into vector of strings
	
	auto vert_indexes = split(vstring,"\t\n ");
	vert_indexes.erase( 
		std::remove_if(vert_indexes.begin(), vert_indexes.end(), [](std::string s){
			return !IsNum(s) || IsSpaces(s);
		}),
		vert_indexes.end()
	);
	//this looks scarily like javascript. removes all non integer tokens

	//create adj list of ints, add to the face refs
	for(const std::string& v_index : vert_indexes){
		face_ref.push_back(boost::lexical_cast<unsigned,std::string>(v_index));
	}
	return face_ref;
}


Vec4 ObjFile::ParseVertex(const std::string& vstring){
	printf("Parsing vertex or normal: \"%s\"\n",vstring.c_str());
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

