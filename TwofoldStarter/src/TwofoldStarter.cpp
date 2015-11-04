//============================================================================
// Name        : TwofoldStarter.cpp
// Author      : Alex Lee
// Version     : 1.0
// Description : Finds a twofold 2-starter, if one exists.
//============================================================================
#include "twofoldstarter.h"

#define DEBUG false
#define MSG(msg, info) std::cout << msg << info << std::endl;

// GLOBALS
// The infinity element, n-1.
int INF;

/*
 * For some reason cannot overload ostream's <<, so need to print 2-factors manually.
 *
 * @param numCycles - the number of cycles in cycleList 
 * @param factor - array such that factor[i] is the length of the i-th cycle
 * @param cycleList - array such that cycleList[i][j] is the j-th vertex on the i-th cycle
 *
 * @return a string representation of cycleList, in the form [cycle1, cycle2, ..., cyclet]
 *         for example, [[1, 2, 3][4, 5, 6]]
 */
string str_cycle_list(int numCycles, int* factor, Vertex** cycleList) {
	stringstream ss;
	ss << "[";
	for(int i = 0; i < numCycles; i++) {
		ss << "[";
		for(int j = 0; j < factor[i]-1; j++) {
			ss << cycleList[i][j].vertex << ", ";
		}
		ss << cycleList[i][factor[i]-1].vertex << "]";
	}
	ss << "]";

	return ss.str();
}

/*
 * Return a string representation of an integer array.
 * @param len - the length of array 
 * @param array - the array of integers to string-ify
 *
 * @return a string representation of array of the form [1, 2, 3]
 */
string str_int_array(int len, int* array) {
	stringstream ss;
	ss << "[";
	for(int i = 0; i < len-1; i++) {
		ss << array[i] << ",";
	}
	ss << array[len-1] << "]";

	return ss.str();
}

/**
 * Marks all the vertices as being available.
 * Intended to be called by find_starter.
 *
 * @param len - the length of the available array, n.
 * @param available - array in which available[i]= 1 iff vertex
 * 					  i has not been used in the starter yet.
 */
void init_available(int len, int* available) {
	for(int i = 0; i < len; i++) {
		available[i] = 1;
	}

	return;
}

/**
 * Initialises an array of array of Vertex objects, where each array
 * of Vertex objects represents a cycle.
 *
 * @param numCycles - the number of cycles in the starter
 * @param factor - an array of length numCycles in which factor[i] is the
 * 				   length of the i-th cycle.
 * @param cycleList - an array of pointers to Vertex objects, of length numCycles.
 */
void initialise_cycle_list(int numCycles, int* factor, Vertex** cycleList) {
	for(int i = 0; i < numCycles; i++) {
		cycleList[i] = new Vertex[factor[i]]();
	}

	return;
}

/**
 * Puts all the unused vertices on the stack.
 *
 * @param n - the order of the OP
 * @param avaiable - array of length n in which available[i] == 1
 * 					 iff vertex i has not yet been used.
 * @param theStack - the main stack used in our DFS.
 */
void init_theStack(int n, int* available, vector<Vertex>& theStack) {
	for(int i = 0; i < n; i++) {
		if(available[i]) {
			Vertex v;
			v.vertex = i;
			theStack.push_back(v);
		}
	}

	return;
}

/*
 * Calculates the differences given by the vertices previous and next,
 * and if we do not already have 2 of those differences, increments the difference
 * list accordingly and returns true. Otherwise, do nothing and return false.
 *
 * Uses the global variable INF = n-1, the order of the group.
 *
 * @param previous - a vertex
 * @param next - another vertex distinct from previous
 * @param diffList - an array of length n-2 in which diffList[i] indicates
 * 					 the number of times the difference i (modulo n-1) has
 * 					 occurred so far.
 * @return true iff the difference previous - next (and next - previous) have
 * 					occured at most once prior to the call of this method.
 */
inline bool increase_diffs(int previous, int next, int* diffList) {

	// Either this vertex or the next is the infinity vertex
	if(previous == INF || next == INF) {
		return true;
	}

	int diff1 = mod(INF, previous - next);
	int diff2 = (INF) - diff1;

	if(diffList[diff1] > 1 || diffList[diff2] > 1) {
		return false;
	} else {
		diffList[diff1]++;
		diffList[diff2]++;
		return true;
	}
}

