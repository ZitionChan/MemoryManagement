#pragma once
#include"PageTable.h"

template<class T>
class Frame :public PageTable<T> {
public:
	int pid;//����Ľ���id
	Frame(int size=FrameSize) :PageTable<T>(size) {

	}

};