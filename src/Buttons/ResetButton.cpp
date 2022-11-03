/*
 * ResetButton.cpp
 *
 *  Created on: Aug 18, 2022
 *      Author: hector
 */

#include "ResetButton.h"
#include "../Renderer.h"
#include <SDL2/SDL_image.h>

ResetButton::ResetButton(const char* txt, int x, int y)
: Button(txt, x, y)
{
	_srect.h = 100;
	_srect.w = 80;
	_srect.x = 0;
	_srect.y = 50;

	_drect.h = 40;
	_drect.w = 40;
	_drect.x = x;
	_drect.y = y+5;
}

ResetButton::~ResetButton() {
	// TODO Auto-generated destructor stub
}


void ResetButton::render() {
	static SDL_Texture * t = IMG_LoadTexture(Renderer::getInstance().getSDLRenderer(), "../assets/reset_button.png");
	_texture = t;
	Renderer::getInstance().drawString(_text, _x + 50, _y+5);
	if(SDL_RenderCopy(Renderer::getInstance().getSDLRenderer(), _texture, &_srect, &_drect) < 0)
		std::cout << SDL_GetError() << std::endl;
	if (_texture == nullptr) std::cout << "text : nullptr" << std::endl;
}

void ResetButton::update() {
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (intersect(x, y)) {
		select();
	}else {
		deselect();
	}

	if(_isSelected) {
		_srect.x = 90;
		_srect.w = 110;
	}else {
		_srect.x = 0;
		_srect.w = 90;
	}
}
