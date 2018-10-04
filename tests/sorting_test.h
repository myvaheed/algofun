/*
 * sorting.cpp
 *
 *  Created on: Sep 30, 2018
 *      Author: myvaheed
 */

#include <boost/test/auto_unit_test.hpp>
#include <sort.h>


BOOST_AUTO_TEST_SUITE(Sorting)

std::vector<int> data = {35, 0, -14, 35, 23, 3, 54, 1, -13, 143};
std::vector<int> sorted = {-14, -13, 0, 1, 3, 23, 35, 35, 54, 143};

BOOST_AUTO_TEST_CASE(Bubble) {
	std::vector<int> cdata = data;
	Sort<int>::bubble_sort(cdata);
	BOOST_REQUIRE(cdata == sorted);
}

BOOST_AUTO_TEST_CASE(Insertion) {
	std::vector<int> cdata = data;
	Sort<int>::insertion_sort(cdata);
	BOOST_REQUIRE(cdata == sorted);
}

BOOST_AUTO_TEST_CASE(Quicksort) {
	std::vector<int> cdata = data;
	Sort<int>::quicksort(cdata);
	BOOST_REQUIRE(cdata == sorted);
}

BOOST_AUTO_TEST_CASE(MergeSort) {
	std::vector<int> cdata = data;
	Sort<int>::merge_sort(cdata);
	BOOST_REQUIRE(cdata == sorted);
}

BOOST_AUTO_TEST_SUITE_END()


