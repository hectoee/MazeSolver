/*
 * StartButton.h
 *
 *  Created on: Aug 17, 2022
 *      Author: hector
 */

#ifndef BUTTONS_STARTBUTTON_H_
#define BUTTONS_STARTBUTTON_H_

#include "Button.h"

class StartButton: public Button {
public:
	StartButton(int=0, int=0);
	virtual ~StartButton();

	void render();

	void update();
};

#endif /* BUTTONS_STARTBUTTON_H_ */