/**
 * Calculates the difference (modulo n-1) given by the vertices previous
 * and next, and decreases them by 1. Used when rolling back vertices.
 *
 * @param previous - a vertex
 * @param next - a vertex distinct from previous
 * @param diffList - an array of length n-2 in which diffList[i] indicates
 * 					 the number of times the difference i (modulo n-1) has
 * 					 occurred so far.
 */
inline void decrease_diffs(int previous, int next, int* diffList) {
	//MSG("decreasing diffs", "")

	if(previous == INF || next == INF) {
		return;
	}

	int diff1 = mod(INF, previous - next);
	int diff2 = INF - diff1;

	diffList[diff1]--;
	diffList[diff2]--;

	return;
}

/**
 * Takes off the last vertex on the cycle, decrementing the counter numVerts,
 * updating the diffList and available arrays.
 *
 * @param cycle - the cycle from which we are rolling back the last (highest index,
 * 				  at numVertex-1) vertex.
 * @param diffList - the array of length n-2 in which diffList[i] indicates
 * 					 the number of times the difference i (modulo n-1) has
 * 					 occurred so far.
 * @param available - array of length n in which available[i] == 1
 * 					  iff vertex i has not yet been used.
 *
 * @return the number of vertices now on the cycle (numVerts - 1).
 */
inline int roll_back(int numVerts, Vertex* cycle, int* diffList, int* available) {
	//MSG("Rolling back vertex ", vertex)
	numVerts--;
	int vertex = cycle[numVerts].vertex;
	cycle[numVerts].vertex = -1;
	if(numVerts > 0) {
		decrease_diffs(cycle[numVerts-1].vertex, vertex, diffList);
	}
	available[vertex] = 1;
	//MSG("Cycle length is now ", numVerts)
	return numVerts;
}

/*
 * Pushes onto the stack all the vertices which could follow the vertex parent;
 * i.e., all the vertices that have not been used yet. Sets the parent of the each
 * child vertex to parent.
 *
 * @param n - the order of the OP
 * @param parent - the parent vertex, the last vertex on the cycle.
 * @param theStack - the main stack being used for the DFS.
 */
void expand_vertex(int n, int parent, int* available, vector<Vertex>& theStack) {
	for(int i = 0; i < n; i++) {
		if(available[i]) {
			Vertex v;
			v.vertex = i;
			v.parent = parent;
			theStack.push_back(v);
		}
	}

	return;
}

/**
 * Intended to be called only by find_starter.
 * Tries to find the next cycle of the starter, given we have set cycleID-1 cycles
 * 
 * @param n - the order of the OP
 * @param factor - an array of length numCycles in which factor[i] is the
 * 				   length of the i-th cycle.
 * @param numCycles - the number of cycles in the 2-factor.
 * @param cycleID - we are trying to label the cycleID-th cycle in the starter.
 * @param cycleList - the starter so far, with cycleList[i][j] being the j-th vertex of the i-th cycle.
 * @param diffList - array such that diffList[i] is the number of times the difference i occurs in cycleList.
 * 
 * @return true iff we could find a twofold 2-starter with the first numCycles-1 cycles of the starter being
 *         the union of cycleList[i] for i=0 to numCycles-1
 */
