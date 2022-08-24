/*
 * Color.cpp
 *
 *  Created on: Jul 13, 2022
 *      Author: hector
 */

#include "Color.h"
#include <iostream>

Color Color::LightGrey = Color(200, 200, 200);
Color Color::DarkGrey  = Color(100, 100, 100);
Color Color::Yellow    = Color(255, 255, 0);
Color Color::Red       = Color(255, 0, 0);
Color Color::Green     = Color(0, 255, 0);

Color::Color(int r, int g, int b)
{
	_c[0] = r;
	_c[1] = g;
	_c[2] = b;
}

Color::~Color() {
	// TODO Auto-generated destructor stub
}
