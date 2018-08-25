#pragma once
#include"PageTable.h"

template<class T>
class Frame :public PageTable<T> {
public:
	int pid;//分配的进程id
	Frame(int size=FrameSize) :PageTable<T>(size) {

	}

};