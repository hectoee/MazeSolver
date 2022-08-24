/*
 * Astar.h
 *
 *  Created on: Jul 30, 2022
 *      Author: hector
 */

#ifndef ALGORITHMS_ASTAR_H_
#define ALGORITHMS_ASTAR_H_

#include "Dijkstra.h"

class Astar: public Dijkstra {
public:
	Astar();
	Astar(const NodeSet&);
	virtual ~Astar();

private:
	Node getUnvisitedNodeSmallestDist(const std::list<Node>&, const Node&);

	// compute straight-line distance between two vertices
	double heuristicFunction(const Node&, const Node&) const;
};

#endif /* ALGORITHMS_ASTAR_H_ */
