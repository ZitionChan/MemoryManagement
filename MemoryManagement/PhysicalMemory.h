#pragma once

#include<iostream>
#include<vector>
#include"Frame.h"
#include"PhysicalAddress.h"
#include"FrameOrder.h"
#include"Config.h"

using namespace std;

struct FramesStruct {
	int newFrameNumber;
	int oldPid;
};

class PhysicalMemory {
	unsigned int maxSize;
	FrameOrder<int> frameOrders;//储存的frame分配顺序
	vector<Frame_t*> frames;
public:
	PhysicalMemory(unsigned int size);

	FramesStruct assign(unsigned int pid); //模拟请求分配内存，返回一个{分配的页框号,被替换的pid }

	void access(PhysicalAddress address);

};