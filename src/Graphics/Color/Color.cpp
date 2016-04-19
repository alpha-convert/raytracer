/*
 * Color.cpp
 *
 *  Created on: Oct 28, 2015
 *      Author: Admin
 */

#include "Color.h"
Color::Color(){
	this->r = 0;
	this->g = 0;
	this->b = 0;
}
Color::Color(float r, float g, float b) {
	this->r = r;
	this->g = g;
	this->b = b;
}

const Color Color::Red 		= Color(1.0f,0,0);
const Color Color::Green	= Color(0,1.0f,0);
const Color Color::Blue		= Color(0,0,1.0f);
const Color Color::Black	= Color(0,0,0);
const Color Color::White	= Color(1.0f,1.0f,1.0f);

bool Color::operator==(const Color& c) const{
	return (r == c.r) && (g == c.g) && (b == c.b); 
}

Color Color::operator*(float f) const{
	return Color(f*r,f*g,f*b).clamped();
}
Color Color::operator/(float f) const{
	return Color(r/f,g/f,b/f).clamped();
}

Color Color::operator+(const Color &c) const{
	return Color(r+c.r,g+c.g,b+c.b).clamped();
}

Color Color::clamped(){
	auto c = *this;
	c.clamp();
	return c;
}

void Color::clamp(){
	r = CLAMP(r,0.0,1.0);
	g = CLAMP(g,0.0,1.0);
	b = CLAMP(b,0.0,1.0);
}
