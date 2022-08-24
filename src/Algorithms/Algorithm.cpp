/*
 * Algorithm.cpp
 *
 *  Created on: Jul 25, 2022
 *      Author: hector
 */

#include "Algorithm.h"

Algorithm::Algorithm()
: _isFinished(false), _isRunning(false), _steps(0)
{
	// TODO Auto-generated constructor stub

}

Algorithm::Algorithm(const NodeSet& board)
: _isFinished(false), _isRunning(false), _steps(0)
{
	for(auto it = board.begin(); it != board.end(); ++it) {
		for (auto it2 = it->begin(); it2 != it->end(); ++it2) {
			_seen.insert(std::pair<Node, bool>(*it2, false));
		}
	}
}

Algorithm::~Algorithm() {
	// TODO Auto-generated destructor stub
}

void Algorithm::resetColors() {
	for (auto v : _seen) {
		v.first->setColor(200, 200, 200);
	}
}

void Algorithm::colorPath(Node& start, Node& end){
	if (!_isFinished) return ;
	Node& current = _parent.find(end)->second;

	while(current != start) {
		current->setColor(Color::Yellow);
		current = _parent.find(current)->second;
	}
}

