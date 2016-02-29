/*
 * Color.cpp
 *
 *  Created on: Oct 28, 2015
 *      Author: Admin
 */

#include "Color.h"
#include "stdint.h"

Color::Color(uint8_t r, uint8_t g, uint8_t b) {
	this->r = r;
	this->g = g;
	this->b = b;

}

const Color Color::Red 		= Color(255,0,0);
const Color Color::Green	= Color(0,255,0);
const Color Color::Blue		= Color(0,0,255);
const Color Color::Black	= Color(0,0,0);
const Color Color::White	= Color(255,255,255);

bool Color::operator==(const Color& c) const{
	return (r == c.r) && (g == c.g) && (b == c.b); 
}
