/*
 * Dijkstra.h
 *
 *  Created on: Jul 29, 2022
 *      Author: hector
 */

#ifndef ALGORITHMS_DIJKSTRA_H_
#define ALGORITHMS_DIJKSTRA_H_

#include "Algorithm.h"
#include <list>
#include <limits>
#include <iostream>

class Dijkstra: public Algorithm {
protected	:
	std::map<Node, unsigned int> _distance;


public:
	Dijkstra();
	Dijkstra(const NodeSet&);
	virtual ~Dijkstra();

	void launch(Node&, Node&);

private:
	void launchREC(Node&, Node&);

	bool smallestDistIsInfinity() const ;

	virtual Node getUnvisitedNodeSmallestDist(const std::list<Node>&, const Node& = std::make_shared<Vertex>());


};

#endif /* ALGORITHMS_DIJKSTRA_H_ */
