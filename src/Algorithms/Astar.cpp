/*
 * Astar.cpp
 *
 *  Created on: Jul 30, 2022
 *      Author: hector
 */

#include "Astar.h"
#include <cmath>

Astar::Astar() {}

Astar::Astar(const std::vector<std::vector<std::shared_ptr<Vertex>>>& board)
: Dijkstra(board)
{}

Astar::~Astar() {
	// TODO Auto-generated destructor stub
}

Algorithm::Node Astar::getUnvisitedNodeSmallestDist(const std::list<Node>& open, const Node& end) {
	double maxD = std::numeric_limits<double>::max();
	const Node * v;
	for (auto it = open.begin(); it != open.end(); ++it) {

		unsigned int dist = _distance.find(*it)->second;
		double straightLineDist = heuristicFunction(*it, end);

		if (dist +  straightLineDist < maxD) {
			maxD = dist + straightLineDist;
			v = &(*it);
		}
	}
	return *v;
}

double Astar::heuristicFunction(const Node& v1, const Node& v2) const {
	const int vertexSize = 20; // a node is 20 px, we want to compute a weight between two nodes and not a distance in px
	return sqrt( pow(v2->getY() - v1->getY(), 2) + pow(v2->getX() - v1->getX(), 2) ) / vertexSize;
}

