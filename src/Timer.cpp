/*
 * Timer.cpp
 *
 *  Created on: Jul 15, 2022
 *      Author: hector
 */

#include "Timer.h"

std::unique_ptr<Timer> Timer::_instance;

Timer::Timer() {

}

Timer::~Timer() {
	// TODO Auto-generated destructor stub
}

const Timer & Timer::getInstance() {
	if (!_instance)
		_instance = std::make_unique<Timer>();
	return *_instance;
}
