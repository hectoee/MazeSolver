/*
 * Renderer.h
 *
 *  Created on: Jun 30, 2022
 *      Author: hector
 */

#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include "Color.h"

#ifndef RENDERER_H_
#define RENDERER_H_

class Renderer {
private:
	SDL_Renderer * _SDLrenderer;
	static std::unique_ptr<Renderer> _instance;

	SDL_Window * _window;

public:
	Renderer();
	virtual ~Renderer();

	Renderer & operator=(const Renderer &) = delete;
	Renderer(const Renderer &) = delete;

	SDL_Renderer * getSDLRenderer() const;

	SDL_Window * getSDLWindow() const;

	static const Renderer & getInstance();

	void clear() const;

	void renderPresent() const;

	void drawLine(int x1, int y1, int x2, int y2) const;

	void drawSquare(int x, int y, int height) const;

	void drawFilledSquare(int x, int y, int height, Color * color) const;

	void drawString(std::string, int, int) const;
};

#endif /* RENDERER_H_ */
