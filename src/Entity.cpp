/*
 * Entity.cpp
 *
 *  Created on: Jul 13, 2022
 *      Author: hector
 */

#include "Entity.h"
#include <iostream>

Entity::Entity(int x, int y, Color * color)
: _x(x), _y(y), _color(color)
{}

Entity::~Entity() {
	if (_color)
		delete _color;
}

void Entity::setColor(int r,int g, int b) {
	_color->_c[0] = r;
	_color->_c[1] = g;
	_color->_c[2] = b;
}

void Entity::setColor(const Color & c) {
	if (_color)
		delete _color;
	_color = new Color(c);
}


