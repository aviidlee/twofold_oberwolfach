/*
 * twostarter.h
 *
 *  Created on: 4 Aug 2015
 *      Author: alexi_000
 */

#ifndef TWOFOLDSTARTER_H_
#define TWOFOLDSTARTER_H_

#include <string>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include <cmath>

#include "vertex.h"

using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::stringstream;

bool find_starter(int n, int numCycles, int* factor, Vertex** cycleList);
bool find_cycle(int n, int* factor, int numFactors, int cycleID, Vertex** cycleList, int* diffList, int* available);
string str_cycle_list(int numCycles, int* factor, Vertex** cycleList);
string str_int_array(int len, int* array);

/**
 * @return min(previous - next mod modBy, next - previous mod modBy)
 */
inline int mod(int modBy, int previous, int next) {
	static int HALFDIFF = modBy/2;
	int diff = previous > next ? previous - next : next - previous;
	diff = diff % modBy;
	diff = diff <= HALFDIFF ? diff : modBy - diff;
	return diff;
}

#endif /* TWOFOLDSTARTER_H_ */
