/*
 * stack_test.h
 *
 *  Created on: Sep 30, 2018
 *      Author: myvaheed
 */

#ifndef QUEUE_TEST_CPP_
#define QUEUE_TEST_CPP_

#include <boost/test/auto_unit_test.hpp>
#include <queue.h>

namespace utf = boost::unit_test;

BOOST_AUTO_TEST_SUITE(QueueTest, * utf::enabled())


BOOST_AUTO_TEST_CASE(Empty) {
	Queue<int> emptyQueue;
	BOOST_REQUIRE(emptyQueue.is_empty());
}

BOOST_AUTO_TEST_CASE(Same) {
	Queue<int> queue1;
	queue1.enqueue(4);
	queue1.enqueue(3);
	queue1.enqueue(2);
	Queue<int> queue2;
	queue2.enqueue(4);
	queue2.enqueue(3);
	queue2.enqueue(2);

	BOOST_REQUIRE(queue1 == queue2);
}

BOOST_AUTO_TEST_CASE(NotSame) {
	Queue<int> queue1;
	queue1.enqueue(4);
	queue1.enqueue(3);
	queue1.enqueue(2);
	Queue<int> queue2;
	queue2.enqueue(4);
	queue2.enqueue(3);
	queue2.enqueue(543);
	BOOST_REQUIRE(!(queue1 == queue2));
}

BOOST_AUTO_TEST_CASE(EnqueueDequeue) {
	Queue<int> queue1;
	for (int i = -132; i < 435; i++) {
		queue1.enqueue(std::move(i));
	}

	for (int i = -132; i < 435; i++) {
		BOOST_REQUIRE(queue1.dequeue() == i);
	}

	BOOST_REQUIRE_THROW(queue1.dequeue(), std::length_error);
}


BOOST_AUTO_TEST_CASE(Moved) {
	Queue<int> queue1;
	queue1.enqueue(4);
	queue1.enqueue(3);
	queue1.enqueue(2);
	Queue<int> queue2 = std::move(queue1);
	BOOST_REQUIRE(queue1.is_empty());
	BOOST_REQUIRE(queue2.dequeue() == 4);
}

BOOST_AUTO_TEST_CASE(Lvalue) {
	Queue<int> queue1;
	queue1.enqueue(4);
	queue1.enqueue(3);
	int val = 34;
	queue1.enqueue(val);
	int from_queue = queue1.dequeue();
	BOOST_REQUIRE(from_queue == 4);
}

BOOST_AUTO_TEST_CASE(WithObject) {
	Queue<A> queue1;
	queue1.enqueue(A(1));
	queue1.enqueue(A(2));
	A a1(3);
	queue1.enqueue(std::move(a1));
	BOOST_REQUIRE(a1.getval() == 0);

	int s = queue1.dequeue().getval();
	BOOST_REQUIRE(s == 1);

	A a2(4);
	queue1.enqueue(a2);
	BOOST_REQUIRE(queue1.back().getval() == 4);
	A copied = queue1.back();
	copied.setval(5);
	BOOST_REQUIRE(queue1.back().getval() == 4);
	BOOST_REQUIRE(a2.getval() == 4);
}



BOOST_AUTO_TEST_SUITE_END()



#endif /* STACK_TEST_CPP_ */
