/*
 * World.h
 *
 *  Created on: Jul 13, 2022
 *      Author: hector
 */

#ifndef WORLD_H_
#define WORLD_H_

#include <vector>
#include <memory>
#include "Vertex.h"
#include "Renderer.h"
#include "Algorithms/DFS.h"
#include "Algorithms/BFS.h"
#include "Algorithms/Dijkstra.h"
#include "Algorithms/Astar.h"
#include "Algorithms/Algorithm.h"
#include <iostream>
#include "Buttons/Button.h"
#include "Buttons/RadioButton.h"
#include "Buttons/StartButton.h"
#include "Buttons/ResetButton.h"
#include "Maze.h"
#include <map>

#define NB_VERTEX_HOR 64
#define NB_VERTEX_VER 36
//#define NB_VERTEX_HOR 3
//#define NB_VERTEX_VER 3
#define VERTEX_SIZE 20
#define DELTA_Y 50

class World {
private:
	enum Algo {
			Dijkstra_alg,
			Astar_alg,
			BFS_alg,
			DFS_alg
	};


	using Node = std::shared_ptr<Vertex>;
	using NodeSet = std::vector<std::vector<Node>>;



	NodeSet _board;
	Node _start;
	Node _end;

	Algorithm * _alg;
	std::map<Button*, Algo> _mapButtonsAlgs;

	Button * _startButton;
	Button * _resetButton;
	Button * _clearButton;

	Maze * _maze;


public:
	World();
	virtual ~World();

	void render() const;

	void update();

	void clickButton();

	const Node & getVertexByXY(int x, int y) const;

	void setStart(int x, int y);

	void setEnd(int x, int y);

	void resetAllVerticesLinks();

	void changeStatus(int x, int y);

	void alg();

	void linkVertex(int, int);
	//void linkVertex(Vertex*);

private:
	void linkVertices();

	void detachAllVertices();

	void deselectAllButtons(Button*);

	void clearPath();

};

#endif /* WORLD_H_ */
