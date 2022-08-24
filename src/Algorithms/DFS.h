/*
 * DFS.h
 *
 *  Created on: Jul 26, 2022
 *      Author: hector
 */

#ifndef ALGORITHMS_DFS_H_
#define ALGORITHMS_DFS_H_

#include "Algorithm.h"

class DFS: public Algorithm {
public:
	DFS();
	DFS(const NodeSet&);
	virtual ~DFS();

	void launch(Node& start, Node& end);

private:
	void launchREC(Node& start, Node& end);
};

#endif /* ALGORITHMS_DFS_H_ */
