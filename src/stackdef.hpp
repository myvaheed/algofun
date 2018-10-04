/*
 * stack.cpp
 *
 *  Created on: Sep 30, 2018
 *      Author: myvaheed
 */

#ifndef HEADERS_STACKDEF_H_
#define HEADERS_STACKDEF_H_

#include <stack.h>
#include <cstring>
#include <utility>
#include <stdexcept>
#include <functional>

template<class T>
Stack<T>::Stack() : capacity(10) {
	this->stack = new T[capacity];
}

template<class T>
Stack<T>::Stack(size_t capacity) : capacity(capacity) {
	if (capacity == 0)
		throw std::runtime_error("A capacity can not be small than 1");
	this->stack = new T[capacity];
}

template<class T>
Stack<T>::Stack(Stack<T> const& obj) :
		stack(new T[obj.capacity]),
		capacity(obj.capacity),
		size(obj.size) {
	std::memcpy(stack, obj.stack, sizeof(T) * this->capacity);
}

template<class T>
Stack<T>::Stack(Stack&& robj) : Stack() {
	swap_trick(robj);
}

template<class T>
Stack<T>::~Stack() {
	delete[] stack;
	size = 0;
	capacity = 0;
}

/*
 * for copy and move assignments
 */
template<class T>
Stack<T>& Stack<T>::operator=(Stack obj) {
	Stack<T> temp(obj);
	swap_trick(temp);
	return *this;
}

template<class T>
bool Stack<T>::operator==(Stack<T> const& obj) {
	if (size != obj.size)
		return false;
	return !memcmp(stack, obj.stack, sizeof(T) * size);
}

template<class T>
T const& Stack<T>::top() {
	if (is_empty())
		throw std::length_error("The Stack is empty");
	return stack[size - 1];
}

#include <queue>

template<class T>
T Stack<T>::pop() {
	if (is_empty())
		throw std::length_error("The Stack is empty");
	return std::move(stack[--size]);
}

template<class T>
void Stack<T>::push(T&& elem) {
	pushImpl(std::move(elem));
}

template<class T>
void Stack<T>::push(T const& elem) {
	pushImpl(elem);
}

template<class T>
template<class UR>
void Stack<T>::pushImpl(UR&& elem) {
    static_assert(std::is_same<std::remove_cv_t<std::remove_reference_t<UR>>, T>::value, "UR and T should be the same!");
	if (capacity == size) {
		try {
			Stack<T> newStack(2 * capacity);
			std::memcpy(newStack.stack, stack, sizeof(T) * size);
			newStack.size = size;
			swap_trick(newStack);
		} catch (std::bad_alloc const& e) {
			throw std::bad_alloc();
		}
	}
	stack[size++] = std::forward<UR>(elem);
}

template<class T>
bool Stack<T>::is_empty() {
	return size == 0;
}

template<class T>
size_t Stack<T>::height() {
	return size;
}

template<class T>
void Stack<T>::swap_trick(Stack& obj) {
	using std::swap;
	swap(obj.capacity, this->capacity);
	swap(obj.size, this->size);
	swap(obj.stack, this->stack);
}

#endif
