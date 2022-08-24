/*
 * Algorithm.h
 *
 *  Created on: Jul 25, 2022
 *      Author: hector
 */

#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include <vector>
#include <list>
#include <memory>
#include <map>
#include "../Vertex.h"
#include "../Timer.h"

class Algorithm {
protected:
	bool _isFinished;
	bool _isRunning;
	int _steps;

	using Node = std::shared_ptr<Vertex>;
	using NodeSet = std::vector<std::vector<Node>>;

	std::map<Node, bool> _seen;
	std::multimap<Node, Node> _parent;
			// enfant 	parent

public:
	Algorithm();
	Algorithm(const NodeSet&);
	virtual ~Algorithm();

	virtual void launch(Node& start, Node& end) = 0;

private:
	virtual void launchREC(Node& start, Node& end) = 0;

protected:
	void resetColors();

	void colorPath(Node& , Node&);

};

#endif /* ALGORITHM_H_ */
