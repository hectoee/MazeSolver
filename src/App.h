/*
 * App.h
 *
 *  Created on: Jun 30, 2022
 *      Author: hector
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <memory>
#include "World.h"

#ifndef APP_H_
#define APP_H_

class App {
private:
	bool _running;
	bool _wKeyPressed;

	static std::unique_ptr<World> _world;

public:
	App();
	virtual ~App();

	int onExecute();

	bool onInit();

	void onEvent(SDL_Event* event);

	void onLoop();

	void onRender();

	void onCleanup();

	void exit();

	static World & getWorld();

};

#endif /* APP_H_ */
