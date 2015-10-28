/*
 * vertex.h
 *
 *  Created on: 3 Aug 2015
 *      Author: alexi_000
 */

#ifndef VERTEX_H_
#define VERTEX_H_

#include <iostream>

struct Vertex {
	int vertex;
	int parent;

	Vertex(int i) {
		vertex = i;
		parent = -1;
	}

	Vertex() : vertex(-1), parent(-2) {}

	friend std::ostream& operator<<(std::ostream& os, const Vertex& vert);
};

/*
 * For some reason, complains that it expected initializer before <<
std::ostream& operater<< (std::ostream& os, const Vertex& vert) {
	os << vert.vertex << "co" << vert.parent;
	return os;
}*/

#endif /* VERTEX_H_ */
