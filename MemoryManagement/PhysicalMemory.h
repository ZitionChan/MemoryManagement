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
	FrameOrder<int> frameOrders;//�����frame����˳��
	vector<Frame_t*> frames;
public:
	PhysicalMemory(unsigned int size);

	FramesStruct assign(unsigned int pid); //ģ����������ڴ棬����һ��{�����ҳ���,���滻��pid }

	void access(PhysicalAddress address);

};