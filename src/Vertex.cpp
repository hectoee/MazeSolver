/*
 * Vertex.cpp
 *
 *  Created on: Jul 8, 2022
 *      Author: hector
 */

#include "Vertex.h"
#include "Renderer.h"
#include <cassert>
#include <algorithm>

Vertex::Vertex(int x, int y)
: Entity(x, y, new Color(200, 200, 200)), _status(Vertex::RealVertex)
{}

Vertex::~Vertex() {
}

void Vertex::addNeighboorVertex(const Node & neighboor) {
	assert(_otherVertices.size() < MAXN);
	assert(this != &(*neighboor));
	assert(std::find(_otherVertices.begin(), _otherVertices.end(), neighboor) == _otherVertices.end());
	_otherVertices.push_back(neighboor);
}

//bool Vertex::removeNeighboor(Vertex * neighboor) {
//	for (auto it = _otherVertices.begin(); it != _otherVertices.end(); ++ it) {
//		if ((*it).get() == neighboor) {
//			_otherVertices.erase(it);
//			return true;
//		}
//	}
//	return false;
//}

bool Vertex::hasFourNeighboors() const {
	return _otherVertices.size() == 4;
}

Vertex::Status Vertex::getStatus() const {
	return _status;
}

void Vertex::setStatus(Vertex::Status status) {
	_status = status;
}

void Vertex::render() const{
	const Renderer & rend = Renderer::getInstance();

	rend.drawSquare(_x, _y, VERTEX_SIZE);
	rend.drawFilledSquare(_x+1, _y+1, VERTEX_SIZE-2, _color);

}

void Vertex::update() {

}

const std::list<Vertex::Node> Vertex::getNeighboors() const {
	std::list<Node> finalList = _otherVertices;
	finalList.remove_if(isWall);
	return finalList;
}

void Vertex::detach() {
	_otherVertices.clear();
}

// it is still link to others, but others are not link to it anymore
void Vertex::becomeWall() {
	_status = Vertex::Wall;
	setColor(Color::DarkGrey);
}

void Vertex::becomeRealVertex() {
	_status = Vertex::RealVertex;
	setColor(Color::LightGrey);
}


bool isWall(Vertex::Node& n) {
	return n->getStatus() == Vertex::Wall;
}
