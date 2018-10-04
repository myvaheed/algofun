/*
 * dheap_test.h
 *
 *  Created on: Oct 2, 2018
 *      Author: myvaheed
 */

#ifndef DHEAP_TEST_H_
#define DHEAP_TEST_H_

#include <boost/test/auto_unit_test.hpp>
#include <dheap.h>

namespace utf = boost::unit_test;

BOOST_AUTO_TEST_SUITE(DHeapTest, * utf::enabled())

BOOST_AUTO_TEST_CASE(IsEmpty) {
	DHeap<int> heap;
	BOOST_REQUIRE(heap.is_empty());
}

BOOST_AUTO_TEST_CASE(Push) {
	DHeap<int> heap;
	heap.push(4);
	heap.push(2);
	heap.push(3);
	BOOST_REQUIRE(heap.size() == 3);
}

BOOST_AUTO_TEST_CASE(RootMin) {
	DHeap<int> heap;
	heap.push(4);
	heap.push(2);
	heap.push(3);
	BOOST_REQUIRE(heap.root() == 2);
}

BOOST_AUTO_TEST_CASE(Pop) {
	DHeap<int> heap(1);
	heap.push(4);
	heap.push(2);
	heap.push(3);
	heap.push(4);
	heap.push(1);
	heap.push(5);
	int min = heap.pop();
	BOOST_REQUIRE(min == 1);
	BOOST_REQUIRE(heap.root() == 2);
}

#include <sort.h>
BOOST_AUTO_TEST_CASE(PushPopMany, *utf::enabled()) {
	std::vector<int> data;
	DHeap<int> heap;
	size_t problemSize = 1000;
	for (size_t i = 0; i < problemSize; i++) {
		int num = rand() % 100;
		data.push_back(num);
		heap.push(num);
	}

	Sort<int>::quicksort(data);
	for (size_t i = 0; i < problemSize; i++) {
		BOOST_REQUIRE(data[i] == heap.pop());
	}
}

BOOST_AUTO_TEST_CASE(makeHeap, *utf::enabled()) {
	DHeap<int> heap({6, 2, 4, 2, 12, 8, 13, 14, 7});

	BOOST_REQUIRE(heap.pop() == 2);
	BOOST_REQUIRE(heap.pop() == 2);
	BOOST_REQUIRE(heap.pop() == 4);
	BOOST_REQUIRE(heap.pop() == 6);
	BOOST_REQUIRE(heap.pop() == 7);
	BOOST_REQUIRE(heap.pop() == 8);
	BOOST_REQUIRE(heap.pop() == 12);
	BOOST_REQUIRE(heap.pop() == 13);
	BOOST_REQUIRE(heap.pop() == 14);
}

BOOST_AUTO_TEST_CASE(Moved) {
	DHeap<int> heap1({6, 2, 4, 2, 12, 8, 13, 14, 7});
	DHeap<int> heap2(std::move(heap1));
	BOOST_REQUIRE(heap2.root() == 2);
	BOOST_REQUIRE(heap1.is_empty());
}

BOOST_AUTO_TEST_CASE(IsSame) {
	DHeap<int> heap1({6, 2, 4, 2, 12, 8, 13, 14, 7});
	DHeap<int> heap2({6, 2, 4, 2, 12, 8, 13, 14, 7});
	BOOST_REQUIRE(heap1 == heap2);
}

BOOST_AUTO_TEST_CASE(Copied) {
	DHeap<int> heap1({6, 2, 4, 2, 12, 8, 13, 14, 7});
	DHeap<int> heap2(heap1);
	BOOST_REQUIRE(heap1 == heap2);
}

BOOST_AUTO_TEST_CASE(D3vsD2) {
	DHeap<int, 3> heap1({6, 2, 4, 2, 12, 8, 13, 14, 7});
	DHeap<int, 2> heap2({6, 2, 4, 2, 12, 8, 13, 14, 7});

	for (size_t i = 0; i < heap1.size(); i++) {
		BOOST_REQUIRE(heap1.pop() == heap2.pop());
	}
}

BOOST_AUTO_TEST_CASE(WithObject) {
	DHeap<A,3> heap;
	heap.push(A(1));
	heap.push(A(2));
	A a1(3);
	heap.push(std::move(a1));
	BOOST_REQUIRE(a1.getval() == 0);

	int s = heap.pop().getval();
	BOOST_REQUIRE(s == 1);

	A a2(-10);
	heap.push(a2);
	BOOST_REQUIRE(heap.root().getval() == -10);
	heap.root().setval(10); //copy changed
	BOOST_REQUIRE(heap.root().getval() == -10);

	A fromHeap = heap.pop();
	BOOST_REQUIRE(fromHeap.getval() == -10);

}


BOOST_AUTO_TEST_SUITE_END()

#endif /* DHEAP_TEST_H_ */
