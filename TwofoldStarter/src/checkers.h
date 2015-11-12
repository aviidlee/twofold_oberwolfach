#ifndef CHECKERS_H_
#define CHECKERS_H_

#include "twofoldstarter.h"

/**
 * Checks that no vertices are repeated.
 */
bool check_repeat(int n, int numCycles, int* factor, Vertex** cycleList);

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
bool check_differences(int n, int numCycles, int* factor, Vertex** cycleList);

/**
 * Return check_repeat && check_differences.
 */
bool verify(int n, int numCycles, int* factor, Vertex** cycleList);

#endif