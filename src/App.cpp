/*
 * App.cpp
 *
 *  Created on: Jun 30, 2022
 *      Author: hector
 */

#include <iostream>
#include "App.h"
#include "Renderer.h"
#include "Vertex.h"
#include "Timer.h"
#include "Algorithms/BFS.h"

std::unique_ptr<World> App::_world;

App::App()
: _running(true), _wKeyPressed(false)
{
	_world = std::make_unique<World>();
}

App::~App() {
}

int App::onExecute() {
	if(onInit() == false) {
	       return -1;
	 }

	 SDL_Event Event;

	 const Timer & timer = Timer::getInstance();
	 int oldTime = timer.getTicks();
	 int newTime;

	 while(_running) {
		 newTime = timer.getTicks();
		 if (newTime - oldTime < timer.getTargetTPS()) {
			 continue;
		 }
		 oldTime = newTime;

	     while(SDL_PollEvent(&Event)) {
	        onEvent(&Event);
	     }

	     onLoop();

	     onRender();

	 }


	 onCleanup();

	 return 0;
}

bool App::onInit() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0 ){
	return false;
	}

	if (TTF_Init() < 0) {
		return false;
	}

	const Renderer & renderer = Renderer::getInstance();

	if (renderer.getSDLWindow() == NULL)
		return false;
	if (renderer.getSDLRenderer() == NULL)
		return false;

	std::cout << "starting..." << std::endl;

	std::cout << "\nREAD ME :" << std::endl;
	std::cout << "PRESS W WHILE HOVERING OVER THE NODES TO TURN THEM INTO A WALL" << std::endl;
	std::cout << "LEFT CLICK TO SET THE START" << std::endl;
	std::cout << "RIGHT CLICK TO SET THE END" << std::endl;
	std::cout << "PRESS Q TO QUIT\n" << std::endl;

	return true;
}

void App::onEvent(SDL_Event* event) {
	switch (event->type) {
	case SDL_QUIT:
		exit();
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.y <= 50) {
			_world->clickButton();
		}
		else if(event->button.button == SDL_BUTTON_LEFT) {
			_world->setStart(event->motion.x, event->motion.y);
		}
		else if (event->button.button == SDL_BUTTON_RIGHT) {
			_world->setEnd(event->motion.x, event->motion.y);
		}
		break;
	case SDL_KEYDOWN:
		if (event->key.keysym.sym == 'q') exit();
		else if(event->key.keysym.sym == 't') {
			int x, y;
			SDL_GetMouseState(&x, &y);
			const std::shared_ptr<Vertex> & v = _world->getVertexByXY(x, y);
			const std::list<std::shared_ptr<Vertex>> & l = v->getNeighboors();
			for(auto vv : l)
				vv->setColor(0, 0, 0);
			v->setColor(0, 0, 0);
		}
		else if(event->key.keysym.sym == 'w') {
			_wKeyPressed = true;
		}else if (event->key.keysym.sym == 'd') {
			int x, y;
			SDL_GetMouseState(&x, &y);
			Vertex * v = _world->getVertexByXY(x, y).get();
			v->becomeRealVertex();

		}
		break;
	case SDL_KEYUP:
		if(event->key.keysym.sym == 'w') {
			_wKeyPressed = false;
		}
		break;
	default:
		break;
	}
}

void App::onLoop() {
	if (_wKeyPressed) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		_world->changeStatus(x, y);
	}
	_world->update();
}

void App::onRender() {
	const Renderer & rend = Renderer::getInstance();
	rend.clear();

	_world->render();
	//rend.drawString("hello",0,0);


	rend.renderPresent();
}

void App::onCleanup() {
	TTF_Quit();
	SDL_Quit();
	std::cout << "cleanup app" <<std::endl;
}

void App::exit() {
	std::cout << "exiting..." << std::endl;
	_running = false;
}

World & App::getWorld() {
	if (!_world)
		_world = std::make_unique<World>();
	return *_world;
}

