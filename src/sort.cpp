/*
 * sort.cpp
 *
 *  Created on: Sep 29, 2018
 *      Author: myvaheed
 */
#include <sort.h>
#include <random>

template <class T>
void Sort<T>::insertion_sort(std::vector<T>& data) {

	if (data.size() == 1)
		return;

	for (size_t i = 1; i < data.size(); i++) {
		int j = i;
		while(j > 0 && data[j - 1] > data[j]) {
			swap(data[j - 1], data[j]);
			j--;
		}
	}
}

template<class T>
void Sort<T>::bubble_sort(std::vector<T>& data) {

	for (size_t i = 1; i < data.size(); i++) {
		for (size_t j = data.size() - 1; j >= i ; j--) {
			if (data[j - 1] > data[j]) {
				swap(data[j], data[j - 1]);
			}
		}

	}

}

template<class T>
void Sort<T>::straight_selection_sort(std::vector<T>& data) {

	if (data.size() == 1)
		return;

	for (size_t i = 0; i < data.size() - 1; i++) {
		int min = data[i];
		int indMin = i;
		for (size_t j = i + 1; j < data.size(); j++) {
			if (min > data[j]) {
				indMin = j;
				min = data[j];
			}
		}
		swap(data[indMin], data[i]);
	}
}


template<class T>
void Sort<T>::quicksort(std::vector<T>& data) {
	srand(time(0));
	_quicksort::quicksortImpl(data, 0, data.size() - 1);
}

template<class T>
void Sort<T>::_quicksort::quicksortImpl(std::vector<T>& data, uint left, uint right) {
	if (left >= right)
		return;

	uint nextLeft = left;
	uint nextRight = right;
	partition(data, nextLeft, nextRight);
	quicksortImpl(data, left, nextRight);
	quicksortImpl(data, nextLeft, right);
}

template<class T>
void Sort<T>::_quicksort::partition(std::vector<T>& data, uint& left, uint& right) {
	T pivot = data[rand() % (right - left) + left];
	while (left <= right) {

		while (data[left] < pivot)
			left++;

		while (pivot < data[right])
			right--;

		if (left <= right) {
			swap(data[right], data[left]);
			left++;
			right--;
		}

	}
}

template<class T>
void Sort<T>::merge_sort(std::vector<T>& data) {
	data = _mergesort::merge(data, 0, data.size());
}

template<class T>
std::vector<T> Sort<T>::_mergesort::merge(std::vector<T>& data, uint left, uint right) {
	if (left == right) return {};

	if (right - left == 1)
		return {data[left]};

	uint length = right - left;

	std::vector<T> sorted(length);

	uint index = (left + right) / 2;

	//I know, there's no necessity to allocate more arrays. It's for easier understanding
	std::vector<T> leftSide = merge(data, left, index);
	std::vector<T> rightSide = merge(data, index, right);

	uint lp = 0, rp = 0, hp = 0;
	while (lp < leftSide.size() && rp < rightSide.size()) {
		if (leftSide[lp] <= rightSide[rp]) {
			sorted[hp++] = leftSide[lp++];
		} else {
			sorted[hp++] = rightSide[rp++];
		}
	}

	//remaining
	while (rp < rightSide.size()) {
		sorted[hp++] = rightSide[rp++];
	}
	while (lp < leftSide.size()) {
		sorted[hp++] = leftSide[lp++];
	}

	return std::move(sorted);
}



