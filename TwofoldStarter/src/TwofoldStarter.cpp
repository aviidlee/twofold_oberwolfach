//============================================================================
// Name        : TwofoldStarter.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Finds a twofold 2-starter, if one exists.
//============================================================================

/*
 * TODO next:
 *
 */

#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include "windows.h"
#include "vertex.h"

using std::vector;
using std::cout;
using std::cin;
using std::endl;

void initialise_cycle_list(int numCycles, int* factor, Vertex** cycleList) {
	for(int i = 0; i < numCycles; i++) {
		cycleList[i] = new Vertex[factor[i]]();
	}

	return;
}

void init_theStack(int n, vector<Vertex>& theStack) {
	for(int i = 0; i < n; i++) {
		Vertex v;
		v.vertex = i;
		theStack.push_back(v);
	}
}

void init_available(int len, int* available) {
	for(int i = 0; i < len; i++) {
		available[i] = 1;
	}

	return;
}

/*
 * Remember to take into account the infinity vertex, which is n for us.
 */
inline bool increase_diffs(int n, int previous, int next, int* diffList) {
	// Either this vertex or the next is the infinity vertex
	if(previous == n || next == n) {
		return true;
	}
	int diff1 = (next - previous) % n;
	int diff2 = n - diff1;
	if(diffList[diff1] > 1 || diffList[diff2] > 1) {
		return false;
	} else {
		diffList[diff1]++;
		diffList[diff2]++;
		return true;
	}
}

inline void decrease_diffs(int n, int previous, int next, int* diffList) {
	if(previous == n || next == n) {
		return;
	}

	int diff1 = (next - previous) % n;
	int diff2 = n - diff1;

	diffList[diff1]--;
	diffList[diff2]--;

	return;
}

/**
 * Return the number of vertices on the cycle.
 */
inline int roll_back(int n, int vertex, int numVerts, Vertex* cycle, int* diffList, int* available) {
	numVerts--;
	cycle[numVerts].vertex = -1;
	decrease_diffs(n, cycle[numVerts-1].vertex, vertex, diffList);
	available[vertex] = 1;
	return numVerts;
}

/**
 * Return number of vertices now on the cycle.
 */
inline int add_to_cycle() {
	return -1;
}


/*
 *
 */
void expand_Vertex(int n, int parent, int* available, vector<Vertex>& theStack) {
	for(int i = 0; i < n; i++) {
		if(available[i]) {
			Vertex* vertex = new Vertex(i);
			vertex->parent = parent;
			theStack.push_back(*vertex);
		}
	}

	return;
}

/**
 *
 * @param available - the vertices we haven't yet used in a cycle.
 */
bool find_cycle(int n, int* factor, int numFactors, int cycleID, vector<Vertex>& theStack, Vertex** cycleList, int* diffList, int* available) {
	int cycleLen = factor[cycleID];
	Vertex* cycle = cycleList[cycleID];

	// Number of vertices currently in cycle we are working on.
	int numVerts = 0;

	/*
	 * Loop invariant: No element of diffList is greater than 2.
	 * I.e., no difference occurs more than twice.
	 */
	while(theStack.size() != 0) {
		// Get the next candidate vertex from the theStack.
		Vertex nextVertex = theStack[theStack.size()-1];
		int next = nextVertex.vertex;
		theStack.pop_back();

		// If all of the children of a vertex on the cycle are dead ends, we need to roll the vertex up.
		while(numVerts >0 && nextVertex.parent != cycle[numVerts-1].vertex) {
			numVerts = roll_back(n, cycle[numVerts-1].vertex, numVerts, cycle, diffList, available);
		}

		/* Find out if we would have too many instances of some difference if
		 * we put this on the cycle. If so, don't put this vertex on cycle.
		 */
		if(numVerts > 0) {
			if(increase_diffs(n, cycle[numVerts-1].vertex, next, diffList)) {
				cycle[numVerts] = nextVertex;
				numVerts++;
				available[next] = 0;
			} else {
				continue;
			}
		}

		// Check if we have a whole cycle
		if(numVerts == cycleLen) {
			// Check differences given by first and last vertex of cycle
			if(!increase_diffs(n, cycle[0].vertex, cycle[numVerts-1].vertex, diffList)) {
				numVerts = roll_back(n, next, numVerts, cycle, diffList, available);
				continue;
			}

			// Check if we have a 2-factor
			if(cycleID == numFactors) {
				// Everything should be dandy in terms of differences.
				return true;
			} else {
				// See if we got stuck down the line.
				if(!find_cycle(n, factor, numFactors, cycleID+1, theStack, cycleList, diffList, available)) {
					// Roll the cycle back
					numVerts = roll_back(n, next, numVerts, cycle, diffList, available);
					continue;
				}

				cycleList[cycleID] = cycle;
				return true;
			}
		}

		/* Update theStack. If we reach this line, it means we have put something on cycle,
		 * because we always 'continue' if we roll the cycle back or do nothing.
		 */
		expand_Vertex(n, nextVertex.parent, available, theStack);
	}

	// No twofold 2-starter possible, return null.
	return false;
}

bool find_starter(int n, int numCycles, int* factor, Vertex** cycleList) {
	// The current list of differences, with diffList[i] = number of occurrences of difference i.
	int diffList[n];
	initialise_cycle_list(numCycles, factor, cycleList);
	vector<Vertex> theStack;
	init_theStack(n, theStack);
	int available[n+1];
	init_available(n+1, available);
	return find_cycle(n, factor, numCycles, 0, theStack, cycleList, diffList, available);
}

int main(int argc, char** argv) {

	cout << "Looking for amazingly awesome twofold 2-factors!!!" << endl;
	if(argc < 3) {
		cout << "Usage: findstarter n t l_1 l_2 ... l_t where n is number of Vertexs, t is number of cycles, l_i are cycle lengths" << endl;
		return -1;
	}

	int n = atoi(argv[1]);
	int numCycles = atoi(argv[2]);
	if(argc - 3 != numCycles) {
		cout << "Too few or too many cycle lengths entered." << endl;
		return -1;
	}

	if(n < 3 || numCycles < 1) {
		cout << "Too few Vertexs or too few cycles!" << endl;
		return -1;
	}

	int cycleLenSum = 0;
	int factor[numCycles];
	for(int i = 0; i < numCycles; i++) {
		int len = atoi(argv[3+i]);
		factor[i] = len;
		cycleLenSum += len;
		if(len < 3) {
			cout << "Cycle length must be at least 3." << endl;
			return -1;
		}
	}

	if(n != cycleLenSum) {
		cout << "Your cycle lengths do not sum to " << n << endl;
		return -1;
	}
	cout << "Trying to compute a twofold 2-starter with cycle lengths " << factor << endl;

	Vertex* cycleList[numCycles];
	find_starter(n, numCycles, factor, cycleList);
	return 0;
}



