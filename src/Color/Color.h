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

	bool operator==(const Color& c) const;

	void AsHSV(uint32_t &h, uint32_t &s, uint32_t &l) const;
	void SetHSV(const uint32_t &h, const uint32_t &s, const uint32_t &l);
};


#endif /* COLOR_COLOR_H_ */
