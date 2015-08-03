/*
 * stack.c
 *
 *  Created on: 2 Aug 2015
 *      Author: alexi_000
 */

#include <stdio.h>

typedef struct {
	// What's in the stack
	int* content;
	// Top element of stack
	int top;
	// Maximum number of things stack can hold.
	int capacity;
}  Stack;


