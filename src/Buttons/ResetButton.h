/*
 * ResetButton.h
 *
 *  Created on: Aug 18, 2022
 *      Author: hector
 */

#ifndef BUTTONS_RESETBUTTON_H_
#define BUTTONS_RESETBUTTON_H_

#include "Button.h"

class ResetButton: public Button {
public:
	ResetButton(const char *, int=0, int=0);
	virtual ~ResetButton();

	void render();

	void update();
};

#endif /* BUTTONS_RESETBUTTON_H_ */
