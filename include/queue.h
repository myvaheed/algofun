/*
 * queue.h
 *
 *  Created on: Sep 30, 2018
 *      Author: myvaheed
 */

#ifndef HEADERS_QUEUE_H_
#define HEADERS_QUEUE_H_

#include <stdlib.h>
#include <stdint.h>
#include <base_node.h>

/*
 * noncopyable class Queue
 *
 */

template <class T>
class Queue {
	QNode<T>* last;
	QNode<T>* first;
	size_t size = 0;

private:
	void swap_trick(Queue& obj);

	template<class UR>
	void enqueueImpl(UR&& elem);

public:
	Queue();
	Queue(Queue&& robj);
	~Queue();

	Queue& operator=(Queue&& rs);
	bool operator==(Queue const& rs);

	Queue(Queue const& robj) = delete;
	Queue& operator=(Queue const& rs) = delete;

	bool is_empty() const;
	size_t length() const;
	void enqueue(T&& elem);
	void enqueue(T const& elem);
	T dequeue();
	T const& back() const;
	T const& front() const;
};


#endif /* HEADERS_QUEUE_H_ */
