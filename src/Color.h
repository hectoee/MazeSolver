/*
 * Color.h
 *
 *  Created on: Jul 13, 2022
 *      Author: hector
 */

#ifndef COLOR_H_
#define COLOR_H_

#include <tuple>

class Color {
private:
	unsigned int _c[3];
	friend class Entity;

public:
	Color(int r = 0, int g = 0, int b = 0);
	virtual ~Color();

	static Color LightGrey;
	static Color DarkGrey;
	static Color Yellow;
	static Color Red;
	static Color Green;

	const Color & getColor() const ;

	bool operator==(const Color & other) {
		return _c[0] == other._c[0] && _c[1] == other._c[1] && _c[2] == other._c[2];
	}

	unsigned int & operator[](unsigned int index) {
		return _c[index];
	}




};

#endif /* COLOR_H_ */
