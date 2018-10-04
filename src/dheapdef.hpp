/*
 * dheapdef.hpp
 *
 *  Created on: Oct 2, 2018
 *      Author: myvaheed
 */

#ifndef DHEAPDEF_HPP_
#define DHEAPDEF_HPP_

#include <dheap.h>
#include <cstring>

template<class T, uint D>
DHeap<T,D>::DHeap() : capacity(10) {
	this->nodes = new DNode<T>[capacity];
}

template<class T, uint D>
DHeap<T, D>::DHeap(size_t capacity) : capacity(capacity) {
	if (capacity == 0)
		throw std::runtime_error("A capacity can not be small than 1");
	this->nodes = new DNode<T>[capacity];
}

template<class T, uint D>
DHeap<T, D>::DHeap(std::vector<T>const& arrayToHeap) : DHeap(arrayToHeap.size()) {
	for (auto elem : arrayToHeap) {
		push(elem);
	}
}

template<class T, uint D>
DHeap<T,D>::DHeap(DHeap<T,D> const& obj) :
		nodes(new DNode<T>[obj.capacity]),
		capacity(obj.capacity),
		_size(obj._size) {
	std::memcpy(nodes, obj.nodes, sizeof(DNode<T>) * this->capacity);
}

template<class T, uint D>
DHeap<T,D>::DHeap(DHeap&& robj) : DHeap() {
	swap_trick(robj);
}

template<class T, uint D>
DHeap<T, D>::~DHeap() {
	delete[] nodes;
	_size = 0;
	capacity = 0;
}

/*
 * for copy and move assignments
 */
template<class T, uint D>
DHeap<T,D>& DHeap<T,D>::operator=(DHeap obj) {
	DHeap<T,D> temp(obj);
	swap_trick(temp);
	return *this;
}

template<class T, uint D>
bool DHeap<T,D>::operator==(DHeap<T, D> const& obj) {
	if (_size != obj._size)
		return false;
	for (uint i = 0; i < _size; i++) {
		if (nodes[i].data != obj.nodes[i].data)
			return false;
	}
	return true;
}

template<class T, uint D>
bool DHeap<T,D>::is_sheet(uint index) {
	if (index >= _size)
		throw NotValidIndex();
	return (index * D + 1) > (_size - 1);
}

template<class T, uint D>
bool DHeap<T,D>::is_root(uint index) {
	return index == 0;
}


template<class T, uint D>
uint DHeap<T,D>::leftChildId(uint index) {
	if (index >= _size || is_sheet(index))
		throw NotValidIndex();

	return index * D + 1;
}

template<class T, uint D>
uint DHeap<T,D>::rightChildId(uint index) {
	uint l = leftChildId(index);
	return std::min(l + D - 1, (uint) _size - 1);
}

template<class T, uint D>
uint DHeap<T,D>::minChildId(uint index) {
	uint l = leftChildId(index);
	uint r = rightChildId(index);
	uint minInd = l;
	while (l <= r) {
		if (nodes[l].data < nodes[minInd].data) {
			minInd = l;
		}
		l++;
	}
	return minInd;
}

template<class T, uint D>
uint DHeap<T,D>::parentId(uint index) {
	if (index >= _size || is_root(index))
		throw NotValidIndex();
	return (index - 1) / D;
}

template<class T, uint D>
void DHeap<T,D>::emersion(uint index) {
	if (is_root(index))
		return;

	uint p = parentId(index);
	uint ch = index;

	while (nodes[p].data >= nodes[ch].data) {
		std::swap(nodes[p], nodes[ch]);
		ch = p;
		if (is_root(ch))
			return;
		p = parentId(ch);
	}
}

template<class T, uint D>
void DHeap<T,D>::diving(uint index) {
	if (is_sheet(index))
		return;

	uint p = index;
	uint ch = minChildId(p);

	while (nodes[p].data >= nodes[ch].data) {
		std::swap(nodes[p], nodes[ch]);
		p = ch;
		if (is_sheet(p))
			return;
		ch = minChildId(p);
	}
}

template<class T, uint D>
void DHeap<T, D>::decreaseWeightToMin(uint i) {
	if (i >= _size)
		throw NotValidIndex();
	nodes[i].data = nodes[0].data;
	emersion(i);
}

template<class T, uint D>
T DHeap<T, D>::pop() {
	T data = std::move(nodes[0].data);
	std::swap(nodes[0], nodes[--_size]);
	if (!is_empty())
		diving(0);
	return std::move(data);
}

template<class T, uint D>
void DHeap<T, D>::push(T&& elem) {
	pushImpl(std::move(elem));
}

template<class T, uint D>
void DHeap<T, D>::push(T const& elem) {
	pushImpl(elem);
}

template<class T, uint D>
template<class UR>
void DHeap<T, D>::pushImpl(UR&& elem) {
    static_assert(std::is_same<std::remove_cv_t<std::remove_reference_t<UR>>, T>::value, "UR and T should be the same!");

    if (capacity == _size) {
		try {
			DHeap<T, D> temp(2 * capacity);
			temp._size = _size;
			std::memcpy(temp.nodes, nodes, sizeof(DNode<T>) * _size);
			swap_trick(temp);
		} catch (std::bad_alloc&) {
			throw std::bad_alloc();
		}

	}
	nodes[_size++] = std::move(DNode<T>(std::forward<UR>(elem)));
	emersion(_size - 1);
}


template<class T, uint D>
bool DHeap<T, D>::is_empty() {
	return _size == 0;
}

template<class T, uint D>
size_t DHeap<T, D>::size() {
	return _size;
}

template<class T, uint D>
T DHeap<T, D>::root() {
	return nodes[0].data;
}


template<class T, uint D>
void DHeap<T,D>::swap_trick(DHeap& obj) {
	using std::swap;
	swap(obj.capacity, this->capacity);
	swap(obj._size, this->_size);
	swap(obj.nodes, this->nodes);
}



#endif /* DHEAPDEF_HPP_ */
