/*
 * queuedef.hpp
 *
 *  Created on: Sep 30, 2018
 *      Author: myvaheed
 */

#ifndef QUEUEDEF_HPP_
#define QUEUEDEF_HPP_

#include <queue.h>
#include <cstring>
#include <utility>
#include <stdexcept>
#include <functional>

template<class T>
Queue<T>::Queue(): first(nullptr), last(nullptr) {}

template<class T>
Queue<T>::Queue(Queue&& robj) : Queue() {
	swap_trick(robj);
}

template<class T>
Queue<T>::~Queue() {
	size = 0;
	while (first) {
		QNode<T>* next = first->next;
		delete first;
		first = next;
	}
}

template<class T>
Queue<T>& Queue<T>::operator=(Queue&& obj) {
	swap_trick(obj);
	return *this;
}

#include <boost/concept_check.hpp>
template<class T>
bool Queue<T>::operator==(Queue<T> const& obj) {
	//is operator== defined for T
	BOOST_CONCEPT_ASSERT((boost::EqualityComparable<T>));

	if (size != obj.size)
		return false;
	QNode<T>* item = first;
	QNode<T>* itemObj = obj.first;
	while(item) {
		if (!(item->data == itemObj->data))
			return false;
		item = item->next;
		itemObj = itemObj->next;
	}
	return true;
}

template<class T>
T const& Queue<T>::back() {
	if (is_empty())
		throw std::length_error("The Queue is empty");
	return last->data;
}

template<class T>
T const& Queue<T>::front() {
	if (is_empty())
		throw std::length_error("The Queue is empty");
	return first->data;
}

template<class T>
T Queue<T>::dequeue() {
	if (is_empty())
		throw std::length_error("The Queue is empty");
	T data = std::move(first->data);

	QNode<T>* next = first->next;
	delete first;
	first = next;
	size--;

	return data;
}

template<class T>
void Queue<T>::enqueue(T&& elem) {
	enqueueImpl(std::move(elem));
}

template<class T>
void Queue<T>::enqueue(T const& elem) {
	enqueueImpl(elem);
}

template<class T>
template<class UR>
void Queue<T>::enqueueImpl(UR&& elem) {
    static_assert(std::is_same<std::remove_cv_t<std::remove_reference_t<UR>>, T>::value, "UR and T should be the same!");

	QNode<T>* new_item = new QNode<T>(std::forward<UR>(elem));
	if (is_empty()) {
		first = new_item;
		last = first;
	} else {
		last->next = new_item;
		last = new_item;
	}
	size++;
}

template<class T>
size_t Queue<T>::length() {
	return size;
}

template<class T>
bool Queue<T>::is_empty() {
	return size == 0;
}

template<class T>
void Queue<T>::swap_trick(Queue& obj) {
	using std::swap;
	swap(obj.first, this->first);
	swap(obj.size, this->size);
	swap(obj.last, this->last);
}



#endif /* QUEUEDEF_HPP_ */
