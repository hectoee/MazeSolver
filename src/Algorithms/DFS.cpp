/*
 * DFS.cpp
 *
 *  Created on: Jul 26, 2022
 *      Author: hector
 */

#include "DFS.h"

DFS::DFS() {
	// TODO Auto-generated constructor stub

}

DFS::DFS(const NodeSet& board)
: Algorithm(board)
{}

DFS::~DFS() {
	// TODO Auto-generated destructor stub
}

void DFS::launch(Node& start, Node& end) {
	int startTime = Timer::getInstance().getTicks();
	_isRunning = true;
	launchREC(start, end);
	colorPath(start, end);
	start->setColor(Color::Green);
	int endTime = Timer::getInstance().getTicks();
	std::cout << "END, time : " << (endTime - startTime) << "ms" << std::endl;
}

void DFS::launchREC(Node& current, Node& end) {
	if (_seen.find(current)->second || _isFinished) return;
	if (current == end) {
		_isFinished = true;
		return;
	}

	_seen.find(current)->second = true;

	const std::list<Node> & nl = current->getNeighboors();
	for (auto n : nl) {
		_parent.insert(std::make_pair(n, current));
		launchREC(n, end);
	}
}

