/*
 * stack.h
 *
 *  Created on: Sep 30, 2018
 *      Author: myvaheed
 */

#ifndef HEADERS_STACK_H_
#define HEADERS_STACK_H_

#include <stdlib.h>

template <class T>
class Stack {
	T* stack;
	size_t size = 0;
	size_t capacity;

private:
	void swap_trick(Stack& obj);

	template <class UR>
	void pushImpl(UR&& elem);

public:
	Stack();
	Stack(size_t capacity);
	Stack(Stack const& robj);
	Stack(Stack&& robj);

	~Stack();

	Stack& operator=(Stack rs);
	bool operator==(Stack const& rs);

	bool is_empty();
	size_t height();

	void push(T const& elem);
	void push(T&& elem);

	T pop();
	T const& top();
};

#endif /* HEADERS_STACK_H_ */
