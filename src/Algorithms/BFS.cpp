/*
 * BFS.cpp
 *
 *  Created on: Jul 25, 2022
 *      Author: hector
 */

#include "BFS.h"
#include "SDL2/SDL.h"
#include <queue>

BFS::BFS()
: Algorithm()
{}

BFS::BFS(const NodeSet& board)
: Algorithm(board)
{}

BFS::~BFS() {
	// TODO Auto-generated destructor stub
}

void BFS::launch(Node& start, Node& end) {
	int startTime = Timer::getInstance().getTicks();

	std::queue<Node> queue;
	queue.push(start);

	_seen.find(queue.front())->second = true;

	while (!queue.empty()) {
		if (queue.front() == end) {
			_isFinished = true;
			break;
		}


		const std::list<Node> & nl = queue.front()->getNeighboors();

		for (auto it = nl.begin(); it != nl.end(); ++it) {
			if (_seen.find(*it)->second) continue;
			queue.push(*it);
			_seen.find(*it)->second = true;
			_parent.insert(std::make_pair(*it, queue.front()));
		}
		queue.pop();
	}

	colorPath(start, end);
	end->setColor(Color::Red);
	int endTime = Timer::getInstance().getTicks();
	std::cout <<  "END, time : " << (endTime - startTime) << "ms" << std::endl;
}




