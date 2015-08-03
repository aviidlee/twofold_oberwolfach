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
#include "windows.h"

using namespace std;
struct Node {
	int vertex;
	Node* parent;
};


inline void updateDiffList(int* diffList, int diff1, int diff2) {
	diffList[diff1]++;
	diffList[diff2]++;
	return;
}

int** find_starter(int n) {
	// The current list of differences, with diffList[i] = number of occurrences of difference i.
	int diffList[n];

}

/**
 * Return the number of vertices on the cycle.
 */
inline int roll_back(int n, int vertex, int numVerts, int* cycle, int* diffList, int* available) {
	numVerts--;
	cycle[numVerts] = -1;
	decrease_diffs(n, cycle[numVerts-1], vertex, diffList);
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

/*
 *
 */
void expand_node(int n, int* available, vector<int>& stack) {
	for(int i = 0; i < n; i++) {
		if(available[i]) {
			stack.push_back(i);
		}
	}

	return;
}

/**
 *
 * @param available - the vertices we haven't yet used in a cycle.
 */
bool find_cycle(int n, int* factor, int numFactors, int cycleID, vector<int>& stack, int** cycleList, int* diffList, int* available) {
	int cycleLen = factor[cycleID];
	int* cycle = cycleList[cycleID];

	// Number of vertices currently in cycle we are working on.
	int numVerts = 0;

	/*
	 * Loop invariant: No element of diffList is greater than 2.
	 * I.e., no difference occurs more than twice.
	 */
	while(stack.size() != 0) {
		// Get the next candidate vertex from the stack.
		int next = stack[stack.size()-1];
		stack.pop_back();

		// If all of the children of a vertex are dead ends, we need to roll the vertex up.


		/* Find out if we would have too many instances of some difference if
		 * we put this on the cycle. If so, don't put this vertex on cycle.
		 */
		if(numVerts > 0) {
			if(increase_diffs(n, cycle[numVerts-1], next, diffList)) {
				cycle[numVerts] = next;
				numVerts++;
				available[next] = 0;
			} else {
				continue;
			}
		}

		// Check if we have a whole cycle
		if(numVerts == cycleLen) {
			// Check differences given by first and last vertex of cycle
			if(!increase_diffs(n, cycle[0], cycle[numVerts-1], diffList)) {
				numVerts = roll_back(n, next, numVerts, cycle, diffList, available);
				continue;
			}

			// Check if we have a 2-factor
			if(cycleID == numFactors) {
				// Everything should be dandy in terms of differences.
				return true;
			} else {
				int* nextCycle = find_cycle(n, factor, numFactors, cycleID+1, stack, cycleList, diffList, available);
				// See if we got stuck down the line.
				if(nextCycle == NULL) {
					// Roll the cycle back
					numVerts = roll_back(n, next, numVerts, cycle, diffList, available);
					continue;
				}

				cycleList[cycleID] = cycle;
				return true;
			}
		}

		/* Update stack. If we reach this line, it means we have put something on cycle,
		 * because we always 'continue' if we roll the cycle back or do nothing.
		 */
		expand_node(n, available, stack);
	}

	// No twofold 2-starter possible, return null.
	return false;
}

int main() {

	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}



