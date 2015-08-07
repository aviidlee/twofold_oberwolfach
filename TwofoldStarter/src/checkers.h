#include "twofoldstarter.h"

/**
 * Checks that no vertices are repeated.
 */
bool check_repeat(int n, int numCycles, int* factor, Vertex** cycleList) {
	// vertices[i] = number of times vertex i occurs.
	int vertices[n] = {0};

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
 *
 * REMEMBER TO IGNORE N BECAUSE IT'S INFINITY.
 */
bool check_differences(int n, int numCycles, int* factor, Vertex** cycleList) {
	int N = n-1;
	int diffList[N] = {0};

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

	cout << "Differences calculated by check_differences: " << str_int_array(N, diffList) << endl;
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
