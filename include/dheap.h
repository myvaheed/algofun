/*
 * dheap.h
 *
 *  Created on: Oct 2, 2018
 *      Author: myvaheed
 */

#ifndef INCLUDE_DHEAP_H_
#define INCLUDE_DHEAP_H_

#include "base_node.h"
#include <vector>

class NotValidIndex: public std::runtime_error {
public:
	NotValidIndex() :
			std::runtime_error("Not valid index") {}
};

template<class T, uint D = 3>
class DHeap {
	DNode<T>* nodes;
	size_t _size = 0;
	size_t capacity;

public:
	void swap_trick(DHeap& obj);

	template<class UR>
	void pushImpl(UR&& elem);

	bool is_sheet(uint i);
	bool is_root(uint i);
	uint leftChildId(uint i);
	uint rightChildId(uint i);
	uint minChildId(uint i);
	uint parentId(uint i);
	void diving(uint i);
	void emersion(uint i);
	void decreaseWeightToMin(uint i);
public:
	DHeap();
	DHeap(size_t capacity);
	DHeap(std::vector<T>const& arrayToHeap);
	DHeap(DHeap const& robj);
	DHeap(DHeap&& robj);

	~DHeap();

	DHeap& operator=(DHeap rs);

	bool operator==(DHeap<T,D> const& rs);

	bool is_empty();
	size_t size();

	void push(T const& elem);
	void push(T&& elem);

	T pop();
	T root();
};



#endif /* INCLUDE_DHEAP_H_ */
