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

int main() {

	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}

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
inline int roll_back(int n, int next, int numVerts, int* cycle, int* diffList) {
	numVerts--;
	cycle[numVerts] = -1;
	int diffToRollBack = (cycle[numVerts-1] - next) % n;
	diffList[diffToRollBack]--;
	diffList[n-diffToRollBack]--;
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
void expand_node() {

}

/**
 *
 * @param available - the vertices we haven't used yet.
 */
int* find_cycle(int n, int* factor, int numFactors, int cycleID, vector<int>& stack, int** cycleList, int* diffList, vector<int>& available) {
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

		/* Find out if we would have too many instances of some difference if
		 * we put this on the cycle. If so, don't put this vertex on cycle.
		 */
		if(numVerts > 0) {
			int diff1 = (cycle[numVerts-1] - next) % n;
			int diff2 = n - diff1;
			if(diffList[diff1] > 1 || diffList[diff2] > 1) {
				continue;
			} else {
				cycle[numVerts] = next;
				numVerts++;
				updateDiffList(diffList, diff1, diff2);
			}
		}

		// Check if we have a whole cycle
		if(numVerts == cycleLen) {
			// Check differences given by first and last vertex of cycle
			int diff1 = (cycle[numVerts-1] - cycle[0]) % n;
			int diff2 = n - diff1;
			if(diffList[diff1] > 1 || diffList[diff2] > 1) {
				// Revert the cycle. Roll back differences - TODO abstract out into function.
				numVerts = roll_back(n, next, numVerts, cycle, diffList);
				continue;
			}

			// Check if we have a 2-factor
			if(cycleID == numFactors) {
				// Everything should be dandy in terms of differences.
				return cycle;
			} else {
				// TODO update the list of available vertices before calling!
				int* nextCycle = find_cycle(n, factor, numFactors, cycleID+1, stack, cycleList, diffList, available);
				// See if we got stuck down the line.
				if(nextCycle == NULL) {
					// Roll the cycle back
					numVerts = roll_back(n, next, numVerts, cycle, diffList);
					continue;
				}

				cycleList[cycleID] = cycle;
				return cycle;
			}
		}

		// Update stack


	}

	// No twofold 2-starter possible, return null.
	return NULL;
}



