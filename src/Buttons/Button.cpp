/*
 * Button.cpp
 *
 *  Created on: Aug 16, 2022
 *      Author: hector
 */

#include "Button.h"
#include "../Renderer.h"
#include <SDL2/SDL_image.h>

Button::Button()
: _x(0), _y(0)
{
	_texture = nullptr;
	_isSelected = false;
}

Button::Button(std::string text, int x, int y)
:_x(x), _y(y)
{
	_text = text;
	_isSelected = false;
	_texture = nullptr;
}

Button::~Button() {
	if (_texture)
		SDL_DestroyTexture(_texture);
}

bool Button::intersect(int x, int y) const {
	SDL_Point p = {x, y};
	return SDL_PointInRect(&p, &_drect);
}

