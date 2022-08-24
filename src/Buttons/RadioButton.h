/*
 * AlgButton.h
 *
 *  Created on: Aug 16, 2022
 *      Author: hector
 */

#ifndef ALGBUTTON_H_
#define ALGBUTTON_H_

#include "Button.h"

class RadioButton: public Button {
public:
	RadioButton(std::string, int, int);
	RadioButton();
	virtual ~RadioButton();

	void render();

	void update();
};

#endif /* ALGBUTTON_H_ */
