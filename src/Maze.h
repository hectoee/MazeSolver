/*
 * Maze.h
 *
 *  Created on: Aug 20, 2022
 *      Author: hector
 */

#ifndef MAZE_H_
#define MAZE_H_

#include <memory>
#include <vector>
#include "Vertex.h"
#include <cstdlib>

class Maze {
private:
	using Node = std::shared_ptr<Vertex>;
	using NodeSet = std::vector<std::vector<Node>>;

	const NodeSet & _board;

public:
	Maze(const NodeSet &);
	virtual ~Maze();

	void create();

private:
	double random() {
		return rand() / RAND_MAX;
	}


};

#endif /* MAZE_H_ */
