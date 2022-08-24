/*
 * Button.h
 *
 *  Created on: Aug 16, 2022
 *      Author: hector
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "../Entity.h"
#include <iostream>
#include <string>
#include <SDL2/SDL.h>

class Button{
protected:
	SDL_Texture * _texture;
	SDL_Rect _srect, _drect;
	bool _isSelected;
	std::string _text;
	int _x, _y;

public:
	Button(std::string, int , int);
	Button();
	virtual ~Button();

	virtual void render() = 0;
	virtual void update() = 0;

	void deselect() { _isSelected = false; }

	void select() { _isSelected = true; }

	bool getSelect() { return _isSelected; }

	bool intersect(int, int) const;


};

#endif /* BUTTON_H_ */
