/*
 * World.cpp
 *
 *  Created on: Jul 13, 2022
 *      Author: hector
 */

#include "World.h"
#include "Buttons/RadioButton.h"


World::World() {
	// fill _board with vertices
	for (int i = 0; i < NB_VERTEX_VER; ++i) {
		std::vector<Node> * ptr_v = new std::vector<Node>();
		_board.push_back(*ptr_v);
		for (int j = 0; j < NB_VERTEX_HOR; ++j) {
			_board[i].push_back(std::make_shared<Vertex>(j * VERTEX_SIZE, i * VERTEX_SIZE + DELTA_Y));
		}
	}

	// link the vertices
	linkVertices();

	_mapButtonsAlgs.insert(std::pair<Button*, Algo>(new RadioButton("Dijkstra", 5, 0), World::Dijkstra_alg));
	_mapButtonsAlgs.insert(std::pair<Button*, Algo>(new RadioButton("A*", 260, 0), World::Astar_alg));
	_mapButtonsAlgs.insert(std::pair<Button*, Algo>(new RadioButton("DFS", 360, 0), World::DFS_alg));
	_mapButtonsAlgs.insert(std::pair<Button*, Algo>(new RadioButton("BFS", 490, 0), World::BFS_alg));

	_startButton = new StartButton(1065, 0);
	_resetButton = new ResetButton("Reset", 850, 0);
	_clearButton = new ResetButton("Clear", 650, 0);

	_maze = new Maze(_board);
	_maze->create();

}

World::~World() {
	auto it = _mapButtonsAlgs.begin();
	while (it != _mapButtonsAlgs.end()) {
		delete it->first;
		it = _mapButtonsAlgs.erase(it);
	}
	if (_alg)
		delete _alg;
	if (_startButton)
		delete _startButton;
	if (_resetButton)
		delete _resetButton;
	if (_maze)
		delete _maze;
	detachAllVertices();
}

void World::linkVertices() {
	for(long unsigned int i = 0; i < _board.size(); ++i) {
		for(long unsigned int j = 0; j <_board[i].size(); ++j) {
			linkVertex(i, j);
		}
	}
}

void World::linkVertex(int i, int j) {
	// linking top vertex if possible
	try {
		_board[i][j]->addNeighboorVertex(_board.at(i-1).at(j));
	}catch(std::exception& e){
		//std::cout << "Top vertex out of range : " << e.what() << std::endl;
	}

	// linking right vertex if possible
	try {
		_board[i][j]->addNeighboorVertex(_board.at(i).at(j+1));
	}catch(std::exception& e){
		//std::cout << "Right vertex out of range : " << e.what() << std::endl;
	}

	// linking bottom vertex if possible
	try {
		_board[i][j]->addNeighboorVertex(_board.at(i+1).at(j));
	}catch(std::exception& e){
		//std::cout << "Bottom vertex out of range : " << e.what() << std::endl;
	}

	// linking left vertex if possible
	try {
		_board[i][j]->addNeighboorVertex(_board.at(i).at(j-1));
	}catch(std::exception& e){
		//std::cout << "Left vertex out of range : " << e.what() << std::endl;
	}
}

//void World::linkVertex(Vertex * v) {
//	unsigned int x = (v->getY() - DELTA_Y) / VERTEX_SIZE;
//	unsigned int y = v->getX() / VERTEX_SIZE;
//	linkVertex(x, y);
//}

void World::detachAllVertices() {
	for (long unsigned int i = 0; i < _board.size(); ++i) {
		for(long unsigned int j = 0; j < _board[i].size(); ++j) {
			_board[i][j]->detach();
		}
	}
}

void World::resetAllVerticesLinks() {
	detachAllVertices();
	linkVertices();
	for (auto it = _board.begin(); it != _board.end(); ++it) {
		for (auto it2 = it->begin(); it2 != it->end(); ++ it2) {
			it2->get()->becomeRealVertex();
		}
	}
	_start.reset();
	_end.reset();
}

void World::render() const {
	for (auto it = _board.begin(); it != _board.end(); ++it) {
		for (auto it2 = it->begin(); it2 != it->end(); ++ it2) {
			it2->get()->render();
		}
	}
	for (auto it = _mapButtonsAlgs.begin(); it != _mapButtonsAlgs.end(); ++ it) {
		it->first->render();
	}
	_startButton->render();
	_resetButton->render();
	_clearButton->render();
}

void World::update() {
	for (auto it = _mapButtonsAlgs.begin(); it != _mapButtonsAlgs.end(); ++ it) {
		it->first->update();
	}
	_startButton->update();
	_resetButton->update();
	_clearButton->update();

}

void World::clickButton() {
	int x, y;
	SDL_GetMouseState(&x, &y);
	for (auto it = _mapButtonsAlgs.begin(); it != _mapButtonsAlgs.end(); ++ it) {
		if (it->first->intersect(x, y)) {
			if (it->first->getSelect()) {
				it->first->deselect();
			}
			else {
				it->first->select();
				deselectAllButtons(it->first);
			}
		}
	}

	if (_startButton->intersect(x, y)){
		alg();
	}else if(_resetButton->intersect(x, y)) {
		resetAllVerticesLinks();
	}else if(_clearButton->intersect(x, y)) {
		clearPath();
	}
}

void World::clearPath() {
	for (auto it = _board.begin(); it != _board.end(); ++it) {
		for (auto it2 = it->begin(); it2 != it->end(); ++it2) {
			if (Color::Yellow == (*it2)->getColor()) {
				(*it2)->setColor(Color::LightGrey);
			}
		}
	}
}

void World::deselectAllButtons(Button* b) {
	for (auto it = _mapButtonsAlgs.begin(); it != _mapButtonsAlgs.end(); ++ it) {
		if (it->first != b)
			it->first->deselect();
	}
}

const World::Node & World::getVertexByXY(int x, int y) const {
	y -= DELTA_Y;
	int vertexNBX = (int) y / VERTEX_SIZE;
	int vertexNBY = (int) x / VERTEX_SIZE;

	if (vertexNBX < 0) return _board[0][vertexNBY];

	return _board[vertexNBX][vertexNBY];

}


void World::setStart(int x, int y) {
	if (_start) {
		_start->setColor(Color::LightGrey);
	}
	_start = getVertexByXY(x, y);
	_start->setColor(Color::Green);
}

void World::setEnd(int x, int y) {
	if (_end) {
		_end->setColor(Color::LightGrey);
	}
	_end = getVertexByXY(x, y);
	_end->setColor(Color::Red);
}

void World::changeStatus(int x, int y) {
	const Node & v = getVertexByXY(x, y);
	if(v == _start || v == _end) return;
	if (v->getStatus() == Vertex::RealVertex)
		v->becomeWall();
}

void World::alg() {
	if(!_start || !_end) return ;

	if (_alg)
		delete _alg;

	World::Algo algo;
	for (auto it = _mapButtonsAlgs.begin(); it != _mapButtonsAlgs.end(); ++ it) {
		if (it->first->getSelect())
			algo = it->second;
	}

	switch (algo) {
	case World::Dijkstra_alg:
		_alg = new Dijkstra(_board);
		break;
	case World::Astar_alg:
		_alg = new Astar(_board);
		break;
	case World::BFS_alg:
		_alg = new BFS(_board);
		break;
	case World::DFS_alg:
		_alg = new DFS(_board);
		break;
	default:
		break;
	}

	if (!_alg) return ;


	std::cout << "STARTING ALG" << std::endl;
	_alg->launch(_start, _end);
}





















