/*
 * Color.h
 *
 *  Created on: Oct 28, 2015
 *      Author: Admin
 */

#ifndef COLOR_COLOR_H_
#define COLOR_COLOR_H_
#include <stdint.h>

class Color {
public:
	uint8_t r;
	uint8_t g;
	uint8_t b;
	Color(uint8_t r, uint8_t g, uint8_t b);
	virtual ~Color(){};

	static const Color Red;
	static const Color Green;
	static const Color Blue;
	static const Color Black;
	static const Color White;

};


#endif /* COLOR_COLOR_H_ */
