/*
 * stack.h
 *
 *  Created on: 2 Aug 2015
 *      Author: alexi_000
 */

#ifndef STACK_H_
#define STACK_H_

typedef struct {
	// What's in the stack
	int* content;
	// Top element of stack
	int top;
	// Maximum number of things stack can hold.
	int capacity;
}  Stack;


#endif /* STACK_H_ */
