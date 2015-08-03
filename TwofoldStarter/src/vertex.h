/*
 * vertex.h
 *
 *  Created on: 3 Aug 2015
 *      Author: alexi_000
 */

#ifndef VERTEX_H_
#define VERTEX_H_

struct Vertex {
	int vertex;
	int parent;

	Vertex(int i) {
		vertex = i;
		parent = -1;
	}

	Vertex() : vertex(-1), parent(-1) {}
};


#endif /* VERTEX_H_ */
