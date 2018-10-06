/*
 * instantiating.cpp
 *
 *  Created on: Sep 30, 2018
 *      Author: myvaheed
 */


#include "stackdef.hpp"
#include "queuedef.hpp"
#include "sort.cpp"
#include "dheapdef.hpp"

template class Stack<int>;
template class Stack<A>;
template class Queue<int>;
template class Queue<A>;
template class DHeap<int, 3>;
template class DHeap<int, 2>;
template class DHeap<A, 3>;

template class Stack<std::string>;
template class Queue<std::string>;

template class Sort<int>;
