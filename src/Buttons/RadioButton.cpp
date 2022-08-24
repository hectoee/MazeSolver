/*
 * AlgButton.cpp
 *
 *  Created on: Aug 16, 2022
 *      Author: hector
 */

#include "RadioButton.h"
#include "../Renderer.h"
#include <SDL2/SDL_image.h>
#include <iostream>

RadioButton::RadioButton(std::string text, int x, int y)
: Button(text, x, y)
{
	_srect.h = 80;
	_srect.w = 80;
	_srect.x = 15;
	_srect.y = 60;

	_drect.h = 40;
	_drect.w = 40;
	_drect.x = x;
	_drect.y = y+5;
}

RadioButton::~RadioButton() {

}

void RadioButton::render() {
	static SDL_Texture * t = IMG_LoadTexture(Renderer::getInstance().getSDLRenderer(), "assets/radio_buttons.png");
	_texture = t;
	Renderer::getInstance().drawString(_text, _x + 40, _y+5);
	if(SDL_RenderCopy(Renderer::getInstance().getSDLRenderer(), _texture, &_srect, &_drect) < 0)
		std::cout << SDL_GetError() << std::endl;
	if (_texture == nullptr) std::cout << "text : nullptr" << std::endl;
}

void RadioButton::update() {
	if(_isSelected) {
		_srect.x = 112;
	}else {
		_srect.x = 15;
	}
}

