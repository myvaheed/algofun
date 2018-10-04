/*
 * stack_test.h
 *
 *  Created on: Sep 30, 2018
 *      Author: myvaheed
 */

#ifndef STACK_TEST_CPP_
#define STACK_TEST_CPP_

#include <boost/test/auto_unit_test.hpp>
#include <stack.h>
#include "for_testing.h"

namespace utf = boost::unit_test;

BOOST_AUTO_TEST_SUITE(StackTest)


BOOST_AUTO_TEST_CASE(Empty) {
	Stack<int> emptyStack;
	BOOST_REQUIRE(emptyStack.is_empty());
}

BOOST_AUTO_TEST_CASE(Same) {
	Stack<int> stack1;
	stack1.push(4);
	stack1.push(3);
	stack1.push(2);
	Stack<int> stack2 = stack1;
	BOOST_REQUIRE(stack1 == stack2);
}

BOOST_AUTO_TEST_CASE(NotSame) {
	Stack<int> stack1;
	stack1.push(4);
	stack1.push(3);
	stack1.push(2);
	Stack<int> stack2 = stack1;
	stack2.pop();
	stack2.push(543);
	BOOST_REQUIRE(!(stack1 == stack2));
}

BOOST_AUTO_TEST_CASE(PushPop, * utf::enabled()) {
	Stack<int> stack;

	for (int i = -1000; i <= 1000; i++) {
		stack.push(i);
	}

	for (int i = 1000; i >= -1000; i--) {
		BOOST_REQUIRE(stack.pop() == i);
	}

	BOOST_REQUIRE_THROW(stack.pop(), std::length_error);
}


BOOST_AUTO_TEST_CASE(Moved) {
	Stack<int> stack;
	stack.push(4);
	stack.push(3);
	stack.push(2);
	Stack<int> stack2 = std::move(stack);
	BOOST_REQUIRE(stack.is_empty());
	BOOST_REQUIRE(stack2.pop() == 2);
}


BOOST_AUTO_TEST_CASE(Lvalue) {
	Stack<int> stack1;
	stack1.push(4);
	stack1.push(3);
	int val = 34;
	stack1.push(val);
	int from_stack = stack1.pop();
	BOOST_REQUIRE(from_stack == 34);
}


BOOST_AUTO_TEST_CASE(WithObject) {
	Stack<A> stack1;
	stack1.push(A(1));
	stack1.push(A(2));
	A a1(3);
	stack1.push(std::move(a1));
	BOOST_REQUIRE(a1.getval() == 0);

	int s = stack1.pop().getval();
	BOOST_REQUIRE(s == 3);

	A a2(4);
	stack1.push(a2);
	BOOST_REQUIRE(stack1.top().getval() == 4);
	stack1.top().setval(5);
	BOOST_REQUIRE(stack1.top().getval() == 5);
	BOOST_REQUIRE(a2.getval() == 4);

	stack1.top().setval(6);
	A changed_front = stack1.top();
	BOOST_REQUIRE(changed_front.getval() == 6);

}


BOOST_AUTO_TEST_SUITE_END()



#endif /* STACK_TEST_CPP_ */