bool find_cycle(int n, int* factor, int numCycles, int cycleID, Vertex** cycleList, int* diffList, int* available) {

	vector<Vertex> theStack;
	init_theStack(n, available, theStack);

	//MSG("Looking for cycle number ", cycleID)
	//MSG("The available array: ", str_int_array(n, available))
	//MSG("Current cycleList: ", str_cycle_list(numCycles, factor, cycleList))
	//MSG("Differences: ", str_int_array(n-1, diffList))

	int cycleLen = factor[cycleID];
	Vertex* cycle = cycleList[cycleID];

	// Number of vertices currently in cycle we are working on.
	int numVerts = 0;

	/*
	 * Loop invariant: No element of diffList is greater than 2 (or less than 0).
	 * I.e., no difference occurs more than twice.
	 */
	while(theStack.size() != 0) {
		//MSG("Looking for vertex number ", numVerts)
		//MSG("On cycle no. ", cycleID)

		// Get the next candidate vertex from the theStack.
		Vertex nextVertex = theStack[theStack.size()-1];
		int next = nextVertex.vertex;
		theStack.pop_back();

		//MSG("cycle list: ", str_cycle_list(numCycles, factor, cycleList))
		//MSG("While loop start diff list: ", str_int_array(n-1, diffList))
		//MSG("Looking at vertex ", next)

		// If all of the children of a vertex on the cycle are dead ends, we need to roll the vertex up.
		while(numVerts > 0 && nextVertex.parent != cycle[numVerts-1].vertex) {
			//cout << str_cycle_list(numCycles, factor, cycleList) << endl;
			//cout << "I am " << next << " , expecting " << cycle[numVerts-1].vertex<< " as my parent" << endl;
			//cout << "Instead I got " << nextVertex.parent << endl;
			numVerts = roll_back(numVerts, cycle, diffList, available);
		}

		/* Find out if we would have too many instances of some difference if
		 * we put this on the cycle. If so, don't put this vertex on cycle.
		 */
		if(numVerts > 0) {
			if(increase_diffs(cycle[numVerts-1].vertex, next, diffList)) {
				//cout << "Putting " << next << " on cycle" << endl;
				cycle[numVerts] = nextVertex;
				numVerts++;
				available[next] = 0;
				//cout << "Current diff list: ";
				//print_int_array(n-1, diffList);
			} else {
				continue;
			}
		} else {
			// Very first vertex on the cycle, don't need to calculate differences.
			//cout << "Putting " << next << " on cycle" << endl;
			cycle[numVerts] = nextVertex;
			numVerts++;
			available[next] = 0;
		}

		// Check if we have a whole cycle
		if(numVerts == cycleLen) {
			//cout << "We have a whole cycle, but it may get rolled back... " << endl;
			// Check differences given by first and last vertex of cycle
			if(!increase_diffs(cycle[0].vertex, next, diffList)) {
				numVerts = roll_back(numVerts, cycle, diffList, available);
				continue;
			}

			// Check if we have a 2-factor
			if(cycleID == numCycles-1) {
				// Everything should be dandy in terms of differences.
				//cout << "Found a twofold 2-starter, returning!" << endl;
				return true;
			} else {
				// See if we got stuck down the line.
				if(!find_cycle(n, factor, numCycles, cycleID+1, cycleList, diffList, available)) {
					// Roll the cycle back
					numVerts = roll_back(numVerts, cycle, diffList, available);
					// Remember to change diffs for first and last vertices as well
					//cout << "Updating diffs for first and last vertex of cycle." << endl;
					decrease_diffs(cycle[0].vertex, next, diffList);
					continue;
				}

				//cout << "*GASP* I think we found a cycle" << endl;

				return true;
			}
		}

		/* Update theStack. If we reach this line, it means we have put something on cycle,
		 * because we always 'continue' if we roll the cycle back or do nothing.
		 */
		//cout << "Expanding the vertex " << next << endl;
		expand_vertex(n, next, available, theStack);
	}

	// No twofold 2-starter possible, return false.
	//cout << "Could not find cycle, returning false" << endl;
	while(numVerts > 0) {
		numVerts = roll_back(numVerts, cycle, diffList, available);
	}

	return false;
}

/**
 * Tries to find a twofold 2-starter of the OP specified by factor. 
 * 
 * @param n - the order of the OP; the number of vertices in the complete graph.
 * @param numCycles - the number of cycles in each 2-factor.
 * @param factor - array of length numCycles such that factor[i] is the length of the i-th cycle in the 2-factor.
 * @param cycleList - a zero-initialised array in which to store the starter, if we find one. 
 *                    cycleList has length numCycles and for each 0 <= i < numCycles, cycleList[i] has 
 *                    length factor[i].
 * 
 * @return true iff we could find a twofold 2-starter.
 */
bool find_starter(int n, int numCycles, int* factor, Vertex** cycleList) {
	INF = n-1;
	// The current list of differences, with diffList[i] = number of occurrences of difference i.
	int diffList[n-1];

  for(int i = 0; i < n-1; i++) {
    diffList[i] = 0;
  }

	initialise_cycle_list(numCycles, factor, cycleList);
	int available[n];
	init_available(n, available);

	return find_cycle(n, factor, numCycles, 0, cycleList, diffList, available);
}

