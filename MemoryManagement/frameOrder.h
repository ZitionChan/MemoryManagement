#pragma once
//用于记录分配frame的顺序队列

#include<vector>
using namespace std;

template<class T>
class FrameOrder {
	int maxSize;
	vector<T> list;
public:
	FrameOrder(int size) :maxSize(size),list(0) {

	}

	void push(T value) {
		if(list.size()<maxSize)
		list.push_back(value);
		else throw out_of_range("frame Order is full");
	}

	T pop() {
		T front = list.front();
		list.erase(list.begin());
		return front;
	}

	void remove(T value) {
		for (auto it = list.begin(); it != list.end();it++) {
			if (*it == value) {
				list.erase(it);
				break;
			}
		}
	}

	bool isFull() {
		return maxSize == list.size();
	}

};