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

	template<class T2>
	static void print(T2 const& a, char end = '\n') {
		if (typeid(T2).hash_code() == typeid(std::vector<T2>).hash_code()) {
			std::vector<int>const& b = static_cast<std::vector<int>const&>(a);
			for (auto el : b) {
				std::cout << el << end;
			}
		}
	}

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

};



#endif /* SORT_H_ */
