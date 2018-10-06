/*
 * sort.h
 *
 *  Created on: Sep 29, 2018
 *      Author: myvaheed
 */

#ifndef SORT_H_
#define SORT_H_

#include <vector>
#include <iostream>

//as namespace
template<class T>
struct Sort {

	static void swap(T& a, T& b) {
		T temp = a;
		a = b;
		b = temp;
	}

	static void insertion_sort(std::vector<T>& data);
	static void bubble_sort(std::vector<T>& data);
	static void straight_selection_sort(std::vector<T>& data);
	static void quicksort(std::vector<T>& data);
	struct _quicksort {
		static void quicksortImpl(std::vector<T>& data, uint left, uint right);
		static void partition(std::vector<T>& data, uint& left, uint& right);
	};

	static void merge_sort(std::vector<T>& data);
	struct _mergesort {
		static std::vector<T> merge(std::vector<T>& data, uint left, uint right);
	};

	static void heap_sort(std::vector<T>& data);
};



#endif /* SORT_H_ */
