/*
 * main.cpp
 *
 *  Created on: 4 Aug 2015
 *      Author: alexi_000
 */

#include <fstream>

#include "twofoldstarter.h"
#include "checkers.h"
#include "tests.h"

#define TEST false

using std::ofstream;
using std::stringstream;

/**
 * *SIGH* Could not get unit tests to work!!!
 */
int run_tests() {
	if(!test_check_differences_all()) {
		cout << "Difference verifier not working!!" << endl;
		return -1;
	}

	if(!test_repeat_all()) {
		cout << "Repeat checker not working!!" << endl;
		return -1;
	}

	cout << "Checker code is working, running OPs" << endl;

	if(!test_all()) {
		cout << "!!!FAIL!!!" << endl;
		return -1;
	}

	cout << "All tests pass" << endl;
	return 0;
}

int main(int argc, char** argv) {

	if(TEST) {
		cout << "Testing code. Change variable TEST to false if you want to use program." << endl;
		return run_tests();
	}

	cout << "This is a program to find twofold 2-starters" << endl;
	cout << "This is version 1" << endl;

	if(argc < 4) {
		cout << "Usage: TwofoldStarter.exe n t l_1 l_2 ... l_t fileName" << endl;
		cout << "where n is number of vertices, t is number of cycles, l_i are cycle lengths" << endl;
		cout << "and where fileName is the file you want to output the result to." << endl;
		return -1;
	}

	int n = atoi(argv[1]);
	int numCycles = atoi(argv[2]);
	if(argc - 4 != numCycles) {
		cout << "Too few or too many cycle lengths entered. Or maybe you forgot the file name?" << endl;
		cout << "But have I told you how amazingly good looking you are?" << endl;
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

	char* fileName = argv[argc-1];
	ofstream outFile(fileName, std::ios_base::app);
	if(!outFile.is_open()) {
		cout << "Could not open output file." << endl;
		return -2;
	} else {
		outFile << n << "; " << str_int_array(numCycles, factor) << " : ";
	}

	cout << "Trying to compute a twofold 2-starter with cycle lengths: "
		 << str_int_array(numCycles, factor) << endl;
	cout << "Vertices are labelled from 0 to " << n-1 << " with "
		 << n-1 << " being infinity." << endl;
	cout << "Result will be appended to " << fileName << endl;

	Vertex* cycleList[numCycles];
	stringstream ssCycleList;
	string starter;

	if(find_starter(n, numCycles, factor, cycleList)) {
		ssCycleList << str_cycle_list(numCycles, factor, cycleList);
		starter = ssCycleList.str();
		cout << "Your beautiful twofold 2-starter: ";
		cout <<  starter << endl;

		outFile << starter;

		// Run sanity checks.
		if(verify(n, numCycles, factor, cycleList)) {
			cout << "It looks to be correct!" << endl;
			outFile << " PASS" << endl;
		} else {
			cout << "Failed sanity checks! Differences are incorrect or vertices repeat." << endl;
			cout << "Oh Knuth, Shannon and Erdos have mercy, the code has bugs." << endl;
			outFile << " !!!!!!!FAIL!!!!!!" << endl;
		}
	} else {
		cout << "No 2-starter found!" << endl;
		outFile << "--" << endl;
	}

	cout << endl;
	outFile.close();
	return 0;
}



