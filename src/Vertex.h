/*
 * Vertex.h
 *
 *  Created on: Jul 8, 2022
 *      Author: hector
 */
#include "Entity.h"
#include <iostream>
#include <memory>
#include <list>

#ifndef VERTEX_H_
#define VERTEX_H_

#define MAXN 4
#define VERTEX_SIZE 20

class Vertex : public Entity{
public:
	enum Status {
		Wall,
		RealVertex
	};
	using Node = std::shared_ptr<Vertex>;

private:
	std::list<Node> _otherVertices;
	Status _status;

	friend bool isWall(Node &);

public:
	Vertex(int x = 0, int y = 0);
	virtual ~Vertex();

	Status getStatus() const ;

	void setStatus(Status);

	void addNeighboorVertex(const Node & neighboor); // _otherVertices must be not full

	const std::list<Node> getNeighboors() const;

	//bool removeNeighboor(Vertex * neighboor); // return true if the neighboor has been succesfully erased

	bool hasFourNeighboors() const;

	void render() const;

	void update();

	void detach();

	void becomeWall();

	void becomeRealVertex();

};

// Predicat function
bool isWall(Vertex::Node& n);

#endif /* VERTEX_H_ */
