/*
 * base_node.h
 *
 *  Created on: Sep 30, 2018
 *      Author: myvaheed
 */

#ifndef HEADERS_BASE_NODE_H_
#define HEADERS_BASE_NODE_H_

template<class T>
struct Node {
	T data;
	Node(T const& data): data(data){}
	Node(T&& data): data(std::move(data)) {}
	virtual ~Node() {}
};

//queue-node
template<class T>
struct QNode: public Node<T> {
	QNode* next;
	QNode* prev;
	QNode(T&& d) : Node<T>(std::move(d)) {
		next = nullptr;
		prev = nullptr;
	}
	QNode(T const& d): Node<T>(d) {
		next = nullptr;
		prev = nullptr;
	}
	~QNode() {
		next = nullptr;
		prev = nullptr;
	}
};

//d-ary heap-node
template<class T>
struct DNode : public Node<T> {
	DNode() : Node<T>(T()) {}
	DNode(T&& d) : Node<T>(std::move(d)) {}
	DNode(T const& d): Node<T>(d) {}
	DNode(DNode&& node) : Node<T>(std::move(node.data)){
		node.data = T();
	}
	DNode(DNode const& node) : Node<T>(node.data) {}
	DNode& operator=(DNode const& n) {
		Node<T>::data = n.data;
		return *this;
	}
	DNode& operator=(DNode&& n) {
		Node<T>::data = std::move(n.data);
		n.data = T();
		return *this;
	}
	~DNode() {}
};


#include "for_testing.h"

#endif /* HEADERS_BASE_NODE_H_ */
