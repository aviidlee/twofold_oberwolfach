/*
 * checkers.cpp
 *
 *  Created on: 14 Aug 2015
 *      Author: alexi_000
 */

#include "checkers.h"

void zero_initialise(int n, int* array) {
	for(int i = 0; i < n; i++) {
		array[i] = 0;
	}

	return;
}

/**
 * Return true iff there are no repeated vertices (and thus every vertex
 * occurs exactly once)
 */
bool check_repeat(int n, int numCycles, int* factor, Vertex** cycleList) {
	// vertices[i] = number of times vertex i occurs.
	int vertices[n];
	zero_initialise(n, vertices);

	for(int i = 0; i < numCycles; i++) {
		Vertex* cycle = cycleList[i];
		int cycleLen = factor[i];
		for(int j = 0; j < cycleLen; j++) {
			vertices[cycle[j].vertex]++;
		}
	}

	for(int i = 0; i < n; i++) {
		if(vertices[i] != 1) {
			return false;
		}
	}

	return true;
}

/**
 * Checks that every difference in Z_{n-1}\{0} occurs exactly twice.
 * NOTE: cycle lengths must be >= 3
 *
 * @param n - the order of the OP
 * @param numCycles - the number of cycles in the factor
 * @param factor - the 2-factor, an array whose entries are cycle lengths.
 * @param cycleList - the supposed twofold 2-starter, consisting of an aray of
 * array of vertices, where the array of vertices represents a cycle.
 *
 * REMEMBER TO IGNORE N BECAUSE IT'S INFINITY.
 */
bool check_differences(int n, int numCycles, int* factor, Vertex** cycleList) {
	int N = n-1;
	int diffList[N];
	zero_initialise(N, diffList);

	//cout << "We are in the group Z_" << N << endl;
	//cout << "Our infinity element is thus " << N << endl;

	for(int i = 0; i < numCycles; i++) {
		Vertex* cycle = cycleList[i];
		int cycleLen = factor[i];

		for(int j = 0; j < cycleLen; j++) {
			int v1 = cycle[j].vertex;
			int v2 = cycle[mod(cycleLen, j+1)].vertex;
			if(v1 == N || v2 == N) {
				continue;
			}

			int diff1 = mod(N, v1 - v2);
			diffList[diff1]++;
			diffList[N - diff1]++;
		}
	}

	// cout << "Differences calculated by check_differences: " << str_int_array(N, diffList) << endl;
	for(int i = 1; i < N; i++) {
		if(diffList[i] != 2) {
			return false;
		}
	}

	return true;
}

bool verify(int n, int numCycles, int* factor, Vertex** cycleList) {
	return check_repeat(n, numCycles, factor, cycleList) &&
			check_differences(n, numCycles, factor, cycleList);
}
