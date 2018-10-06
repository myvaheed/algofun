/*
 * for_testing.h
 *
 *  Created on: Oct 1, 2018
 *      Author: myvaheed
 */

#ifndef HEADERS_FOR_TESTING_H_
#define HEADERS_FOR_TESTING_H_

#include <iostream>

#define PRINT_TEST 0

// class for testing
class A {
	int val;
public:
	A(int val = 0):val(val) {

#if PRINT_TEST
		printf("constr\n");
#endif

	}
	bool operator==(A const& a) {
		return val == a.val;
	}
	bool operator<=(A const& a) {
		return val <= a.val;
	}
	bool operator>=(A const& a) {
		return val >= a.val;
	}
	bool operator>(A const& a) {
		return val > a.val;
	}
	bool operator<(A const& a) {
		return val < a.val;
	}
	bool operator!=(A const& a) {
		return !this->operator==(a);
	}
	~A() {

#if PRINT_TEST
		printf("destrcr\n");
#endif

		val = - 1;
	}
	A(A const& obj): val(obj.val) {

#if PRINT_TEST
		printf("copy\n");
#endif

	}
	A(A&& obj): val(obj.val) {
		obj.val = 0;

#if PRINT_TEST
		printf("move\n");
#endif

	}

	A& operator=(A const& a) {
		this->val = a.val;

#if PRINT_TEST
		printf("copy assnmnt\n");
#endif

		return *this;
	}
	A& operator=(A&& a) {
		this->val = a.val;
		a.val = 0;

#if PRINT_TEST
		printf("move assnmnt\n");
#endif

		return *this;
	}

	int getval() const {return val;}
	void setval(int val) {this->val = val;}
};



#endif /* HEADERS_FOR_TESTING_H_ */
