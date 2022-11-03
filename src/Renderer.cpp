/*
 * Renderer.cpp
 *
 *  Created on: Jun 30, 2022
 *      Author: hector
 */

#include "Renderer.h"
#include <iostream>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>

#define WIN_HEIGHT 770
#define WIN_WIDTH 1280

std::unique_ptr<Renderer> Renderer::_instance;

Renderer::Renderer() {
	SDL_CreateWindowAndRenderer(WIN_WIDTH, WIN_HEIGHT,SDL_WINDOW_OPENGL, &_window, &_SDLrenderer);
	TTF_Init();
	SDL_SetWindowTitle(_window, "Path finding application");
}

Renderer::~Renderer() {
	SDL_DestroyRenderer(_SDLrenderer);
	SDL_DestroyWindow(_window);
}

SDL_Renderer* Renderer::getSDLRenderer() const {
	return _SDLrenderer;
}

SDL_Window* Renderer::getSDLWindow() const {
	return _window;
}

const Renderer & Renderer::getInstance() {
	if (!_instance)
		_instance = std::make_unique<Renderer>();
	return *_instance;
}

void Renderer::clear() const {
	SDL_SetRenderDrawColor(_SDLrenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(_SDLrenderer);
}

void Renderer::renderPresent() const {
	SDL_RenderPresent(_SDLrenderer);
}

void Renderer::drawLine(int x1, int y1, int x2, int y2) const {
	SDL_SetRenderDrawColor(_SDLrenderer, 100, 100, 100, SDL_ALPHA_OPAQUE);
	if (SDL_RenderDrawLine(_SDLrenderer, x1, y1, x2, y2) < 0) {
		std::cout << "Error when drawing line" << std::endl;
		exit(-1);
	}
}

void Renderer::drawSquare(int x, int y, int height) const {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = height;
	rect.h = height;

	SDL_SetRenderDrawColor(_SDLrenderer, 100, 100, 100, SDL_ALPHA_OPAQUE);
	if( SDL_RenderDrawRect(_SDLrenderer, &rect) < 0) {
		std::cout << "Error when drawing rect" << std::endl;
		exit(-1);
	}
}

void Renderer::drawFilledSquare(int x, int y, int height, Color * color) const {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = height;
	rect.h = height;

	SDL_SetRenderDrawColor(_SDLrenderer, color->operator [](0), color->operator [](1), color->operator [](2), SDL_ALPHA_OPAQUE);
	if (SDL_RenderFillRect(_SDLrenderer, &rect) < 0) {
		std::cout << "Error when drawing filled rect" << std::endl;
		exit(-1);
	}
}


void Renderer::drawString(std::string str, int x, int y) const {
	//this opens a font style and sets a size
	TTF_Font* Sans = TTF_OpenFont("../fonts/OpenSans-Light.ttf", 24);

	// this is the color in rgb format,
	// maxing out all would give you the color white,
	// and it will be your text's color
	SDL_Color White = {0, 0, 0};

	if (Sans == nullptr) {
		std::cout << TTF_GetError() << std::endl;
	}

	// as TTF_RenderText_Solid could only be used on
	// SDL_Surface then you have to create the surface first
	SDL_Surface* surfaceMessage;
	if ((surfaceMessage = TTF_RenderText_Solid(Sans, str.c_str(), White)) == NULL) {
		std::cout << "error when getting surface : " << SDL_GetError() << std::endl;
	}
	TTF_CloseFont(Sans);

	// now you can convert it into a texture
	SDL_Texture* Message = SDL_CreateTextureFromSurface(_SDLrenderer, surfaceMessage);

	SDL_Rect Message_rect; //create a rect
	Message_rect.x = x;  //controls the rect's x coordinate
	Message_rect.y = y; // controls the rect's y coordinte
	Message_rect.w = 25 * str.size(); // controls the width of the rect
	Message_rect.h = 35; // controls the height of the rect

	// (0,0) is on the top left of the window/screen,
	// think a rect as the text's box,
	// that way it would be very simple to understand

	// Now since it's a texture, you have to put RenderCopy
	// in your game loop area, the area where the whole code executes

	// you put the renderer's name first, the Message,
	// the crop size (you can ignore this if you don't want
	// to dabble with cropping), and the rect which is the size
	// and coordinate of your texture
	SDL_RenderCopy(_SDLrenderer, Message, NULL, &Message_rect);
	SDL_DestroyTexture(Message);
	SDL_FreeSurface(surfaceMessage);

}










