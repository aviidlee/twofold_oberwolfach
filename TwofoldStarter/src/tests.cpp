/*
 * tests.cpp
 *
 * BECAUSE I CAN'T GET THE UNIT TESTING FRAMEWORK TO WORK!!!
 *
 *  Created on: 14 Aug 2015
 *      Author: alexi_000
 */
#include "checkers.h"

/**
 * Check that a correct list of difference, i.e., one otf
 * [0, 2, 2, ..., 2] works.
 *
 * NB cycle length is expected to be >= 3 here.
 */
bool test_pos_check_diffs() {

    /*
     * Odd n
     * Example from lit review. Order = 7, Inf = 6.
     */
    Vertex c1[] = {Vertex(6), Vertex(2), Vertex(5)};
    Vertex c2[] = {Vertex(0), Vertex(1), Vertex(3), Vertex(4)};
    Vertex* cycleList[] = {c1, c2};
    int factor[] = {3, 4};
    if(!check_differences(7, 2, factor, cycleList)) {
        return false;
    }

    /*
     * Even n
     * Manually checked starter for OP(4, 4)
     */
    Vertex c3[] = {Vertex(7), Vertex(6), Vertex(5), Vertex(3)};
    Vertex c4[] = {Vertex(4), Vertex(1), Vertex(2), Vertex(0)};
    Vertex* cycleList2[] = {c3, c4};
    int factor2[] = {4, 4};
    if(!check_differences(8, 2, factor2, cycleList2)) {
    	return false;
    }

    /*
     * For good measure.
     */
    Vertex a[] = {Vertex(11), Vertex(10), Vertex(9)};
    Vertex b[] = {Vertex(8), Vertex(6), Vertex(3)};
    Vertex c[] = {Vertex(7), Vertex(2), Vertex(0)};
    Vertex d[] = {Vertex(5), Vertex(4), Vertex(1)};
    Vertex* cycleList3[] = {a, b, c, d};
    int factor3[] = {3, 3, 3, 3};
    if(!check_differences(12, 4, factor3, cycleList3)) {
		return false;
	}

    return true;
}

/**
 * Check that missing/duplicated differences are picked up.
 */
bool test_neg_check_diffs() {
	Vertex c1[] = {0, 1, 2};
	Vertex c2[] = {3, 4, 5};
	Vertex* cycleList[] = {c1, c2};
	int factor[] = {3, 3};
	if(check_differences(6, 2, factor, cycleList)) {
		return false;
	}

	Vertex c3[] = {1, 7, 0};
	Vertex c4[] = {2, 3, 4, 6, 5};
	Vertex* cycleList2[] = {c3, c4};
	int factor2[] = {3, 5};
	if(check_differences(8, 2, factor2, cycleList2)) {
		return false;
	}

    return true;
}

bool test_check_differences_all() {
    return test_pos_check_diffs() && test_neg_check_diffs();
}

bool test_no_repeat() {
    return false;
}

bool test_repeat() {
    return false;
}

bool test_repeat_all() {
    return false;
}






