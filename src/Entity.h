/*
 * Entity.h
 *
 *  Created on: Jul 13, 2022
 *      Author: hector
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include "Color.h"

#define VERTEX_SIZE 20

// an entity can be drawn on screen
class Entity {
protected:
	int _x, _y;
	Color * _color;

public:
	Entity(int x = 0, int y = 0, Color * color = new Color());
	Entity();
	virtual ~Entity();

	virtual void render() const = 0;
	virtual void update() = 0;

	int getX() { return _x; }
	int getY() { return _y; }
	const Color & getColor() { return *_color; }
	void setColor(int,int,int);
	void setColor(const Color&);
};

#endif /* ENTITY_H_ */
