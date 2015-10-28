# README
**Author:** Alexia (Alex) Lee
**Email:** alexia.lee@uqconnect.edu.au
**Institution:** The University of Queensland
**README updated on:** 28/10/2015

**Notes:** we use the terms "twofold 2-starter" and "starter" interchangeably.

## Description
This code was written as a part of an honours project on the twofold Oberwolfach
problem at the University of Queensland, under the supervision of Dr Barbara Maenhaut.
The code is a brute-force search for twofold 2-starters, as defined in the 2012 paper 
"2-starters, graceful labelings, and a doubling construction for the Oberwolfach Problem"
by Marco Buratti and Tommaso Traetta (http://www.ams.org/mathscinet-getitem?mr=2974194). 

So far, all problem instances have a starter. The list of starters are contained in the 
`results` folder. The vertices are labelled from 0 to n-1, and n-1 is the infinity vertex.
The starters are given in the format 

<order>: <lengths of cycles> : <cycles given as lists> PASS

For example, a starter for OP(14; 3, 3, 3, 5) is 

14; [3,3,3,5] : [[13, 12, 11][10, 9, 6][5, 3, 0][8, 4, 2, 7, 1]] PASS

with 13 being infinity. The `PASS` at the end just indicates that the starter passed
verification, so that it is actually a starter. 

## File list 
- results: contains starters for undecided twofold OPs of orders 10 to 32 inclusive.
	- OP10.txt
	- OP11.txt
	- OP12.txt
	- OP14.txt
	- OP16.txt
	- OP18.txt
	- OP20.txt
	- OP22.txt
	- OP24.txt
	- OP28.txt
	- OP30.txt

- src: all source code used to generate starters
	- `checkers.cpp`: code for verifying correctness of generated starters
	- `checkers.h`
	- `main.cpp`
	- `tests.cpp`: basic tests for code
	- `tests.h`
	- `TwofoldStarters.cpp`: code for finding twofold 2-starters
	- `Twofoldstarter.h`: wonderful consistency in naming
	- `vertex.h`: class representing node in the search tree

- `launcher.sh`: bash script for automatically submitting jobs to Obelix 
- `runner.sh`: bash script for submitting a single job, used by `launcher.sh`

## Compilation instructions
Coming soon. 

## Usage instructions
Run as 

twofoldstarters.exe <order of problem> <number of cycles in 2-factor> <space separated list of cycle lengths> <output file name>

For example, to solve OP(14; 3, 3, 3, 5) and output the result to a file called `out.txt`, run

twofoldstarters.exe 14 4 3 3 3 5 out.txt