/*
 * BFS.h
 *
 *  Created on: Jul 25, 2022
 *      Author: hector
 */

#ifndef ALGORITHMS_BFS_H_
#define ALGORITHMS_BFS_H_

#include "Algorithm.h"

class BFS: public Algorithm {
private:



public:
	BFS();
	BFS(const NodeSet&);
	virtual ~BFS();

	void launch(Node& start, Node& end);

private:
	void launchREC(Node& start, Node& end){}

};

#endif /* ALGORITHMS_BFS_H_ */
