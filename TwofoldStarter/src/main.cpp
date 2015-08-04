/*
 * main.cpp
 *
 *  Created on: 4 Aug 2015
 *      Author: alexi_000
 */

#include "twofoldstarter.h"

int main(int argc, char** argv) {

	cout << "Looking for amazingly awesome twofold 2-factors!!!" << endl;
	cout << "This is version 1" << endl;

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
		cout << "Too few vertices or too few cycles!" << endl;
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
	cout << "Trying to compute a twofold 2-starter with cycle lengths: " << endl;
	print_int_array(numCycles, factor);

	Vertex* cycleList[numCycles];
	if(find_starter(n, numCycles, factor, cycleList)) {
		cout << str_cycle_list(numCycles, factor, cycleList) << endl;
	} else {
		cout << "No 2-starter found!" << endl;
	}

	return 0;
}



