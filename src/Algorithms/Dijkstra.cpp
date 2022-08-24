/*
 * Dijkstra.cpp
 *
 *  Created on: Jul 29, 2022
 *      Author: hector
 */

#include "Dijkstra.h"
#include <algorithm>

Dijkstra::Dijkstra()
: Algorithm()
{}

Dijkstra::Dijkstra(const NodeSet& board)
: Algorithm(board)
{
	for(auto it = board.begin(); it != board.end(); ++it) {
		for (auto it2 = it->begin(); it2 != it->end(); ++it2) {
			_distance.insert(std::pair<Node, unsigned int>(*it2, std::numeric_limits<unsigned int>::max()));
		}
	}
}

Dijkstra::~Dijkstra() {

}

/*
 * RECURSIVE VERSION
 */

//void Dijkstra::launch(Node& start, Node& end) {
//	_isRunning = true;
//	_distance.find(start)->second = 0;
//	launchREC(start, end);
//	colorPath(start, end);
//	std::cout << "END OF ALG" << std::endl;
//}
//
//void Dijkstra::launchREC(Node& current, Node& end) {
//	if (current == end || _isFinished) {
//		_isFinished = true;
//		_isRunning = false;
//		return ;
//	}
//
//	const std::vector<Node>& nlist = current->getNeighboors();
//	unsigned int currentDist = _distance.find(current)->second;
//
//
//	for (auto& n : nlist) {
//		unsigned int & nDist = _distance.find(n)->second;
//		if(_seen.find(n)->second) continue;
//		_parent.insert(std::make_pair(n, current));
//		if (nDist > currentDist + 1) {
//			nDist = currentDist + 1;
//		}
//	}
//
//	_seen.find(current)->second = true;
//
//	if (smallestDistIsInfinity()) {
//		_isFinished = true;
//		_isRunning = false;
//		return ;
//	}
//	//current->setColor(new Color(255, 255, 0));
//
//	Node next = getUnvisitedNodeSmallestDist(end);
//
// 	launchREC(next, end);
//
//}

/*
 * ITERATIF VERSION
 */


//void Dijkstra::launch(Node& start, Node& end) {
//	_isRunning = true;
//
//	Node current = start;
//
//	while (current != end && !_isFinished) {
//		const std::vector<Node>& nlist = current->getNeighboors();
//		unsigned int currentDist = _distance.find(current)->second;
//
//		for (auto& n : nlist) {
//			unsigned int & nDist = _distance.find(n)->second;
//			if(_seen.find(n)->second) continue;
//			_parent.insert(std::make_pair(n, current));
//			if (nDist > currentDist + 1) {
//				nDist = currentDist + 1;
//			}
//		}
//
//		_seen.find(current)->second = true;
//		//current->setColor(255, 255, 0);
//		if (smallestDistIsInfinity()) {
//			std::cout << "NO PATH FOUND..." << std::endl;
//			std::cout << "maybe, the start is surrounded by walls" << std::endl;
//			_isFinished = true;
//			_isRunning = false;
//			return;
//		}
//
//		current = getUnvisitedNodeSmallestDist(end);
//
//	}
//
//	_isRunning = false;
//	_isFinished = true;
//
//	std::cout << "END OF ALG" << std::endl;
//	colorPath(start, end);
//}


void Dijkstra::launch(Node & start, Node & end) {
	int startTime = Timer::getInstance().getTicks();

	std::list<Node> open;
	std::list<Node> close; // all seen nodes

	open.push_back(start);
	_distance.find(start)->second = 0;

	bool endFound;

	while (!open.empty()) {
		Node q = getUnvisitedNodeSmallestDist(open, end);

		open.remove(q);

		unsigned int currentDist = _distance.find(q)->second;
		for (const Node& n : q->getNeighboors()) {
			if (std::find(close.begin(), close.end(), n) != close.end()) continue; // n is already seen

			_parent.insert(std::make_pair(n, q));
			if (n == end) {
				endFound = true;
				goto endOfAlg;
			}

			unsigned int & nDist = _distance.find(n)->second;
			nDist = std::min(nDist, currentDist + 1);
			open.push_back(n);
		}

		close.push_back(q);
	}

endOfAlg:

	int endTime = Timer::getInstance().getTicks();
	std::cout << "END, time : " << (endTime - startTime) << "ms" << std::endl;
	_isFinished = true;
	if (endFound) {
		colorPath(start, end);
	}else {
		std::cout << "NO PATH FOUND..." << std::endl;
		std::cout << "maybe, the start or the end are surrounded by walls" << std::endl;
	}

}

void Dijkstra::launchREC(Node&, Node&) {}

bool Dijkstra::smallestDistIsInfinity() const {
	for (auto it = _seen.begin(); it != _seen.end(); ++it) {
		if(it->second) continue;
		auto it_pair = _distance.find(it->first);
		unsigned int dist = it_pair->second;
//		unsigned int dist = it_pair == _distance.end() ? std::numeric_limits<unsigned int>::max(): it_pair->second;
		if(dist < std::numeric_limits<unsigned int>::max()) return false;
	}
	return true;
}

Algorithm::Node Dijkstra::getUnvisitedNodeSmallestDist(const std::list<Node>& open, const Node&) {
	unsigned int maxD = std::numeric_limits<unsigned int>::max();
	//const Node* v;
	Node v;
	for (auto it = open.begin(); it != open.end(); ++it) {
		unsigned int dist = _distance.find(*it)->second;

		if (dist < maxD) {
			maxD = dist;
			v = *it;
		}
	}
	return v;
}



















