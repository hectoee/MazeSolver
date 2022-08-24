/*
 * Timer.h
 *
 *  Created on: Jul 15, 2022
 *      Author: hector
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <memory>
#include <SDL2/SDL.h>

#define FPS 30

class Timer {
private:
	static std::unique_ptr<Timer> _instance;

public:
	Timer();
	virtual ~Timer();

	Timer(const Timer&) = delete;
	Timer & operator=(const Timer &) = delete;

	static const Timer & getInstance();

	int getTargetTPS() const { return 1000 / FPS; }

	int getTicks() const { return SDL_GetTicks(); }


};

#endif /* TIMER_H_ */
