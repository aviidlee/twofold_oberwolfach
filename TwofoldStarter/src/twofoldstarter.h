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

#include "windows.h"

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
void print_int_array(int len, int* array);

#endif /* TWOFOLDSTARTER_H_ */
