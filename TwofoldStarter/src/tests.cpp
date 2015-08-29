/*
 * tests.cpp
 *
 * BECAUSE I CAN'T GET THE UNIT TESTING FRAMEWORK TO WORK!!!
 *
 *  Created on: 14 Aug 2015
 *      Author: alexi_000
 */
#include "checkers.h"

#define FAIL_MSG "MUCHO MUCHO FAIL! But you're good-looking so it's OK."
#define PASS_MSG "PASS"

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
	Vertex c3[] = {Vertex(7), Vertex(6), Vertex(5), Vertex(3)};
	Vertex c4[] = {Vertex(4), Vertex(1), Vertex(2), Vertex(0)};
	Vertex* cycleList2[] = {c3, c4};
	int factor2[] = {4, 4};
	if(!check_repeat(8, 2, factor2, cycleList2)) {
		return false;
	}

	return true;
}

bool test_repeat() {
	Vertex c3[] = {Vertex(7), Vertex(6), Vertex(5), Vertex(3)};
	Vertex c4[] = {Vertex(4), Vertex(0), Vertex(2), Vertex(0)};
	Vertex* cycleList2[] = {c3, c4};
	int factor2[] = {4, 4};
	if(check_repeat(8, 2, factor2, cycleList2)) {
		return false;
	}
    return true;
}

bool test_repeat_all() {
    return test_no_repeat() && test_repeat();
}

bool test_OP(int n, int numCycles, int* factor, string expected) {
	cout << "Testing OP of order " << n << ", parameters are "
		 << str_int_array(numCycles, factor) << endl;
	Vertex* cycleList[numCycles];
	find_starter(n, numCycles, factor, cycleList);
  string actual = str_cycle_list(numCycles, factor, cycleList);
	if(actual != expected) {
		cout << FAIL_MSG << endl;
    cout << "Expected " << expected << endl;
    cout << "But got " << actual << endl;
		return false;
	} else {
		cout << PASS_MSG << endl;
		return true;
	}
}

bool test_3_4() {
	int factor[] = {3, 4};
	return test_OP(7, 2, factor, "[[6, 5, 4][3, 1, 2, 0]]");
}

bool test_3_3() {
	int factor[] = {3, 3};
	Vertex* cycleList[2];
	// Should not find a solution
	cout << "Testing OP of order " << 6 << ", parameters are "
			 << str_int_array(2, factor) << endl;
	if(find_starter(6, 2, factor, cycleList)) {
		cout << FAIL_MSG << endl;
		return false;
	} else {
		cout << PASS_MSG << endl;
		return true;
	}
}

/*
 * Test OP_2(12; 3, 3, 3, 3)
 */
bool test_12() {
	int factor[] = {3, 3, 3, 3};
	return test_OP(12, 4, factor, "[[11, 10, 9][8, 6, 3][7, 2, 0][5, 4, 1]]");
}

bool test_11() {
	int factor[] = {3, 3, 5};
	return test_OP(11, 3, factor, "[[10, 9, 8][7, 6, 3][5, 1, 4, 2, 0]]");
}

bool test_4_4() {
	int factor[] = {4, 4};
	return test_OP(8, 2, factor, "[[7, 6, 5, 3][4, 1, 2, 0]]");
}

bool test_4_5() {
	int factor[] = {4, 5};
	return test_OP(9, 2, factor, "[[8, 7, 6, 1][5, 3, 4, 0, 2]]");
}

bool test_3_5() {
	int factor[] = {3, 5};
	return test_OP(8, 2, factor, "[[7, 6, 5][4, 2, 1, 3, 0]]");
}

bool test_all() {
	/* return test_3_4() && test_3_3() && test_12() && test_11()
			&& test_4_4() && test_4_5() && test_3_5();
  */
  return test_3_3() && test_12() && test_4_4() && test_3_5();
}
